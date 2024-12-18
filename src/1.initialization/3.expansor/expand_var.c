/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:05:50 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 16:59:26 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Helper function to extract variable name
char *extract_var_name(const char *input_str, int *index)
{
    int start_index = *index;
    int var_len = 0;

    while (input_str[*index] &&
           (isalnum((unsigned char)input_str[*index]) || input_str[*index] == '_'))
    {
        (*index)++;
        var_len++;
    }

    return ft_substr(input_str, start_index, var_len);
}

static char *expand_special_parameter(const char *input_str, int *index, t_minishell *minishell)
{
    if (input_str[*index] == '?')
    {
        (*index)++;
        return ft_itoa(minishell->status);
    }
    (*index)++;
    return strdup("");
}

static char *get_variable_value(const char *input_str, int *index, t_minishell *minishell)
{
    char *var_name = extract_var_name(input_str, index);
    char *expanded_value;

    if (!var_name)
        return NULL;

    expanded_value = expand_env(var_name, minishell->envp); // Fetch environment variable
    free(var_name);
    return expanded_value;
}


char *expand_parameter(const char *input_str, int *index, t_minishell *minishell)
{
    // Check if the '$' is escaped
    if (*index > 0 && input_str[*index - 1] == '\\')
    {
        (*index)++; // Skip the escaped '$'
        return strdup("$"); // Treat as literal '$'
    }
    (*index)++; // Skip the '$'
    // Handle invalid variable names
    if (!input_str[*index] ||
        (!isalnum((unsigned char)input_str[*index]) &&
         input_str[*index] != '_' && input_str[*index] != '?'))
    {
        return strdup("$");
    }
    // Handle special parameters like '$?' or numeric variables
    if (input_str[*index] == '?' || isdigit((unsigned char)input_str[*index]))
        return expand_special_parameter(input_str, index, minishell);
    // Expand a regular variable
    return get_variable_value(input_str, index, minishell);
}
