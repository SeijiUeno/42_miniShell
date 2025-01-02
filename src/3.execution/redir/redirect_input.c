/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:42:45 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 13:14:25 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	redirect_input(char *filename)
{
	int	fd;

	fd = open_file(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		return (EXIT_FAILURE);
	}
	return (redirect_fd(fd, STDIN_FILENO));
}
