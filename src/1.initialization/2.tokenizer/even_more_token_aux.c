/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   even_more_token_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emorales <emorales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:53:20 by emorales          #+#    #+#             */
/*   Updated: 2024/12/12 16:05:15 by emorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int	validate_all_quotes(char *input)
{
	int		index;
	char	*quote;

	index = 0;
	while (input[index])
	{
		if (ft_strchr(QUOTES, input[index]))
		{
			quote = &input[index];
			index++;
			while (input[index] && input[index] != *quote)
				index++;
			if (!input[index])
				return (EXIT_FAILURE);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}

int	is_only_spaces(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_strchr(WHITESPACE, input[i]))
		i++;
	return (input[i] == '\0');
}
int assign_redirection_type(char op_char, char *content)
{
    if (op_char == '<')
    {
        if (content[1] == '<') // Handle '<<'
            return HEREDOC;
        else
            return REDIR_IN;
    }
    else if (op_char == '>')
    {
        if (content[1] == '>') // Handle '>>'
            return APPEND;
        else
            return REDIR_OUT;
    }
    return OPERATOR; // Default case for unexpected input
}
