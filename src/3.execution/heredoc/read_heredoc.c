/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:18:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 00:51:00 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

// Sets up the signal handler for the heredoc process
static void	setup_heredoc_signals(void)
{
	signal(SIGINT, &signal_handle_heredoc);
}

// Resets the signal handler back to default
static void	reset_signals(void)
{
	signal(SIGINT, &signal_handle);
}

// Processes a single line of heredoc input
static int process_line(char *line, const char *delim, int fd) {
    if (!line) {
        ft_putstr_fd("Warning: heredoc delimited by EOF. Expected: ", STDERR_FILENO);
        ft_putstr_fd(delim, STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (1);  // Stop processing due to EOF
    }

    if (ft_strcmp(line, delim) == 0) {
        return (1);  // Stop processing when the delimiter is reached
    }

    ft_putendl_fd(line, fd);
    return (0);  // Continue processing
}

// Reads heredoc input until the delimiter is reached or an error occurs
int heredoc_read(const char *delim, int fd) {
    char *line;
    int stop = 0;

    setup_heredoc_signals();

    while (!stop) {
        line = readline("> ");
        if (!line) {
            // Handle signal interruption (Ctrl+C)
            if (errno == EINTR) {
                reset_signals();
                return (STATUS_SIGINT);
            }
            // EOF or other error
            break;
        }

        stop = process_line(line, delim, fd);
        free(line);
    }

    reset_signals();

    if (stop) {
        return (0);  // Success
    } else {
        return (STATUS_EOF);  // EOF-specific status or error
    }
}

// Verifies if any heredoc tokens exist and processes them
int	verify_heredoc(t_minishell *minishell)
{
	t_token	*current;
	int		status = 0;

	current = minishell->tokens;
	while (current && !status)
	{
		if (current->type == HEREDOC)
			status = heredoc(&current->next->content, 0);
		current = current->next;
	}
	return (status);
}