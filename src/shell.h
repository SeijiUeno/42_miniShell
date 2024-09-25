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

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

char	*ft_strdup(char *src);
void	handle_sigint(int sig);
int		is_operator(char c);
void	signal_init(void);
t_token	*tokenizer(char *input);

#endif