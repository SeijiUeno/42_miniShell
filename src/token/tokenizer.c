/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:51:36 by emorales          #+#    #+#             */
/*   Updated: 2024/11/06 19:18:29 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (is_operator(input[i]))
			new_token = create_operator_token(input, &i);
		else
			new_token = create_word_token(input, &i);
		if (!new_token)
		{
			free_tokens(head);
			return (NULL);
		}
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

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
