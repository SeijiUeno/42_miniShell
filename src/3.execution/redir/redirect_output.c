/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:43:05 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 19:16:34 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	redirect_output(char *filename)
{
	int	fd;

	fd = open_file(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (EXIT_FAILURE);
	return (redirect_fd(fd, STDOUT_FILENO));
}

int	append_output(char *filename)
{
	int	fd;

	fd = open_file(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (EXIT_FAILURE);
	return (redirect_fd(fd, STDOUT_FILENO));
}
