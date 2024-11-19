/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:46 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/29 16:47:33 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

const char *get_token_type_name(t_token_type type)
{
    if (type == TOKEN_WORD)
        return "TOKEN_WORD";
    else if (type == TOKEN_OPERATOR)
        return "TOKEN_OPERATOR";
    else if (type == TOKEN_PIPE)
        return "TOKEN_PIPE";
    else if (type == TOKEN_REDIRECT_IN)
        return "TOKEN_REDIRECT_IN";
    else if (type == TOKEN_REDIRECT_OUT)
        return "TOKEN_REDIRECT_OUT";
    else if (type == TOKEN_REDIRECT_APPEND)
        return "TOKEN_REDIRECT_APPEND";
    else if (type == TOKEN_HEREDOC)
        return "TOKEN_HEREDOC";
    else
        return "UNKNOWN";
}

// Function to print tokens
void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	printf("-----TOKENS-----\n");
	while (current != NULL)
	{
		printf("Token Value: '%s', Token Type: %s\n", current->value, get_token_type_name(current->type));
		current = current->next;
	}
	printf("-----END-----\n");
}
