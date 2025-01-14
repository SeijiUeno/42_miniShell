/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:15:38 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 20:03:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>

typedef struct s_garbage_node	t_garbage_node;

struct	s_garbage_node
{
	void			*address;
	t_garbage_node	*next;
};

typedef enum e_gc_status
{
	GC_SUCCESS = 0,
	GC_FAILURE = -1,
	GC_NOT_FOUND = 1
}t_gc_status;

t_garbage_node	**get_garbage_list(void);
void			init_garbage_collector(void);
void			*gc_allocate(size_t size);
t_gc_status		gc_deallocate(void *address);
void			gc_cleanup(void);
t_gc_status		gc_track(void *address);

#endif
