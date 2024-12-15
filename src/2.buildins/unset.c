/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:11:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:21:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int is_key_in_envp(const char *key, t_ms *minishell)
{
    int i;

    if (!key || !minishell || !minishell->envp)
        return (EXIT_FAILURE);
    i = 0;
    while (minishell->envp[i])
    {
        if (ft_strncmp(minishell->envp[i], key, ft_strlen(key)) == 0 &&
            minishell->envp[i][ft_strlen(key)] == '=')
            return (EXIT_SUCCESS);
        i++;
    }
    return (EXIT_FAILURE);
}

static int get_filtered_envp_len(char **envp, const char *key)
{
    int i = 0;
    int count = 0;

    if (!envp || !key)
        return (0);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, ft_strlen(key)) != 0 ||
            envp[i][ft_strlen(key)] != '=')
            count++;
        i++;
    }
    return (count);
}

static int unset_env(const char *key, t_ms *minishell)
{
    int i = 0;
    int j = 0;
    int new_len;
    char **new_env;

    if (!key || !minishell || !minishell->envp)
        return (EXIT_FAILURE);
    new_len = get_filtered_envp_len(minishell->envp, key);
    new_env = (char **)malloc(sizeof(char *) * (new_len + 1));
    if (!new_env)
        return (EXIT_FAILURE);
    while (minishell->envp[i])
    {
        if (ft_strncmp(minishell->envp[i], key, ft_strlen(key)) != 0 ||
            minishell->envp[i][ft_strlen(key)] != '=')
        {
            new_env[j] = minishell->envp[i];
            j++;
        }
        else
            free(minishell->envp[i]);
        i++;
    }
    new_env[j] = NULL;
    free(minishell->envp);
    minishell->envp = new_env;
    return (EXIT_SUCCESS);
}

int unset(const char **keys, t_ms *minishell)
{
    int status_error = 0;
    char **key_iter;

    if (!keys || !keys[1])
        return (status_error);
    key_iter = (char **)(keys + 1);
    while (*key_iter)
    {
        if (var_validate_name(*key_iter))
        {
            status_error = error(*key_iter, ": not a valid identifier", 1);
        }
        else if (is_key_in_envp(*key_iter, minishell) == EXIT_SUCCESS)
        {
            unset_env(*key_iter, minishell);
        }
        key_iter++;
    }
    util_free_array(minishell->path);
    minishell->path = get_paths(minishell->envp);
    return (status_error);
}