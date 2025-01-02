/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:18:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:10:24 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, &signal_handle_heredoc);
}

static void	reset_signals(void)
{
	signal(SIGINT, &signal_handle);
}

static int	process_line(char *line, const char *delim, int fd)
{
	if (!line)
	{
		ft_putstr_fd("Warning: heredoc delimited by EOF. Expected: ",
			STDERR_FILENO);
		ft_putstr_fd(delim, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	if (ft_strcmp(line, delim) == 0)
		return (1);
	ft_putendl_fd(line, fd);
	return (0);
}

int	heredoc_read(const char *delim, int fd)
{
	char	*line;
	int		stop;

	stop = 0;
	setup_heredoc_signals();
	while (!stop)
	{
		line = readline("> ");
		if (!line)
		{
			if (errno == EINTR)
			{
				reset_signals();
				return (STATUS_SIGINT);
			}
			break ;
		}
		stop = process_line(line, delim, fd);
		free(line);
	}
	reset_signals();
	if (stop)
		return (0);
	else
		return (STATUS_EOF);
}

int	verify_heredoc(t_ms *minishell)
{
	t_token	*current;
	int		status;

	status = 0;
	current = minishell->tokens;
	while (current && !status)
	{
		if (current->type == HEREDOC)
			status = heredoc(&current->next->content, 0);
		current = current->next;
	}
	return (status);
}
