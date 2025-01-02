/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:21:56 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:24:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	update_pwd_env(char **envp, const char *key, const char *value)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			gc_deallocate(envp[i]);
			envp[i] = ft_strjoin(key, value);
			return ;
		}
		i++;
	}
}

static void	aux(char *current_path, char *old_pwd, t_ms *m)
{
	update_pwd_env(m->envp, "OLDPWD=", old_pwd);
	update_pwd_env(m->envp, "PWD=", current_path);
}

void	update_pwd(t_ms *m)
{
	char	*current_path;
	char	*old_pwd;
	int		i;

	current_path = getcwd(NULL, 0);
	old_pwd = NULL;
	i = 0;
	if (!current_path)
	{
		m->status = 1;
		return ;
	}
	while (m->envp[i])
	{
		if (ft_strncmp(m->envp[i], "PWD=", 4) == 0)
		{
			old_pwd = ft_strdup(m->envp[i] + 4);
			break ;
		}
		i++;
	}
	aux(current_path, old_pwd, m);
	free(current_path);
	gc_deallocate(old_pwd);
	m->status = 0;
}
