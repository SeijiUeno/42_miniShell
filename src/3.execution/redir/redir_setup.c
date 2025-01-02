/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:43:09 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:33:25 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	redir_process(t_token *redir)
{
	if (redir->type == REDIR_IN || redir->type == HEREDOC)
		return (redirect_input(redir->content));
	if (redir->type == REDIR_OUT)
		return (redirect_output(redir->content));
	if (redir->type == APPEND)
		return (append_output(redir->content));
	return (EXIT_SUCCESS);
}

int	redir_setup(t_token *redir, t_ms *m)
{
	while (redir)
	{
		if (!redir->content)
		{
			ft_putstr_fd("Error: missing filename for redirection\n",
				STDERR_FILENO);
			m->status = 1;
			return (EXIT_FAILURE);
		}
		if (redir_process(redir) == EXIT_FAILURE)
		{
			m->status = 1;
			return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
