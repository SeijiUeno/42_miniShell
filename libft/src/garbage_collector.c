/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:41 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/22 20:40:25 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

static t_garbage_node **get_garbage_list(void)
{
    static t_garbage_node   *garbage_list;
    return (&garbage_list);
}

void init_garbage_collector(void)
{
    t_garbage_node  **garbage_list;

    garbage_list = get_garbage_list();
    *garbage_list = NULL;
}

void *gc_allocate(size_t size)
{
    void            *address;
    t_garbage_node  *new_node;
    t_garbage_node  **garbage_list;

    address = malloc(size);
    if (!address)
        return (NULL);

    new_node = malloc(sizeof(t_garbage_node));
    if (!new_node)
    {
        free(address);
        return (NULL);
    }

    garbage_list = get_garbage_list();
    new_node->address = address;
    new_node->next = *garbage_list;
    *garbage_list = new_node;
    return (address);
}

t_gc_status gc_deallocate(void *address) 
{
    t_garbage_node  **garbage_list;
    t_garbage_node  *prev;
    t_garbage_node  *current;

    if (!address)
    {
        //"Warning: Attempted to deallocate a NULL pointer
        return (GC_FAILURE);
    }

    garbage_list = get_garbage_list();
    prev = NULL;
    current = *garbage_list;
    while (current)
    {
        if (current->address == address)
        {
            if (prev)
                prev->next = current->next;
            else
                *garbage_list = current->next;
            free(current->address);
            free(current);
            return GC_SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    //"Warning: Attempted to deallocate untracked memory at 
    return (GC_NOT_FOUND);
}

void gc_cleanup(void)
{
    t_garbage_node  **garbage_list;
    t_garbage_node  *current;
    t_garbage_node  *temp;

    garbage_list = get_garbage_list();
    current = *garbage_list;
    while (current)
    {
        temp = current;
        current = current->next;
        if (temp->address)
            free(temp->address);
        if (temp)
            free(temp);  
    }
    *garbage_list = NULL;
}
