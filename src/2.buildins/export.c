/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:44:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 19:41:32 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static void sort_env_vars(char **envp) {
    int i;
    int j;

    i = 0;
    while (envp[i]) {
        j = i + 1;
        while (envp[j]) {
            if (ft_strcmp(envp[i], envp[j]) > 0)
                util_swap_array(&envp[i], &envp[j]);
            j++;
        }
        i++;
    }
}

static void print_sorted_env_vars(char **envp) {
    char **sorted_env;
    int i;

    sorted_env = get_env(envp);
    sort_env_vars(sorted_env);
    i = 0;
    while (sorted_env[i]) {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        i++;
    }
    util_free_array(sorted_env);
}

int buildin_export(char **args, t_ms *minishell) {
    int i;
    char *invalid_var;

    if (!args[1]) {
        print_sorted_env_vars(minishell->envp);
        return (0);
    }
    i = 1;
    minishell->status = 0;
    while (args[i]) {
        invalid_var = val_e_v(args[i]);
        if (invalid_var) {
            ft_putstr_fd("export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            minishell->status = 1;
        } else {
            insert_env_var(args[i], minishell);
        }
        i++;
    }
    util_free_array(minishell->path);
    minishell->path = get_paths(minishell->envp);
    return (minishell->status);
}
