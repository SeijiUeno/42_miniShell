/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:22:20 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 13:42:45 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

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

static char	**ft_alloc_words(char const *s, char **arr_str, char c, int arr_s)
{
	int		i;
	int		j;
	int		a;
	char	*str;

	i = 0;
	a = 0;
	while (a < arr_s)
	{
		j = 0;
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		str = (char *)s + i;
		while (s[i] && s[i++] != c)
			j++;
		arr_str[a] = ft_substr(str, 0, j);
		if (!arr_str[a])
			return (NULL);
		a++;
	}
	arr_str[a] = NULL;
	return (arr_str);
}

char	**ft_split(char const *s, char c)
{
	int		count_words;
	char	**arr_str;

	if (!s || !*s)
		return (NULL);
	count_words = ft_count_words(s, c);
	arr_str = (char **)malloc(sizeof(char *) * (count_words + 1));
	if (!arr_str)
		return (NULL);
	if (count_words == 0)
	{
		arr_str[0] = NULL;
		return (arr_str);
	}
	return (ft_alloc_words(s, arr_str, c, count_words));
}
