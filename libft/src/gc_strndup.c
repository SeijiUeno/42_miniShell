/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:23:39 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 19:34:15 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/garbage_collector.h"
#include "../includes/libft.h"

char *gc_strndup(const char *s, size_t n)
{
    size_t len;
    char *copy;
    size_t i;

    len = 0;
    if (!s)
        return NULL;
    while (s[len] && len < n)
        len++;
    copy = gc_allocate(len + 1); 
    if (!copy)
        return NULL;
    i = 0;
    while (i < len)
    {
        copy[i] = s[i];
        i++;
    }
    copy[len] = '\0';

    return copy;
}
