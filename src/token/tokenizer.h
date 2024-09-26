/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:57 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/26 18:16:02 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../shell.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

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

// Function prototypes
t_token *tokenizer(char *input);
void free_tokens(t_token *head);

// From operator_token.c
t_token *create_operator_token(char *input, int *index);

// From word_token.c
t_token *create_word_token(char *input, int *index);

// From utils.c
int is_operator(char c);

//testing
const char *get_token_type_name(t_token_type type);
void print_tokens(t_token *head);

#endif // TOKENIZER_H
