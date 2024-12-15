/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:16:32 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 06:17:49 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

static int	handle_builtin(char **command, t_ms *minishell, size_t index)
{
	if (index == 0)
		return (change_dir(command, minishell));
	if (index == 1)
		return (echo(command));
	if (index == 2)
		return (print_env(command, minishell->envp, minishell));
	if (index == 3)
		return (buildin_export(command, minishell));
	if (index == 4)
		return (unset((const char **)command, minishell));
	if (index == 5)
		return (pwd(command, minishell));
	if (index == 6)
		return (builtin_exit(command, minishell));
	return (-1);
}

int	builtin_check(char **command, t_ms *minishell)
{
	size_t	i;

	static const char *builtins[] = {
		"cd",
		"echo",
		"env",
		"export",
		"unset",
		"pwd",
		"exit",
	};
	if (!command || !command[0])
		return (-1);
	i = 0;
	while (i < sizeof(builtins) / sizeof(builtins[0]))
	{
		if (ft_strncmp(command[0], builtins[i], ft_strlen(builtins[i])
				+ 1) == 0)
			return (handle_builtin(command, minishell, i));
		i++;
	}
	return (-1);
}
