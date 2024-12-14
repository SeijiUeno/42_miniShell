/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:26:58 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 14:42:26 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

static int	open_heredoc_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Failed to open heredoc file: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (fd);
}

static int	handle_heredoc_read(const char *str, int fd, char *filename)
{
	int	status;

	status = heredoc_read(str, fd);
	close(fd);
	if (status)
	{
		free(filename);
		return (status);
	}
	return (0);
}

int	heredoc(char **str, int index)
{
	char	*filename;
	int		fd;
	int		status;

	filename = heredoc_generate_name(index);
	if (!filename)
		return (EXIT_FAILURE);
	fd = open_heredoc_file(filename);
	if (fd < 0)
	{
		free(filename);
		return (EXIT_FAILURE);
	}
	status = handle_heredoc_read(*str, fd, filename);
	if (status)
		return (status);
	free(*str);
	*str = filename;
	return (0);
}
