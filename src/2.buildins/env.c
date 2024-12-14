/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:16:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 17:20:14 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int print_env(char **args, char **envp, t_minishell *m) {
    char **temp;

    if (args[1] != NULL) {
        ft_putstr_fd("env: \"", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("\" File or directory not found\n", STDERR_FILENO);
        m->status = 1;
        return (1); // Return 1 for invalid usage
    }
    temp = envp;
    while (*temp != NULL) {
        if (ft_strchr(*temp, '=')) {
            ft_putstr_fd(*temp, STDOUT_FILENO);
            ft_putchar_fd('\n', STDOUT_FILENO);
        }
        temp++;
    }
    m->status = 0; // Success
    return (0);
}
