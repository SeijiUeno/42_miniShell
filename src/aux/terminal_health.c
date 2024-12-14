/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_health.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:07 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 16:02:45 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void terminal_save_settings(struct termios *original_term) {
	struct termios term ;
	
    if (tcgetattr(STDIN_FILENO, original_term) == -1) { // Save original settings
        perror("tcgetattr");
        return;
    }

    term = *original_term;
    term.c_lflag &= ~ECHOCTL; // Disable signal character echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
    }
}

/* Restores terminal settings */
void	terminal_restore_settings(const struct termios *original)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

// free
void	prompt_clear(t_minishell *minishell)
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

void	free_all(t_minishell *minishell)
{
	if (!minishell)
		return ;
	util_free_array(minishell->path);
	util_free_array(minishell->envp);
	if (minishell->pid_list)
		free_list(&minishell->pid_list);
	if (minishell->input)
		free(minishell->input);
	if (minishell->tokens)
		free_all_tokens(&minishell->tokens);
	if (minishell->tree_cmd)
		free_tree(&minishell->tree_cmd);
	if (minishell->stdin_backup >= 0)
		close(minishell->stdin_backup);
	if (minishell->stdout_backup >= 0)
		close(minishell->stdout_backup);
	rl_clear_history();
}
