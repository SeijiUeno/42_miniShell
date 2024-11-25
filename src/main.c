/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/11/25 18:12:34 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"
#include "token/tokenizer.h"
#include "signal/signals.h"
#include "ast/ast.h"

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
			gc_cleanup();
			clear_history();
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
			gc_deallocate (input);
			continue ;// Skip this iteration and prompt again
		}
		print_tokens(tokens);
		tree = tree_constructor(tokens);
		print_ast(tree, 6);
		gc_deallocate_tokens(tokens);
		gc_deallocate(tree); // gc_deallocate_tree to be build!!! must gc_deallocate all of it
		gc_deallocate(input);
	}
	clear_history();
	return (0);
}
