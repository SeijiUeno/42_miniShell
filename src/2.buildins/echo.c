/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:51 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 18:46:42 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	check_args_minus_n(const char *arg)
{
	int	i;

	if (!arg || ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 2;
	while (arg[i] == 'n')
	{
		if (arg[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
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
