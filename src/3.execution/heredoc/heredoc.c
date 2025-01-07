/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:26:58 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/07 20:12:28 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	heredoc(char **str, int index)
{
	char	*filename;
	int		fd;
	int		status;

	filename = heredoc_generate_name(index);
	if (!filename)
		return (EXIT_FAILURE);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Failed to open heredoc file", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	status = heredoc_read(*str, fd);
	close(fd);
	if (status != 0)
	{
		if (g_in_subprocess == SUBPROCESS_INT_HDOC)
			return (130);
		ft_putchar_fd('\n', 1);
	}
	*str = filename;
	return (0);
}
