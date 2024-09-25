/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/09/25 19:01:52 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"

int	main(void)
{
	char	*input;

	signal_init(); // init signal handling
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
		printf("You entered: %s\n", input);
		free(input);
	}
	clear_history(); // Clear the history list (readlline f)
	return (0);
}
