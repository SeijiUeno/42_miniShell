/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tracker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:18:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 20:20:37 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"

t_gc_status	gc_track(void *address)
{
	t_garbage_node	*new_node;
	t_garbage_node	**garbage_list;

	if (!address)
		return (GC_FAILURE);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (GC_FAILURE);
	garbage_list = get_garbage_list();
	new_node->address = address;
	new_node->next = *garbage_list;
	*garbage_list = new_node;
	return (GC_SUCCESS);
}

void	gc_cleanup(void)
{
	t_garbage_node	**garbage_list;
	t_garbage_node	*current;
	t_garbage_node	*temp;

	garbage_list = get_garbage_list();
	current = *garbage_list;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->address)
		{
			free(temp->address);
			temp->address = NULL;
		}
		if (temp)
		{
			free(temp);
			temp = NULL;
		}
	}
	*garbage_list = NULL;
}
