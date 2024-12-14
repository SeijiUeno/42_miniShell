/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:07:09 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/14 18:42:10 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#define BASE 16

size_t	ft_putptr_len(void *ptr, int fd)
{
	size_t		len;
	const char	digits[BASE] = "0123456789abcdef";

	len = 0;
	if ((size_t)ptr >= BASE)
		len += ft_putptr_len((void *)((size_t)ptr / BASE), fd);
	ft_putchar_fd(digits[(size_t)ptr % BASE], fd);
	len++;
	return (len);
}
