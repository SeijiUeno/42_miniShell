/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 02:02:55 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 13:08:33 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/garbage_collector.h"

char	*gc_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s);
	str = gc_allocate(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, len + 1);
	return (str);
}
