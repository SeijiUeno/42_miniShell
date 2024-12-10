/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:16:32 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:51:30 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static int	handle_builtin(char **command, t_minishell *minishell, size_t index)
{
	if (index == 0)
		return (change_dir(command, minishell));
	if (index == 1)
		return (echo(command));
	if (index == 2)
		return (print_env(minishell->envp));
	if (index == 3)
		return (export(command, minishell));
	if (index == 4)
		return (unset((const char **)command, minishell));
	if (index == 5)
		return (pwd());
	if (index == 6)
		return (exit_builtin(command, minishell));
	return (-1);
}

int	is_builtin(char **command, t_minishell *minishell)
{
	static const char	*builtins[] = {
		"cd",
		"echo",
		"env",
		"export",
		"unset",
		"pwd",
		"exit",
	};
	size_t				i;

	if (!command || !command[0])
		return (-1);
	i = 0;
	while (i < sizeof(builtins) / sizeof(builtins[0]))
	{
		if (ft_strncmp(command[0], builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (handle_builtin(command, minishell, i));
		i++;
	}
	return (-1);
}
