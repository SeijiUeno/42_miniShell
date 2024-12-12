/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:22:07 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/12 14:33:56 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*generate_heredoc_name(int index)
{
	char	*index_text;
	char	*full_name;

	index_text = ft_itoa(index);
	if (!index_text)
	{
		ft_putstr_fd("Error: Failed to convert index to string\n", STDERR_FILENO);
		return (NULL);
	}
	full_name = ft_strjoin("/tmp/heredoc-", index_text);
	free(index_text);
	if (!full_name)
		ft_putstr_fd("Error: Failed to generate heredoc name\n", STDERR_FILENO);
	return (full_name);
}
