/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:45:08 by sueno-te          #+#    #+#             */
/*   Updated: 2025/01/03 12:08:50 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

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

char	**build_argument_vector(t_token *tokens, t_ms *minishell)
{
	int	count;

	count = count_command_arguments(tokens);
	if (!count)
		return (NULL);
	return (allocate_argument_array(tokens, minishell, count));
}

static void	free_argument_array_partially(char **argv, int used)
{
	while (used--)
		gc_deallocate(argv[used]);
	gc_deallocate(argv);
}

char	**allocate_argument_array(t_token *tokens,
	t_ms *minishell, int count)
{
	char	**argv;
	int		index;

	argv = gc_allocate(sizeof(char *) * (count + 1));
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

void	advance_to_next_pipe(t_token **tokens)
{
	while (*tokens && (*tokens)->type != PIPE)
		*tokens = (*tokens)->next;
}
