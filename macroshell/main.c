/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 18:20:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free
void	free_prompt(t_myShell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	minishell->input = NULL;
}

static void cleanup_minishell(t_minishell *minishell)
{
    free_prompt(minishell);
    free_resources_prompt(minishell);
    free_all(minishell);
    close(minishell->stdin_backup);
    close(minishell->stdout_backup);
}

//  terminal state 
void save_terminal_settings(struct termios *original)
{
    if (tcgetattr(STDIN_FILENO, original) == -1)
    {
        perror("tcgetattr");
        exit(EXIT_FAILURE);
    }
}
void restore_terminal_settings(const struct termios *original)
{
    if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
    {
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}

// build

int	build_commands(t_myShell *minishell)
{
	int	status;

	get_token(minishell->input, &(minishell->tokens));
	if (!(minishell->tokens) || !(minishell->tokens->content)
		|| validate_tokens(minishell->tokens) == 1)
		return (EXIT_FAILURE);
	set_operator_type(&(minishell->tokens));
	status = verify_heredoc(minishell);
	if (status)
	{
		minishell->status = status;
		return (EXIT_FAILURE);
	}
	ft_generate_tree(minishell);
	return (EXIT_SUCCESS);
}

void	build_and_execute(t_myShell *minishell)
{
	add_history(minishell->input);
	if (build_commands(minishell))
	{
		free_resources_prompt(minishell);
		return ;
	}
	execute_tree_commands(minishell);
	free_resources_prompt(minishell);
}

// core 
static void init_minishell(t_myShell *minishell)
{
    extern char **environ;

    if (environ != NULL)
    {
        minishell->envp = get_env(environ);
    }
    else
    {
        minishell->envp = NULL;
    }

    if (minishell->envp != NULL)
    {
        minishell->path = get_paths(minishell->envp);
    }
    else
    {
        minishell->path = NULL;
    }

    minishell->input = NULL;
    minishell->status = 0;
    minishell->stdin_backup = dup(STDIN_FILENO);
    minishell->stdout_backup = dup(STDOUT_FILENO);
    minishell->tokens = NULL;
    minishell->tree_cmd = NULL;
    minishell->pid_list = NULL;

    prepare_signals();
}

void shell_loop(t_myShell *minishell)
{
    static struct termios original_term;
    
    save_terminal_settings(&original_term);
    while (1)
    {
        reset_fds(minishell);
        minishell->input = readline("minishell$ ");
        if (control_status(-1))
            minishell->status = control_status(-1);
        control_status(0);

        if (!minishell->input)
            break;

        if (minishell->input[0])
            build_and_execute(minishell);
        restore_terminal_settings(&original_term);
        control_status(0);
    }
    restore_terminal_settings(&original_term); // Final cleanup
}

int main(void)
{
    t_myShell minishell;

    init_minishell(&minishell);
    shell_loop(&minishell);
    cleanup_minishell(minishell);
    return (0);
}