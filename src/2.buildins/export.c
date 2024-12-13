/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:44:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 18:46:21 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	util_swap_array(char **wordA, char **wordB)
{
	char	*temp;

	if (!wordA || !wordB || !(*wordA) || !(*wordB))
		return ;
	temp = *wordA;
	*wordA = *wordB;
	*wordB = temp;
}

char	*validate_env_var_name(const char *var)
{
	int	i;

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

static int	calculate_name_size(const char *text, char delimiter)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != delimiter)
		i++;
	return (i);
}

static int	is_env_var_existing(char *var, t_minishell *minishell)
{
	char	**envp;
	int		name_len;
	int		i;

	envp = minishell->envp;
	name_len = calculate_name_size(var, '=');
	i = 0;
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

static void	insert_env_var(char *var, t_minishell *minishell)
{
	char	**new_envp;
	int		env_size;
	int		i;

	env_size = 0;
	i = 0;
	if (is_env_var_existing(var, minishell))
		return ;
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

static void	sort_env_vars(char **envp)
{
	int	i;
	int	j;

	i = 0;
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

static void	print_sorted_env_vars(char **envp)
{
	char	**sorted_env;
	int		i;
	char	*equal_sign;

	sorted_env = get_env(envp);
	i = 0;
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

int	buildin_export(char **args, t_minishell *minishell)
{
	int		i;
	int		error_status;
	char	*invalid_var;

	i = 1;
	error_status = 0;
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
