/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:07:41 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 19:41:50 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// Initialize the environment variables into a linked list
int	last_exit_status(int exit_status)
{
	static int	status;

	if (exit_status != -1)
		status = exit_status;
	return (status);
}

void environ_list_initializer(void)
{
    extern char **__environ;
    int          index;
    t_env_list  *env_list;

    env_list = NULL;
    index = 0;
    while (__environ[index])
    {
        char *equal_sign = ft_strchr(__environ[index], '=');
        char *key;
        char *value;

        if (equal_sign)
        {
            key = gc_strndup(__environ[index], equal_sign - __environ[index]);
            value = gc_strdup(equal_sign + 1);
        }
        else
        {
            key = gc_strdup(__environ[index]);
            value = gc_strdup("");
        }
        add_env_variable(&env_list, key, value);
        index++;
    }
    environ_list_holder(env_list, 0);
}

// Acts as a getter and setter for the environment list
t_env_list *environ_list_holder(t_env_list *new_env_list, int to_free)
{
    static t_env_list *env_list = NULL;

    if (new_env_list)
        env_list = new_env_list;
    if (to_free && env_list)
    {
        free_env_list(env_list);
        env_list = NULL;
    }
    return env_list;
}

// Add a new environment variable to the linked list
void add_env_variable(t_env_list **env_list, char *key, char *value)
{
    t_env_list *new_node = gc_allocate(sizeof(t_env_list));

    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;

    if (*env_list == NULL)
    {
        *env_list = new_node;
    }
    else
    {
        t_env_list *current = *env_list;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

// Remove an environment variable from the linked list
void remove_env_variable(t_env_list **env_list, const char *key)
{
    t_env_list *current = *env_list;
    t_env_list *previous = NULL;

    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
                *env_list = current->next; // Removing the head node
            else
                previous->next = current->next;

            // Explicitly free memory using gc_deallocate
            if (current->key)
                gc_deallocate(current->key);
            if (current->value)
                gc_deallocate(current->value);
            gc_deallocate(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

// Retrieve the value of an environment variable
char *get_env_value(t_env_list *env_list, const char *key)
{
    while (env_list)
    {
        if (ft_strcmp(env_list->key, key) == 0)
            return env_list->value;
        env_list = env_list->next;
    }
    return NULL;
}

// Free the entire environment list
void free_env_list(t_env_list *env_list)
{
    t_env_list *current = env_list;
    t_env_list *next_node;

    while (current)
    {
        next_node = current->next;
        // Explicitly free key and value
        if (current->key)
            gc_deallocate(current->key);
        if (current->value)
            gc_deallocate(current->value);
        // Free the node itself
        gc_deallocate(current);
        current = next_node;
    }
}