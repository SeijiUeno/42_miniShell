/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:51 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 18:24:56 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	check_args_minus_n(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

int	echo(char **args)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	while (args[i] && check_args_minus_n(args[i]))
	{
		print_newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
