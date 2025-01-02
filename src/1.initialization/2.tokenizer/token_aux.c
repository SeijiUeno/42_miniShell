/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:24:11 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

void	initialize_token_list(t_token **tokens)
{
	*tokens = (t_token *)gc_allocate(sizeof(t_token));
	if (!(*tokens))
	{
		perror("gc_allocate");
		exit(EXIT_FAILURE);
	}
	(*tokens)->type = -1;
	(*tokens)->content = NULL;
	(*tokens)->next = NULL;
	(*tokens)->prev = NULL;
}

void	append_token(t_token **token_list, t_token *new_token)
{
	t_token	*current;

	current = *token_list;
	if (!current)
	{
		*token_list = new_token;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

void	clear_tok(t_token **token_list)
{
	t_token	*current;
	t_token	*next_token;

	current = *token_list;
	while (current)
	{
		next_token = current->next;
		if (current->content)
		{
			gc_deallocate(current->content);
		}
		gc_deallocate(current);
		current = next_token;
	}
	*token_list = NULL;
}

void	skip_quoted_token(char *input, int *index)
{
	char	quote;

	quote = input[*index];
	(*index)++;
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
		(*index)++;
}

void	skip_whitespace(char *input, int *index)
{
	while (input[*index] && ft_strchr(WHITESPACE, input[*index]))
		(*index)++;
}
