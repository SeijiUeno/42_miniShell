/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:26:11 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/09 20:26:16 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: error opening file '%s': %s\n", filename, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_output(char *filename)
{
	int	fd;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: error opening file '%s': %s\n", filename, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	append_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		fprintf(stderr, "minishell: error opening file '%s': %s\n", filename, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	setup_redirs(t_token *redir)
{
	while (redir)
	{
		if (!redir->content)
		{
			fprintf(stderr, "minishell: missing filename for redirection\n");
			return (EXIT_FAILURE);
		}

		if (redir->type == REDIR_IN || redir->type == HEREDOC)
		{
			if (redirect_input(redir->content) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (redirect_output(redir->content) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (redir->type == APPEND)
		{
			if (append_output(redir->content) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}
