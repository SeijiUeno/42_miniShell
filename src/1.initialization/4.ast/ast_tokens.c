/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:45:08 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/15 05:21:23 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

/**
 * Counts the number of arguments in a command up to a pipe.
 * @param tokens - The list of tokens.
 * @return Number of arguments before a PIPE token.
 */
static int	count_command_arguments(t_token *tokens)
{
	int	arg_count;

	arg_count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			arg_count++;
		tokens = tokens->next;
	}
	return (arg_count);
}

/**
 * Builds the argument vector from tokens.
 * @param tokens - The token list.
 * @param minishell - The shell context.
 * @return The argument vector or NULL on failure.
 */
char	**build_argument_vector(t_token *tokens, t_ms *minishell)
{
	int	count;

	count = count_command_arguments(tokens);
	if (!count)
		return (NULL);
	return (allocate_argument_array(tokens, minishell, count));
}

/**
 * Frees partially allocated argument array in case of error.
 * @param argv - The argument array.
 * @param used - Number of arguments allocated.
 */
static void	free_argument_array_partially(char **argv, int used)
{
	while (used--)
		free(argv[used]);
	free(argv);
}

/**
 * Allocates and populates the argument array with expanded variables and quotes.
 * @param tokens - The token list.
 * @param minishell - The shell context.
 * @param count - The number of arguments to allocate.
 * @return The populated argument array or NULL on failure.
 */
char	**allocate_argument_array(t_token *tokens,
	t_ms *minishell, int count)
{
	char	**argv;
	int		index;

	argv = malloc(sizeof(char *) * (count + 1));
	index = 0;
	if (!argv)
		return (NULL);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			argv[index] = expansor(tokens->content, minishell);
			if (!argv[index])
			{
				free_argument_array_partially(argv, index);
				return (NULL);
			}
			index++;
		}
		tokens = tokens->next;
	}
	argv[index] = NULL;
	return (argv);
}

/**
 * Advances the token pointer to the next pipe or end of the list.
 * @param tokens - A pointer to the token pointer.
 */
void	advance_to_next_pipe(t_token **tokens)
{
	while (*tokens && (*tokens)->type != PIPE)
		*tokens = (*tokens)->next;
}
