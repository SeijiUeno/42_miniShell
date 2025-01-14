/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:24:05 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:33:55 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_error(const char *prefix, const char *arg, const char *suffix)
{
	ft_putstr_fd((char *)prefix, 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putendl_fd((char *)suffix, 2);
}
