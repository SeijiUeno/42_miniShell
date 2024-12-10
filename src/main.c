/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:16:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 14:38:26 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	get_and_reset_status(void)
{
	int current_status;

	current_status = control_status(STATUS_GET);
	control_status(0);
	return (current_status);
}

/* Saves terminal settings */
void	save_terminal_settings(struct termios *original)
{
	if (tcgetattr(STDIN_FILENO, original) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
}

/* Restores terminal settings */
void	restore_terminal_settings(const struct termios *original)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

//free 
void	free_prompt(t_minishell *minishell)
{
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_all_tokens(&(minishell->tokens));
	if (minishell->tree_cmd)
		free_tree(&(minishell->tree_cmd));
	if (minishell->pid_list)
		free_list(&(minishell->pid_list));
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

static void cleanup_minishell(t_minishell *minishell)
{
    free_all(minishell);
    if (minishell->stdin_backup >= 0)
        close(minishell->stdin_backup);
    if (minishell->stdout_backup >= 0)
        close(minishell->stdout_backup);
}

int main(void)
{
    t_minishell minishell;

    init_minishell(&minishell);
    shell_loop(&minishell);
    cleanup_minishell(&minishell);

    return EXIT_SUCCESS;
}
