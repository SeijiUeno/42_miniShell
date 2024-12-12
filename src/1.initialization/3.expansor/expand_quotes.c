/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:00:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 16:07:15 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

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
