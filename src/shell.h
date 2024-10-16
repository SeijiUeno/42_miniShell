/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/14 19:20:56 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* Include Readline */
#include "token/tokenizer.h"

/* Include Readline */
# include <readline/readline.h>
# include <readline/history.h>

/* Include Signal */
# include <signal.h>
# include "../libft/includes/libft.h"

typedef struct s_minishell
{
	char		**env;
	char		**path;

}t_minishell;

#endif