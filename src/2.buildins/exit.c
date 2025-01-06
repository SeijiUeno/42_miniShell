/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:10 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/06 19:02:22 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	ft_is_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	calculate_exit_code(const char *arg)
{
	int	number;

	number = ft_atoi(arg);
	if (number < 0 || number > 255)
		return (number % 256);
	return (number);
}

static void	d_error(const char *arg,
		const char *message,
		int exit_code, t_ms *minishell)
{
	ft_putstr_fd("ERROR: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	minishell->status = exit_code;
	clear_al(minishell);
	exit(exit_code);
}

static void	handle_exit_arguments(char **args, t_ms *minishell)
{
	if (!args[1])
		minishell->status = 0;
	else if (ft_is_number(args[1]))
		minishell->status = calculate_exit_code(args[1]);
	else
		d_error(args[1],
			": numeric argument required\n", 2, minishell);
}

int	builtin_exit(char **args, t_ms *minishell)
{
	int	arg_count;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2 && ft_is_number(args[1]))
	{
		minishell->status = 1;
		ft_putstr_fd("ERROR: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	handle_exit_arguments(args, minishell);
	clear_al(minishell);
	exit(minishell->status);
	return (EXIT_SUCCESS);
}
