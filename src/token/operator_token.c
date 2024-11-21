/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/31 17:00:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

#include "tokenizer.h"
#include <stdlib.h>
#include <string.h>

static void assign_operator_token_type(t_token *token)
{
    if (strcmp(token->value, "|") == 0)
        token->type = TOKEN_PIPE;
    else if (strcmp(token->value, ">") == 0)
        token->type = TOKEN_REDIRECT_OUT;
    else if (strcmp(token->value, ">>") == 0)
        token->type = TOKEN_REDIRECT_APPEND;
    else if (strcmp(token->value, "<") == 0)
        token->type = TOKEN_REDIRECT_IN;
    else if (strcmp(token->value, "<<") == 0)
        token->type = TOKEN_HEREDOC;
    else
        token->type = TOKEN_OPERATOR; // Default case
}

static void extract_operator(char *input, int *i, char *op)
{
    op[0] = '\0';
    op[1] = '\0';
    if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<' && input[*i + 1] == '<'))
    {
        op[0] = input[(*i)++];
        op[1] = input[(*i)++];
    }
    else
    {
        op[0] = input[(*i)++];
    }
    op[2] = '\0'; // Null-terminate the string
}

t_token *create_operator_token(char *input, int *index)
{
    t_token *token;
    int i;
    char op[3];

    i = *index;
    token = malloc(sizeof(t_token)); // Allocate memory for the token
    if (!token)
        return NULL; // Return NULL if allocation fails

    extract_operator(input, &i, op); // Extract operator from input
    token->value = strdup(op); // Duplicate the operator string
    if (!token->value)
    {
        free(token); // Free memory on failure
        return NULL;
    }
    *index = i; // Update the index
    assign_operator_token_type(token); // Set token type
    token->next = NULL; // Initialize next to NULL
    return token; // Return created token
}
