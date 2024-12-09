/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:33:38 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:17:52 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

#include "../shell.h"
#include "../token/tokenizer.h"

typedef struct s_command	t_command;

struct s_command
{
	char				**argv;
	t_token				*redir;
	int					argc;
	int					fd[2];
	int					type;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*parent;
};

#endif
