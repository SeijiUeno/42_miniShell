/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:16:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 19:27:19 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int env(const char **args)
{
    t_env_list *env_list;
    t_env_list *current;

    // Check for unexpected arguments
    if (args && args[1])
    {
        ft_putendl_fd("minishell: env doesn't accept arguments or flags", STDERR_FILENO);
        return EXIT_FAILURE;
    }

    // Retrieve the environment list
    env_list = environ_list_holder(NULL, 0);
    if (!env_list)
    {
        ft_putendl_fd("minishell: environment is empty or uninitialized", STDERR_FILENO);
        return EXIT_FAILURE;
    }

    // Iterate and print environment variables
    current = env_list;
    while (current)
    {
        if (current->key && current->value)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putendl_fd(current->value, STDOUT_FILENO);
        }
        current = current->next;
    }
    return EXIT_SUCCESS;
}
