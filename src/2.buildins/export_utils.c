/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:01:25 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 06:08:37 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	util_swap_array(char **wordA, char **wordB)
{
	char	*temp;

	if (!wordA || !wordB || !(*wordA) || !(*wordB))
		return ;
	temp = *wordA;
	*wordA = *wordB;
	*wordB = temp;
}

char	*val_e_v(const char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return ((char *)var);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return ((char *)var);
		i++;
	}
	return (NULL);
}

int	calculate_name_size(const char *text, char delimiter)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != delimiter)
		i++;
	return (i);
}
