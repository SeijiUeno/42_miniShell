/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/30 18:37:57 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	assign_operator_token_type(t_token *token)
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
		token->type = TOKEN_OPERATOR;
}

static void	extract_operator(char *input, int *i, char *op)
{
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		op[0] = input[(*i)++];
		op[1] = input[(*i)++];
		//op[2] = '\0';
	}
	else
	{
		op[0] = input[(*i)++];
		//op[1] = '\0';
	}
	op[2] = '\0'; //nesse caso, não seria melhor determinar o \0 na casa 2 pro caso 1 e na casa 1 pro caso 2?
}

t_token	*create_operator_token(char *input, int *index)
{
	t_token	*token;
	int		i;
	char	op[3];

	i = *index;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	extract_operator(input, &i, op);
	token->value = strdup(op);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	*index = i;
	assign_operator_token_type(token);
	token->next = NULL;
	return (token);
}
