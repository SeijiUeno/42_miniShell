/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:54:19 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/22 20:04:47 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/garbage_collector.h"

void	*ft_calloc(size_t number_elements, size_t size)
{
	void	*ptr;
	size_t	total;

	total = number_elements * size;
	if (number_elements && total / number_elements != size)
		return (NULL);
	ptr = gc_allocate(total);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
