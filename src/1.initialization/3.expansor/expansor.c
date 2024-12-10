/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:45:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 19:58:20 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Static function prototypes
static char *expand_single_quotes(const char *input_str, int *index);
static char *extract_var_name(const char *input_str, int *index);

// Function to expand variables and quotes
char *expand_vars_and_quotes(const char *input_str, t_minishell *minishell)
{
    char *result = NULL;
    char *temp_str;
    int index = 0;

    while (input_str[index])
    {
        if (input_str[index] == '\'')
            temp_str = expand_single_quotes(input_str, &index);
        else if (input_str[index] == '"')
            temp_str = expand_double_quotes(input_str, &index, minishell);
        else if (input_str[index] == '$')
            temp_str = expand_parameter(input_str, &index, minishell);
        else
            temp_str = expand_word(input_str, &index);

        if (!temp_str)
        {
            free(result);
            return NULL;
        }

        result = join_word(result, temp_str);
        if (!result)
            return NULL;
    }

    return result;
}

// Function to expand single-quoted strings
static char *expand_single_quotes(const char *input_str, int *index)
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

// Function to expand parameters
char *expand_parameter(const char *input_str, int *index, t_minishell *minishell)
{
    char *var_name;
    char *expanded_value;

    (*index)++; // Skip the '$'

    if (!input_str[*index] ||
        (!isalnum((unsigned char)input_str[*index]) &&
         input_str[*index] != '_' && input_str[*index] != '?'))
    {
        return strdup("$");
    }

    if (input_str[*index] == '?' || isdigit((unsigned char)input_str[*index]))
    {
        return expand_num_or_status(input_str, index, minishell);
    }

    var_name = extract_var_name(input_str, index);
    if (!var_name)
        return NULL;

    expanded_value = expand_env(var_name, minishell->envp);
    free(var_name);
    return expanded_value;
}

// Helper function to extract variable name
static char *extract_var_name(const char *input_str, int *index)
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

// Function to join words
char *join_word(char *word, char *new_word)
{
    char *combined;

    if (!word)
        return new_word;

    combined = ft_strjoin(word, new_word);
    free(word);
    free(new_word);

    return combined;
}

// Static function prototypes
static char *get_env_value_from_envp(const char *env_entry, int var_len);

// Function to expand environment variables
char *expand_env(const char *var_name, char **envp)
{
    int i = 0;
    int var_len = strlen(var_name);

    while (envp[i])
    {
        if (strncmp(var_name, envp[i], var_len) == 0 &&
            (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
        {
            return get_env_value_from_envp(envp[i], var_len);
        }
        i++;
    }
    return strdup("");
}

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

// Static function to get the environment variable value
static char *get_env_value_from_envp(const char *env_entry, int var_len)
{
    int start_index = var_len;
    if (env_entry[start_index] == '=')
        start_index++;
    return strdup(&env_entry[start_index]);
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
