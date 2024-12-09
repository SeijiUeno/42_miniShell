/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:22:20 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:46:47 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/garbage_collector.h"

static int  ft_count_words(char const *s, char c)
{
    int count;
    int i;

    i = 0;
    count = 0;
    if (!*s)
        return (0);
    while (s[i])
    {
        while (s[i] && s[i] == c)
            i++;
        if (s[i])
            count++;
        while (s[i] && s[i] != c)
            i++;
    }
    return (count);
}

static char **ft_alloc_words(char const *s, char **arr_str, char c, int arr_s)
{
    int     i;
    int     j;
    int     a;
    char    *str;

    i = 0;
    a = 0;
    while (a < arr_s)
    {
        j = 0;
        while (s[i] && s[i] == c)
            i++;
        if (!s[i])
            break;
        str = (char *)s + i;
        while (s[i] && s[i++] != c)
            j++;
        arr_str[a] = gc_substr(str, 0, j);
        if (!arr_str[a])
            return (NULL);
        a++;
    }
    arr_str[a] = NULL;
    return (arr_str);
}

char    **gc_split(char const *s, char c)
{
    int     count_words;
    char    **arr_str;

    if (!s || !*s)
        return (NULL);
    count_words = ft_count_words(s, c);
    arr_str = (char **)gc_allocate(sizeof(char *) * (count_words + 1));
    if (!arr_str)
        return (NULL);
    if (count_words == 0)
    {
        arr_str[0] = NULL;
        return (arr_str);
    }
    return (ft_alloc_words(s, arr_str, c, count_words));
}
