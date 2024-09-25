/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/09/25 19:40:20 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*create_operator_token(char *input, int *index)
{
	t_token	*token;
	int		i;
	char	op[3];

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	i = *index;
	// Treat operators with multiple characters (might be transferred to a separate function)
	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
	{
		op[0] = input[i++];
		op[1] = input[i++];
		op[2] = '\0';
	}
	else
	{
		op[0] = input[i++];
		op[1] = '\0';
	}
	token->value = ft_strdup(op);
	*index = i;
	// Define Token type based on operator
	if (ft_strcmp(token->value, "|") == 0)
		token->type = TOKEN_PIPE;
	else if (ft_strcmp(token->value, ">") == 0)
		token->type = TOKEN_REDIRECT_OUT;
	else if (ft_strcmp(token->value, ">>") == 0)
		token->type = TOKEN_REDIRECT_APPEND;
	else if (ft_strcmp(token->value, "<") == 0)
		token->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(token->value, "<<") == 0)
		token->type = TOKEN_HEREDOC;
	else
		token->type = TOKEN_OPERATOR;
	token->next = NULL;
	return (token);
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*new_token;
	t_token	*head;
	t_token	*current;

	i = 0;
	head = NULL;
	current = NULL;
	while (input[i] != '\0')
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (is_operator(input[i]))
			new_token = create_operator_token(input, &i);
		else
			new_token = create_word_token(input, &i); // to be created
		if (head == NULL)
		{
			head = new_token;
			current = new_token;
		}
		else
		{
			current->next = new_token;
			current = new_token;
		}
	}
	return (head);
}
