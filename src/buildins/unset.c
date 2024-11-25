/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:11:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 19:35:01 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int is_valid_identifier(const char *identifier)
{
    if (*identifier != '=' && !ft_isdigit(*identifier))
    {
        while (*identifier && *identifier != '=' &&
               (ft_isalnum(*identifier) || *identifier == '_'))
            identifier++;
        if (*identifier == '=' || !*identifier)
            return 1;
    }
    ft_putendl_fd("minishell: export: not a valid identifier", 2);
    last_exit_status(1);
    return 0;
}

void ft_unsetenv(const char *name)
{
    t_env_list *env_list;

    env_list = environ_list_holder(NULL, 0);
    remove_env_variable(&env_list, name);
    environ_list_holder(env_list, 0); // Update the holder
}

int unset(char **args)
{
    int   arg_index;
    int   exit_status;

    exit_status = EXIT_SUCCESS;
    arg_index = 1;
    while (args[arg_index])
    {
        if (is_valid_identifier(args[arg_index]))
            ft_unsetenv(args[arg_index]);
        else
            exit_status = EXIT_FAILURE;
        arg_index++;
    }
    return exit_status;
}