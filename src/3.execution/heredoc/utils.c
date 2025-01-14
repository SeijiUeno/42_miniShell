/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:22:07 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/04 19:01:29 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

char	*heredoc_generate_name(int index)
{
	char	*index_text;
	char	*full_name;

	index_text = ft_itoa(index);
	if (!index_text)
	{
		ft_putstr_fd("Error: Failed to convert index to string\n",
			STDERR_FILENO);
		return (NULL);
	}
	full_name = ft_strjoin("/tmp/heredoc-", index_text);
	if (!full_name)
	{
		ft_putstr_fd("Error: Failed to generate heredoc name\n", STDERR_FILENO);
		return (NULL);
	}
	return (full_name);
}

void	signal_handle_heredoc(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
	status_control(STATUS_SIGINT);
	if (g_in_subprocess == SUBPROCESS_HEREDOC)
		g_in_subprocess = SUBPROCESS_INT_HDOC;
}
