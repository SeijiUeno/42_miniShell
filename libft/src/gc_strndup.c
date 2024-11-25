/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:23:39 by sueno-te          #+#    #+#             */
/*   Updated: 2024/11/25 16:09:52 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stddef.h> 
# include "../includes/garbage_collector.h"

char *gc_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *copy;

    if (!s)
        return NULL;
    while (s[len] && len < n)
        len++;
    copy = gc_allocate(len + 1); 
    if (!copy)
        return NULL;
    for (size_t i = 0; i < len; i++)
        copy[i] = s[i];
    copy[len] = '\0';

    return copy;
}
