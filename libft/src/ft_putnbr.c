/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:02:12 by sueno-te          #+#    #+#             */
/*   Updated: 2024/09/21 17:02:13 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define BASE 10

void	ft_putnbr(int n)
{
	unsigned int	nb;
	char			x;

	if (n < 0)
	{
		write(1, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	if (nb >= BASE)
		ft_putnbr(nb / BASE);
	x = (nb % BASE) + '0';
	write(1, &x, 1);
}
