/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:38:03 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:51:39 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static int	is_current_or_empty_dir(const char *path)
{
	if (!path || *path == '\0' || !ft_strncmp(path, ".", ft_strlen(".") + 1))
		return (1);
	return (0);
}

static int	display_cd_error(const char *path, const char *error_msg)
{
	if (error_msg)
		ft_fdprintf(STDERR_FILENO, "cd: %s\n", error_msg);
	else if (path)
		ft_fdprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
	return (EXIT_FAILURE);
}

static void	update_environment_pwd(t_minishell *minishell, const char *old_pwd)
{
	char	*new_pwd;
	char	**env_update;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_fdprintf(STDERR_FILENO, "cd: error retrieving current directory\n");
		return ;
	}
	env_update = malloc(sizeof(char *) * 4);
	if (!env_update)
	{
		free(new_pwd);
		ft_fdprintf(STDERR_FILENO, "cd: memory allocation error\n");
		return ;
	}
	env_update[0] = ft_strdup("export");
	env_update[1] = ft_strjoin("PWD=", new_pwd);
	env_update[2] = ft_strjoin("OLDPWD=", old_pwd);
	env_update[3] = NULL;
	export(env_update, minishell);
	free_arr(env_update);
	free(new_pwd);
}

static int	change_to_directory(const char *path, t_minishell *minishell)
{
	char	*full_path;
	char	*home;
	char	*old_pwd;

	full_path = NULL;
	home = getenv("HOME");
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (display_cd_error(path, "error retrieving current directory"));

	if (!path || !ft_strncmp(path, "~", ft_strlen("~") + 1))
		path = home;
	else if (path[0] == '~' && path[1] == '/')
		full_path = ft_strjoin(home, path + 1);

	if (chdir(full_path ? full_path : path) == -1)
	{
		free(full_path);
		free(old_pwd);
		return (display_cd_error(path, NULL));
	}
	update_environment_pwd(minishell, old_pwd);
	free(full_path);
	free(old_pwd);
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **args, t_minishell *minishell)
{
	if (!args || !args[0])
		return (display_cd_error(NULL, "missing argument"));
	if (args[1] && args[2])
		return (display_cd_error(NULL, "too many arguments"));
	if (args[1] && is_current_or_empty_dir(args[1]))
		return (EXIT_SUCCESS);
	return (change_to_directory(args[1], minishell));
}
