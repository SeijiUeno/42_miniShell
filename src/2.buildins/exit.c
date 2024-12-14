/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 18:11:12 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	ft_is_number(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0); // Empty string is not a number
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0); // String is just "+" or "-"
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

static void	display_exit_error(const char *arg, const char *message,
		int exit_code, t_minishell *minishell)
{
	ft_putstr_fd("ERROR: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	minishell->status = exit_code;
	free_all(minishell);
	exit(exit_code);
}

static void	handle_exit_arguments(char **args, t_minishell *minishell)
{
	if (!args[1])
		minishell->status = 0;
	else if (ft_is_number(args[1]))
		minishell->status = calculate_exit_code(args[1]);
	else
		display_exit_error(args[1], ": numeric argument required\n", 2,
			minishell);
}

int	builtin_exit(char **args, t_minishell *minishell)
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
	free_all(minishell);
	exit(minishell->status);
	return (EXIT_SUCCESS);
}
