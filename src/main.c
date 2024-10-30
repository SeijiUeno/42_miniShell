/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/10/30 17:21:21 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"
#include "token/tokenizer.h"
#include "signal/signals.h"
#include "parser/ast/ast.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_ast	*tree;

	signal_init();
	while (1)
	{
		input = readline("myshell> ");
		if (!input)
		{
			printf("\nExiting shell...\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenizer(input);
		if (tokens == NULL)
		{
			// **An error occurred during tokenization**
			// You can choose to continue or exit
			free (input);
			continue ;// Skip this iteration and prompt again
		}
		print_tokens(tokens);
		tree = tree_constructor(tokens);
		free_tokens(tokens);
		free(tree); // free_tree to be build!!! must free all of it
		free(input);
	}
	clear_history();
	return (0);
}
