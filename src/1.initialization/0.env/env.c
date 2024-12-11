/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:06:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/11 17:21:19 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

/*
** Copies the environment variables from envp into a new dynamically allocated
** array of strings. Ensures that the new array is NULL-terminated.
*/
char	**get_env(char **envp)
{
	char	**env;
	int		env_size;
	int		i;

	env_size = 0;
	while (envp[env_size])
		env_size++;
	env = ft_calloc(env_size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (i < env_size)
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			while (--i >= 0)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[env_size] = NULL;
	return (env);
}

/*
** Searches for a specific environment variable in envp. Returns a dynamically
** allocated string containing the full environment variable (name=value) if
** found, or NULL if not.
*/
char	*get_single_env(char *env_name, char **envp)
{
	int		i;
	int		env_len;

	if (!env_name || !envp)
		return (NULL);
	env_len = ft_strlen(env_name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(env_name, envp[i], env_len)
			&& (envp[i][env_len] == '=' || envp[i][env_len] == '\0'))
			return (ft_strdup(envp[i]));
		i++;
	}
	return (NULL);
}

/*
** Retrieves the value of a specific environment variable (everything after
** the '=' character) from envp. Returns a dynamically allocated string
** containing the value, or NULL if the variable is not found or has no value.
*/
char	*get_env_value(char *env_name, char **envp)
{
	char	*full_var_env;
	char	*value;

	if (!env_name || !envp)
		return (NULL);
	full_var_env = get_single_env(env_name, envp);
	if (!full_var_env)
		return (NULL);
	value = ft_strchr(full_var_env, '=');
	if (!value)
	{
		free(full_var_env);
		return (NULL);
	}
	value = ft_strdup(value + 1);
	free(full_var_env);
	return (value);
}

char	**insert_paths(char *paths)
{
	char	**split;
	char	*temp;
	int		i;

	if (!paths)
		return (NULL);
	split = ft_split(paths, ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		temp = split[i];
		split[i] = ft_strjoin(temp, "/");
		if (!split[i])
		{
			free(temp);
			while (--i >= 0)
				free(split[i]);
			free(split);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split);
}

/*
** Searches for the PATH variable in the environment array and uses insert_paths
** to process it into an array of paths.
*/
char	**get_paths(char **env)
{
	char	**temp;

	if (!env)
		return (NULL);
	temp = env;
	while (*temp)
	{
		if (!ft_strncmp("PATH=", *temp, 5))
			return (insert_paths(*temp + 5));
		temp++;
	}
	return (NULL);
}

char *validate_var_name(char *var)
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
