/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:14:10 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 17:34:31 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int ft_is_number(const char *str)
{
    int i;

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

static int calculate_exit_code(const char *arg)
{
    int number;

    number = ft_atoi(arg);
    if (number < 0 || number > 255)
        return (number % 256);
    return (number);
}

static void set_exit_code(char **args, t_minishell *minishell)
{
    int exit_code;

    if (!args[1])
        exit_code = minishell->status;
    else if (ft_is_number(args[1]))
        exit_code = calculate_exit_code(args[1]);
    else
    {
        ft_putstr_fd("ERROR: exit: ", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit_code = 2;
    }

    free_all(minishell);
    exit(exit_code);
}

int exit_builtin(char **args, t_minishell *minishell)
{
    int arg_count;

    ft_putstr_fd("exit\n", STDERR_FILENO);

    // Count the number of arguments
    arg_count = 0;
    while (args[arg_count])
        arg_count++;

    if (arg_count > 2 && ft_is_number(args[1]))
    {
        ft_putstr_fd("ERROR: exit: too many arguments\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }

    set_exit_code(args, minishell);
    return (EXIT_SUCCESS); // This won't be reached due to exit()
}
