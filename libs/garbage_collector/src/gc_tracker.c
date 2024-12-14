/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_tracker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:18:43 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 13:38:16 by emorales         ###   ########.fr       */
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
