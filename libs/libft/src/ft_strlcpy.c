/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 02:03:08 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/04 17:33:49 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	len;

	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	if (srclen >= size)
		len = size - 1;
	else
		len = srclen;
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (srclen);
}
