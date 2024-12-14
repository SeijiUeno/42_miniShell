/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:10:17 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 14:58:21 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_putnbr_len(long long number, char *base, int fd)
{
	unsigned long long	absolute_number;
	size_t				base_lenght;
	size_t				printed_chars;

	printed_chars = 0;
	if (number < 0)
	{
		ft_putchar_fd('-', fd);
		printed_chars++;
		absolute_number = -number;
	}
	else
		absolute_number = number;
	base_lenght = ft_strlen(base);
	if (absolute_number >= base_lenght)
		printed_chars += ft_putnbr_len(absolute_number / base_lenght, base, fd);
	ft_putchar_fd(base[absolute_number % base_lenght], fd);
	printed_chars++;
	return (printed_chars);
}
