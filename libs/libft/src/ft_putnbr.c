/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:02:12 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/30 15:59:10 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define BASE 10

void	ft_putnbr(int n)
{
	unsigned int	number;
	char			x;

	if (n < 0)
	{
		write(1, "-", 1);
		number = -n;
	}
	else
		number = n;
	if (number >= BASE)
		ft_putnbr(number / BASE);
	x = (number % BASE) + '0';
	write(1, &x, 1);
}
