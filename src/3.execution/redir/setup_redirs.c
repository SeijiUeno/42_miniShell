/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:43:09 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/11 19:43:45 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int process_redirection(t_token *redir)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
		return (redirect_input(redir->content));
	if (redir->type == REDIR_OUT)
		return (redirect_output(redir->content));
	if (redir->type == APPEND)
		return (append_output(redir->content));
	return (EXIT_SUCCESS);
}

int setup_redirs(t_token *redir)
{
	while (redir)
	{
		if (!redir->content)
		{
			fprintf(stderr, "minishell: missing filename for redirection\n");
			return (EXIT_FAILURE);
		}
		if (process_redirection(redir) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
