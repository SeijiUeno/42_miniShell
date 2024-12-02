/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/02 17:09:25 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansor.h"

// Function to expand special parameters
char *expand_num_or_status(const char *input_str, int *index, t_minishell *minishell)
{
    if (input_str[*index] == '?')
    {
        (*index)++;
        return ft_itoa(minishell->status);
    }
    (*index)++;
    return strdup("");
}

// Function to expand until a specific character
char *expand_until_char(const char *input_str, int *index, char stop_char)
{
    int start_index = *index;
    int len = 0;

    while (input_str[*index] && input_str[*index] != stop_char && input_str[*index] != '$')
    {
        (*index)++;
        len++;
    }

    return ft_substr(input_str, start_index, len);
}

// Function to expand double-quoted strings
char *expand_double_quotes(const char *input_str, int *index, t_minishell *minishell)
{
    char *result = NULL;
    char *temp_str;

    if (input_str[*index] == '"')
        (*index)++;

    while (input_str[*index] && input_str[*index] != '"')
    {
        if (input_str[*index] == '$')
            temp_str = expand_parameter(input_str, index, minishell);
        else
            temp_str = expand_until_char(input_str, index, '"');

        if (!temp_str)
        {
            free(result);
            return NULL;
        }

        result = join_word(result, temp_str);
        if (!result)
            return NULL;
    }

    if (input_str[*index] == '"')
        (*index)++;

    return result;
}

// Function to expand words outside quotes
char *expand_word(const char *input_str, int *index)
{
    int start_index = *index;
    int len = 0;

    while (input_str[*index] && !strchr(QUOTES, input_str[*index]) &&
           input_str[*index] != '$')
    {
        (*index)++;
        len++;
    }

    return ft_substr(input_str, start_index, len);
}
