/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:52 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 21:07:04 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// token_utils.c

void	initialize_token_list(t_token **tokens)
{
	*tokens = (t_token *)malloc(sizeof(t_token));
	if (!(*tokens))
	{
		perror("malloc");
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
	if (!current) // If the list is empty
	{
		*token_list = new_token;
		return ;
	}
	while (current->next) // Traverse to the end of the list
		current = current->next;
	current->next = new_token; // Append the new token
	new_token->prev = current; // Set the backward link
}

// Free all tokens in the list
void	free_all_tokens(t_token **token_list)
{
	t_token	*current;
	t_token	*next_token;

	current = *token_list;
	// Iterate through the list and free each token
	while (current) {
		next_token = current->next; // Save the next token
		if (current->content) {
			free(current->content); // Free the token's content
		}
		free(current);             // Free the token itself
		current = next_token;      // Move to the next token
	}
	*token_list = NULL; // Set the list pointer to NULL after freeing
}

void	skip_quoted_token(char *input, int *index)
{
	char	quote;

	quote = input[*index];
	(*index)++; // Skip opening quote
	while (input[*index] && input[*index] != quote)
		(*index)++;
	if (input[*index] == quote)
		(*index)++; // Skip closing quote
}

void	skip_whitespace(char *input, int *index)
{
	while (input[*index] && ft_strchr(WHITESPACE, input[*index]))
		(*index)++;
}