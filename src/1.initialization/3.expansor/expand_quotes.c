/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:00:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 03:36:13 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

/**
 * Removes tokens containing "$EMPTY" from the token list.
 * If a "$EMPTY" token is found, the function removes it
 * and returns NULL.
 * @param tokens - Pointer to the root of the token list.
 * @return Updated root of the token list, or NULL if "$EMPTY" was found and removed.
 */
/**
 * Removes tokens containing "$EMPTY" from the token list.
 * If a "$EMPTY" token is found, it is removed, and the list is updated.
 * @param tokens - Pointer to the root of the token list.
 * @return Updated root of the token list.
 */
t_token *remove_empty_tokens(t_token **tokens)
{
	t_token *current;
	t_token *temp;

	if (!tokens || !*tokens)
		return (*tokens); // Return the same list if empty or NULL

	current = *tokens;
	while (current)
	{
		// Check if the token content matches "$EMPTY"
		if (current->content && strcmp(current->content, "$EMPTY") == 0)
		{
			temp = current->next; // Save the next token
			remove_token_from_list(tokens, current); // Remove the current token
			current = temp; // Move to the next token
			continue; // Skip further processing of the removed node
		}
		current = current->next;
	}
	return (*tokens); // Return the updated root of the token list
}


// Function to expand single-quoted strings
char *expand_single_quotes(const char *input_str, int *index)
{
    int start_index;
    int len = 0;
    
    if (input_str[*index] == '\'')
        (*index)++;

    start_index = *index;

    while (input_str[*index] && input_str[*index] != '\'')
    {
        (*index)++;
        len++;
    }

    if (input_str[*index] == '\'')
        (*index)++;

    return ft_substr(input_str, start_index, len);
}

static char *handle_escape_sequence(const char *input_str, int *index)
{
    if (input_str[*index] == '\\' && input_str[*index + 1] == '$')
    {
        *index += 2;
        return strdup("$");
    }
    return NULL;
}

static char *process_inside_quotes(const char *input_str, int *index, t_minishell *minishell)
{
    char *temp_str = handle_escape_sequence(input_str, index);
    if (temp_str)
        return temp_str;

    if (input_str[*index] == '$')
        return expand_parameter(input_str, index, minishell);

    return expand_until_char(input_str, index, '"');
}

char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell)
{
    char *result = NULL, *temp_str;

    if (input_str[*index] == '"')
        (*index)++;
    if (input_str[*index] == '"')
        (*index)++;

    while (input_str[*index] && input_str[*index] != '"')
    {
        temp_str = process_inside_quotes(input_str, index, minishell);
        if (!temp_str || !(result = join_word(result, temp_str)))
        {
            free(result);
            return NULL;
        }
    }

    if (input_str[*index] == '"')
        (*index)++;

    return result;
}
