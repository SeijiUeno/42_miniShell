/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:31:42 by emorales          #+#    #+#             */
/*   Updated: 2024/11/06 19:56:44 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	multiple_operator_checker(const char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		// Verifica se há três operadores consecutivos, como ">>>" ou "|||"
		if ((input[i] == '|' || input[i] == '>')
			&& input[i + 1] == input[i] && input[i + 2] == input[i])
			return (false);
		// Verifica combinações inválidas como ">|" ou ">>|"
		if ((input[i] == '>' && input[i + 1] == '|')
			|| (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '|'))
			return (false);
		// Verifica operadores seguidos de caracteres não esperados, como "|x" ou ">x"
		if ((input[i] == '|' || input[i] == '>')
			&& input[i + 1] != '\0' && !ft_isspace(input[i + 1]))
		{
			if (input[i + 1] != '|' && input[i + 1] != '>')
				return (false);
		}
		i++;
	}
	return (true);
}

// Função principal que chama todas as subfunções de verificação
bool	syntax_analyzer(const char *input)
{
	return (parentheses_checker(input)
		&& quote_checker(input)
		&& invalid_input_checker(input)
		&& redirection_checker(input)
		&& pipe_checker(input)
		&& multiple_operator_checker(input));
}
