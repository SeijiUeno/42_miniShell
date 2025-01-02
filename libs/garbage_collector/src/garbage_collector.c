/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:41 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 20:29:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

t_garbage_node	**get_garbage_list(void)
{
	static t_garbage_node	*garbage_list;

	return (&garbage_list);
}

void	init_garbage_collector(void)
{
	t_garbage_node	**garbage_list;

	garbage_list = get_garbage_list();
	*garbage_list = (NULL);
}

void	*gc_allocate(size_t size)
{
	void			*address;
	t_garbage_node	*new_node;
	t_garbage_node	**garbage_list;

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

t_garbage_node	*gc_deallocate_garbage_node(t_garbage_node **garbage_list,
		void *address)
{
	t_garbage_node	*prev;
	t_garbage_node	*current;

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
			return (current);
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

t_gc_status	gc_deallocate(void *address)
{
	t_garbage_node	**garbage_list;
	t_garbage_node	*node_to_free;

	if (!address)
		return (GC_FAILURE);
	garbage_list = get_garbage_list();
	node_to_free = gc_deallocate_garbage_node(garbage_list, address);
	if (node_to_free)
	{
		if (node_to_free->address)
			free(node_to_free->address);
		node_to_free->address = NULL;
		free(node_to_free);
		node_to_free = NULL;
		return (GC_SUCCESS);
	}
	return (GC_NOT_FOUND);
}
