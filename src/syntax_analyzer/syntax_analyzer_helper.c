/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:36:28 by emorales          #+#    #+#             */
/*   Updated: 2024/11/06 19:42:19 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função para verificar se há parênteses não balanceados
bool	parentheses_checker(const char *input)
{
	int	parentheses;
	int	i;

	i = 0;
	parentheses = 0;
	while (input[i])
	{
		if (input[i] == '(')
			parentheses++;
		else if (input[i] == ')')
		{
			if (parentheses == 0)
				return (false);
			parentheses--;
		}
		i++;
	}
	return (parentheses == 0);
}

// Função para verificar se as aspas estão balanceadas
bool	quote_checker(const char *input)
{
	int		i;
	bool	in_quotes;
	char	quote_type;

	i = 0;
	in_quotes = false;
	quote_type = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (!in_quotes)
			{
				in_quotes = true;
				quote_type = input[i];
			}
			else if (quote_type == input[i])
			{
				in_quotes = false;
				quote_type = 0;
			}
		}
		i++;
	}
	return (!in_quotes);
}

// Função para verificar operadores mal posicionados no início/fim
bool	invalid_input_checker(const char *input)
{
	int	i;

	i = 0;
	if (input[i] == '|' || input[i] == '&')
		return (false);
	while (input[i + 1])
	{
		if ((input[i] == '|' || input[i] == '&') && input[i + 1] == '\0')
			return (false);
		i++;
	}
	return (true);
}

// Função para verificar redirecionamento sem arquivo
bool	redirection_checker(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '>' || input[i] == '<' || input[i] == '|' || input[i] == '\0')
				return (false);
		}
		i++;
	}
	return (true);
}

// Função para verificar pipes sem comandos em um ou ambos os lados
bool	pipe_checker(const char *input)
{
	int		i;
	bool	previous_was_pipe;

	i = 0;
	previous_was_pipe = false;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (previous_was_pipe)
				return (false);
			if (i == 0 || input[i + 1] == '\0')
				return (false);
			previous_was_pipe = true;
		}
		else if (input[i] != ' ')
		{
			previous_was_pipe = false;
		}
		i++;
	}
	return (true);
}
