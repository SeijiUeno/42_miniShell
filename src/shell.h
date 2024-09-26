/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/25 19:24:38 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
/* Include Readline */
# include <readline/readline.h>
# include <readline/history.h>
/* Include Signal */
# include <signal.h>
# include "../libft/includes/libft.h"

typedef enum s_token_type
{
	TOKEN_WORD, //0
	TOKEN_OPERATOR, // 1
	TOKEN_PIPE, // 2
	TOKEN_REDIRECT_IN, //3
	TOKEN_REDIRECT_OUT, //4
	TOKEN_REDIRECT_APPEND, //5 
	TOKEN_HEREDOC, // 6
	TOKEN_EOF // 7	
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

void	handle_sigint(int sig);
int		is_operator(char c);
void	signal_init(void);
t_token	*tokenizer(char *input);

#endif