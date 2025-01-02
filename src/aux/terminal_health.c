/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_health.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:30:07 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:32:48 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	termios_save(struct termios *original_term)
{
	if (tcgetattr(STDIN_FILENO, original_term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
}

void	termios_restore(const struct termios *original)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, original) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	prompt_clear(t_ms *minishell)
{
	if (minishell->input)
		gc_deallocate(minishell->input);
	if (minishell->tokens)
		clear_tok(&(minishell->tokens));
	if (minishell->tree_cmd)
		clear_tr(&(minishell->tree_cmd));
	if (minishell->pid_list)
		clear_li(&(minishell->pid_list));
	minishell->input = NULL;
	minishell->tokens = NULL;
	minishell->tree_cmd = NULL;
	minishell->pid_list = NULL;
}

void	clear_al(t_ms *minishell)
{
	if (!minishell)
		return ;
	util_free_array(minishell->path);
	util_free_array(minishell->envp);
	if (minishell->pid_list)
		clear_li(&minishell->pid_list);
	if (minishell->input)
		gc_deallocate(minishell->input);
	if (minishell->tokens)
		clear_tok(&minishell->tokens);
	if (minishell->tree_cmd)
		clear_tr(&minishell->tree_cmd);
	if (minishell->stdin_backup >= 0)
		close(minishell->stdin_backup);
	if (minishell->stdout_backup >= 0)
		close(minishell->stdout_backup);
	rl_clear_history();
}
