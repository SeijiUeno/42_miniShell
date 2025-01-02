/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:59:54 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 19:58:45 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static size_t	count_digits(int n);

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;
	long	nb;

	size = count_digits(n);
	str = gc_allocate(size + 1);
	if (!str)
		return (NULL);
	str[size--] = '\0';
	nb = n;
	if (n < 0)
		nb *= -1;
	while (size != 0)
	{
		str[size] = ft_tochr(nb % 10);
		nb /= 10;
		size--;
	}
	if (n < 0)
		str[size] = '-';
	else
		str[size] = ft_tochr(nb % 10);
	return (str);
}

static size_t	count_digits(int n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}
