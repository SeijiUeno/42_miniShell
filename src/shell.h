/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:20:34 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include <errno.h>
#include <limits.h>
#include <unistd.h> // For STDOUT_FILENO and getcwd
#include <stdlib.h> // For EXIT_FAILURE and EXIT_SUCCESS
/* Include Readline */
# include <readline/readline.h>
# include <readline/history.h>
/* Include Signal */
# include <signal.h>
/* Include lib */

/* Include env */
#include "../env/env.h"

# include "token/tokenizer.h"
# include "execution/execution.h"

# define STATUS_GET -1
# define STATUS_SIGINT 130
# define STATUS_SIGQUIT 131

typedef struct s_minishell	t_minishell;

struct s_minishell
{
	int			status;
	char		*input;
	char		**envp;
	char		**path;
	int			stdin_backup;
	int			stdout_backup;
	t_token		*tokens;
	t_command	*tree_cmd;
};

#endif