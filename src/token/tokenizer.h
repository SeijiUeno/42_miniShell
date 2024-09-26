/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:57 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/26 17:42:58 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "../shell.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// Function prototypes
t_token *tokenizer(char *input);
void free_tokens(t_token *head);

// From operator_token.c
t_token *create_operator_token(char *input, int *index);

// From word_token.c
t_token *create_word_token(char *input, int *index);

// From utils.c
int is_operator(char c);

#endif // TOKENIZER_H
