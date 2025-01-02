/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:22:39 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 15:22:46 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

	sorted_env = get_env(envp);
	sort_env_vars(sorted_env);
	i = 0;
	while (sorted_env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted_env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	util_free_array(sorted_env);
}

static void	print_er(char *arg, t_ms *m)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	m->status = 1;
}

int	buildin_export(char **args, t_ms *minishell)
{
	int		i;
	char	*invalid_var;

	if (!args[1])
	{
		print_sorted_env_vars(minishell->envp);
		return (0);
	}
	i = 0;
	minishell->status = 0;
	while (args[++i])
	{
		invalid_var = validate_env_var_name(args[i]);
		if (invalid_var)
			print_er(args[i], minishell);
		else
			insert_env_var(args[i], minishell);
	}
	util_free_array(minishell->path);
	minishell->path = get_paths(minishell->envp);
	return (minishell->status);
}
