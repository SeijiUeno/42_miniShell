/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:20:48 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 18:23:14 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int is_env_var_existing(char *var, t_minishell *minishell) {
    char **envp;
    int name_len;
    int i;

    envp = minishell->envp;
    name_len = calculate_name_size(var, '=');
    i = 0;
    while (envp[i]) {
        if (!ft_strncmp(envp[i], var, name_len) && envp[i][name_len] == '=') {
            free(envp[i]);
            envp[i] = ft_strdup(var);
            return (1);
        }
        i++;
    }
    return (0);
}

static char *prepare_env_var(char *var) {
    if (!ft_strchr(var, '='))
        return (ft_strjoin(var, "="));
    return (ft_strdup(var));
}

static char **resize_envp(char **envp, int new_size) {
    char **new_envp;
    int i;

    new_envp = calloc(new_size + 1, sizeof(char *));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (i < new_size) {
        new_envp[i] = envp[i];
        i++;
    }
    return (new_envp);
}

void insert_env_var(char *var, t_minishell *minishell) {
    char **new_envp;
    char *prepared_var;
    int env_size;

    prepared_var = prepare_env_var(var);
    if (is_env_var_existing(prepared_var, minishell)) {
        free(prepared_var);
        return;
    }
    env_size = 0;
    while (minishell->envp[env_size])
        env_size++;
    new_envp = resize_envp(minishell->envp, env_size + 1);
    if (!new_envp) {
        free(prepared_var);
        return;
    }
    new_envp[env_size] = prepared_var;
    new_envp[env_size + 1] = NULL;
    free(minishell->envp);
    minishell->envp = new_envp;
}
