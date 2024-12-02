/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/02 17:12:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansor.h"

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

// Static function to get the environment variable value
static char *get_env_value_from_envp(const char *env_entry, int var_len)
{
    int start_index = var_len;
    if (env_entry[start_index] == '=')
        start_index++;
    return strdup(&env_entry[start_index]);
}