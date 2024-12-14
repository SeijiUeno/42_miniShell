/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:57:25 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/11 18:12:18 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_formatted_print(const char *format, va_list ap);
static int	ft_process_format_specifier(char c, va_list ap);
static int	ft_print_string(char *str);
static int	ft_print_pointer(void *ptr);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	if (!format)
		return (-1);
	va_start(ap, format);
	len = ft_formatted_print(format, ap);
	va_end(ap);
	return (len);
}

static int	ft_formatted_print(const char *format, va_list ap)
{
	int		len;
	size_t	i;

	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_process_format_specifier(format[i], ap);
		}
		else
		{
			ft_putchar_fd(format[i], STDOUT_FILENO);
			len++;
		}
		i++;
	}
	return (len);
}

static int	ft_process_format_specifier(char c, va_list ap)
{
	int	len;

	len = 0;
	if (c == 'c' || c == '%')
		len += 1;
	if (c == 'c')
		ft_putchar_fd(va_arg(ap, int), STDOUT_FILENO);
	else if (c == 's')
		len += ft_print_string(va_arg(ap, char *));
	else if (c == 'p')
		len += ft_print_pointer(va_arg(ap, void *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr_len(va_arg(ap, int), "0123456789", STDOUT_FILENO);
	else if (c == 'u')
		len += ft_putnbr_len(va_arg(ap, unsigned int), "0123456789",
				STDOUT_FILENO);
	else if (c == 'x')
		len += ft_putnbr_len(va_arg(ap, unsigned int), "0123456789abcdef",
				STDOUT_FILENO);
	else if (c == 'X')
		len += ft_putnbr_len(va_arg(ap, unsigned int), "0123456789ABCDEF",
				STDOUT_FILENO);
	else if (c == '%')
		ft_putchar_fd('%', STDOUT_FILENO);
	return (len);
}

static int	ft_print_string(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_putstr_len("(null)", STDOUT_FILENO));
	len += ft_putstr_len(str, STDOUT_FILENO);
	return (len);
}

static int	ft_print_pointer(void *ptr)
{
	int	len;

	len = 0;
	if (!ptr)
		return (ft_putstr_len("(nil)", STDOUT_FILENO));
	len += ft_putstr_len("0x", STDOUT_FILENO);
	len += ft_putptr_len((char *)ptr, STDOUT_FILENO);
	return (len);
}
