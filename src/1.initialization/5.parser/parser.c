/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:56:46 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/06 15:09:00 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	parse_input(t_ms *minishell)
{
	int	status;

	status = generate_tokens(minishell->input, &(minishell->tokens));
	if (!(minishell->tokens) || !(minishell->tokens->content))
		return (2);
	if (validate_tokens(minishell->tokens) != EXIT_SUCCESS)
		return (2);
	minishell->tokens = remove_empty_tokens(&minishell->tokens);
	if (minishell->tokens == NULL || status != EXIT_SUCCESS)
		return (2);
	return (EXIT_SUCCESS);
}

static int	handle_heredocs(t_ms *minishell)
{
	int	status;

	status = verify_heredoc(minishell);
	if (status != EXIT_SUCCESS)
	{
		g_in_subprocess = SUBPROCESS_NONE;
		status_control(status);
		return (status);
	}
	if (g_in_subprocess == SUBPROCESS_INT_HDOC)
	{
		g_in_subprocess = SUBPROCESS_NONE;
		status_control(STATUS_SIGINT);
		return (STATUS_SIGINT);
	}
	return (EXIT_SUCCESS);
}

int	build_commands(t_ms *minishell)
{
	if (parse_input(minishell) != EXIT_SUCCESS)
		return (2);
	if (handle_heredocs(minishell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	generate_ast(minishell);
	return (EXIT_SUCCESS);
}
