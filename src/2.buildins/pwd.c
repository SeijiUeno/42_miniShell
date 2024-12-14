/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:16:00 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 18:02:05 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	pwd(char **args, t_minishell *m)
{
	char	*cwd;

	(void)args;
	(void)m;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (error("pwd", "failed to get current directory", 1));
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
	return (0);
}
