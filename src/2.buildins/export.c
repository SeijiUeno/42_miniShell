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

void util_swap_array(char **wordA, char **wordB)
{
    if (!wordA || !wordB || !(*wordA) || !(*wordB))
        return;

    char *temp = *wordA;
    *wordA = *wordB;
    *wordB = temp;
}

char *validate_env_var_name(const char *var)
{
    int i;

    if (!var || !(ft_isalpha(var[0]) || var[0] == '_'))
        return ((char *)var);
    i = 1;
    while (var[i] && var[i] != '=')
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return ((char *)var);
        i++;
    }
    return (NULL);
}

static int calculate_name_size(const char *text, char delimiter)
{
    int i = 0;

    while (text[i] && text[i] != delimiter)
        i++;
    return (i);
}

static int is_env_var_existing(char *var, t_minishell *minishell)
{
    char **envp = minishell->envp;
    int name_len = calculate_name_size(var, '=');
    int i = 0;

    while (envp[i])
    {
        if (!ft_strncmp(envp[i], var, name_len) && envp[i][name_len] == '=')
        {
            free(envp[i]);
            envp[i] = ft_strdup(var);
            return (1);
        }
        i++;
    }
    return (0);
}

static void insert_env_var(char *var, t_minishell *minishell)
{
    char **new_envp;
    int env_size = 0;
    int i = 0;

    if (is_env_var_existing(var, minishell))
        return;
    while (minishell->envp[env_size])
        env_size++;
    new_envp = calloc(env_size + 2, sizeof(char *));
    while (i < env_size)
    {
        new_envp[i] = minishell->envp[i];
        i++;
    }
    new_envp[i] = ft_strdup(var);
    new_envp[i + 1] = NULL;
    free(minishell->envp);
    minishell->envp = new_envp;
}

static void sort_env_vars(char **envp)
{
    int i = 0;
    int j;

    while (envp[i])
    {
        j = i + 1;
        while (envp[j])
        {
            if (ft_strcmp(envp[i], envp[j]) > 0)
                util_swap_array(&envp[i], &envp[j]);
            j++;
        }
        i++;
    }	
}

static void print_sorted_env_vars(char **envp)
{
    char **sorted_env = get_env(envp);
    int i = 0;
    char *equal_sign;

    sort_env_vars(sorted_env);
    while (sorted_env[i])
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        equal_sign = ft_strchr(sorted_env[i], '=');
        if (equal_sign)
        {
            ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        else
        {
            ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        i++;
    }
    util_free_array(sorted_env);
}

int buildin_export(char **args, t_minishell *minishell)
{
    int i = 1;
    int error_status = 0;
    char *invalid_var;

    if (!args[1])
    {
        print_sorted_env_vars(minishell->envp);
        return (0);
    }
    while (args[i])
    {
        invalid_var = validate_env_var_name(args[i]);
        if (invalid_var)
        {
            ft_putstr_fd("buildin_export: `", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            error_status = 1;
        }
        else
        {
            insert_env_var(args[i], minishell);
        }
        i++;
    }
    util_free_array(minishell->path);
    minishell->path = get_paths(minishell->envp);
    return (error_status);
}