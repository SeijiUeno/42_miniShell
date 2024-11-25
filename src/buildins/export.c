/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:44:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 18:57:58 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"
#include "buildins.h"

// Extracts the key from "key=value" format
char *key_name(const char *key_value) {
    char *equal_sign = ft_strchr(key_value, '=');
    if (!equal_sign)
        return gc_strdup(key_value);
    return gc_strndup(key_value, equal_sign - key_value);
}

// Formats and prints environment variables
static void format_and_print(const char *key, const char *value) {
    if (value)
        printf("declare -x %s=\"%s\"\n", key, value);
    else
        printf("declare -x %s\n", key);
}

// Prints environment variables in sorted order
void print_environ_sorted(void) {
    t_env_list *env_list = environ_list_holder(NULL, 0);
    t_env_list *sorted = NULL;

    // Create a sorted copy of the environment list
    while (env_list) {
        add_env_variable(&sorted, gc_strdup(env_list->key), 
                         env_list->value ? gc_strdup(env_list->value) : NULL);
        env_list = env_list->next;
    }

    // Print and free the sorted list
    while (sorted) {
        format_and_print(sorted->key, sorted->value);
        t_env_list *temp = sorted->next;
        gc_deallocate(sorted->key);
        if (sorted->value)
            gc_deallocate(sorted->value);
        gc_deallocate(sorted);
        sorted = temp;
    }
}

// Updates or adds a new environment variable
static void ft_setenv(const char *name, const char *value) {
    t_env_list *env_list = environ_list_holder(NULL, 0);

    // Remove the existing variable if it exists
    ft_unsetenv(name);

    // Add the new variable
    add_env_variable(&env_list, gc_strdup(name), value ? gc_strdup(value) : NULL);

    // Update the global environment list
    environ_list_holder(env_list, 0);
}

// Main `export` function
int export(char **args) {
    int i;
    int status = 0;

    if (!args[1]) {
        print_environ_sorted();
        return EXIT_SUCCESS;
    }

    for (i = 1; args[i]; i++) {
        // Reuse `is_valid_identifier` for validation
        if (!is_valid_identifier(args[i])) {
            status = EXIT_FAILURE;
            continue;
        }

        char *name = key_name(args[i]);
        char *equal_sign = ft_strchr(args[i], '=');

        // Add or update the variable
        if (equal_sign)
            ft_setenv(name, equal_sign + 1);
        else
            ft_setenv(name, NULL);

        gc_deallocate(name);
    }
    return status;
}
