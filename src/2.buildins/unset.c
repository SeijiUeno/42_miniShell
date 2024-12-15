/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:11:01 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 06:29:51 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	is_key_in_envp(const char *key, t_ms *minishell)
{
	int	i;

	if (!key || !minishell || !minishell->envp)
		return (EXIT_FAILURE);
	i = 0;
	while (minishell->envp[i])
	{
		if (ft_strncmp(minishell->envp[i], key, ft_strlen(key)) == 0
			&& minishell->envp[i][ft_strlen(key)] == '=')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

static int	get_filtered_envp_len(char **envp, const char *key)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!envp || !key)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) != 0
			|| envp[i][ft_strlen(key)] != '=')
			count++;
		i++;
	}
	return (count);
}

static char	**filter_envp(const char *key, char **envp)
{
	char	**new_env;
	int		new_len;
	int		src_idx;
	int		dest_idx;

	if (!key || !envp)
		return (NULL);
	new_len = get_filtered_envp_len(envp, key);
	new_env = (char **)malloc(sizeof(char *) * (new_len + 1));
	if (!new_env)
		return (NULL);
	src_idx = 0;
	dest_idx = 0;
	while (envp[src_idx])
	{
		if (ft_strncmp(envp[src_idx], key, ft_strlen(key)) != 0
			|| envp[src_idx][ft_strlen(key)] != '=')
			new_env[dest_idx++] = envp[src_idx];
		else
			free(envp[src_idx]);
		src_idx++;
	}
	new_env[dest_idx] = NULL;
	return (new_env);
}

static int	unset_env(const char *key, t_ms *minishell)
{
	char	**new_env;

	if (!key || !minishell || !minishell->envp)
		return (EXIT_FAILURE);
	new_env = filter_envp(key, minishell->envp);
	if (!new_env)
		return (EXIT_FAILURE);
	free(minishell->envp);
	minishell->envp = new_env;
	return (EXIT_SUCCESS);
}

int	unset(const char **keys, t_ms *minishell)
{
	int		status_error;
	char	**key_iter;

	status_error = 0;
	if (!keys || !keys[1])
		return (status_error);
	key_iter = (char **)(keys + 1);
	while (*key_iter)
	{
		if (var_validate_name(*key_iter))
			status_error = error(*key_iter, ": not a valid identifier", 1);
		else if (is_key_in_envp(*key_iter, minishell) == EXIT_SUCCESS)
			unset_env(*key_iter, minishell);
		key_iter++;
	}
	util_free_array(minishell->path);
	minishell->path = get_paths(minishell->envp);
	return (status_error);
}
