/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 18:13:53 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef s_minishell t_myShell;

struct s_minishell
{
	int			status;
	char		*input;
	char		**env;
	char		**path;
	int			stdin_backup;
	int			stdout_backup;
	t_token		*tokens;
	t_command	*tree_cmd;
	t_list		*pid_list;
};