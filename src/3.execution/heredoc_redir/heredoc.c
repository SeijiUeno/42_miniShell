/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:18:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/10 18:55:44 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.c"

void	handle_sig_heredoc(int signal)
{
	// Handle SIGINT by printing a newline and closing stdin
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		close(STDIN_FILENO);
		control_status(130);
	}
}

int	verify_heredoc(t_minishell *minishell)
{
	t_token	*temp;
	int		status;

	// Initialize status to 0 (no error)
	status = 0;
	temp = minishell->tokens;

	// Loop through the tokens to find any HEREDOC types
	while (temp)
	{
		// If a HEREDOC token is found, process it
		if (temp->type == HEREDOC)
		{
			// Call heredoc and increment index for each found HEREDOC
			status = heredoc(&temp->next->content, 0);
		}
		// If an error occurred, return status immediately
		if (status)
			return (status);
		
		// Move to the next token
		temp = temp->next;
	}

	// Return status (0 if no errors were found)
	return (status);
}

char	*generate_heredoc_name(int index)
{
	char	*index_text;
	char	*full_name;

	// Convert index to string
	index_text = ft_itoa(index);
	if (!index_text)
	{
		perror("Error converting index to string");
		return (NULL);
	}

	// Create the full heredoc filename with /tmp/heredoc-<index>
	full_name = ft_strjoin("/tmp/heredoc-", index_text);
	free(index_text); // Free the temporary index string
	if (!full_name)
	{
		perror("Error generating heredoc name");
		return (NULL);
	}

	return (full_name);
}

int	read_heredoc(char *delim, int fd)
{
	char	*line;

	// Initialize line to NULL and set SIGINT handler
	line = NULL;
	signal(SIGINT, &handle_sig_heredoc);

	// Continuously read input for heredoc until delimiter is found or EOF
	while (1)
	{
		line = readline("> ");
		if (!line) // EOF or error in readline
		{
			// Handle EOF case, print warning if necessary
			if (!control_status(-1))
				ft_fdprintf("Warning: heredoc delimited by EOF. Wanted delim: %s\n", 2, delim);
			break ;
		}

		// If line matches delimiter, stop reading and free line
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}

		// Write line to file descriptor and free line
		ft_putendl_fd(line, fd);
		free(line);
	}

	// Restore the original signal handler and return the status
	signal(SIGINT, &handle_signal);
	return (control_status(-1));
}

int	heredoc(char **str, int index)
{
	char	*full_name;
	int		fd;
	int		status;

	// Generate a unique filename for the heredoc
	full_name = generate_heredoc_name(index);
	if (!full_name)
		return (EXIT_FAILURE);

	// Open the file for writing
	fd = open(full_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		// Handle file open failure
		perror("Error opening heredoc file");
		free(full_name);
		return (EXIT_FAILURE);
	}

	// Read input for heredoc and write to the file
	status = read_heredoc(*str, fd);
	close(fd); // Close the file descriptor

	// If an error occurred, return the status
	if (status)
	{
		free(full_name);
		return (status);
	}

	// Update the pointer with the filename and free original delimiter string
	free(*str);
	*str = full_name;

	// Return 0 if no errors occurred
	return (0);
}
