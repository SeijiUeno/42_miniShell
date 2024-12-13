/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:16:18 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/13 18:47:06 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	print_env(char **envp)
{
	char	**temp;

	temp = envp;
	while (*temp != NULL)
	{
		if (ft_strchr(*temp, '='))
			ft_printf("%s\n", *temp);
		temp++;
	}
	return (0);
}
