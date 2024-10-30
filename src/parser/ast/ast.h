/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:40:02 by sueno-te          #+#    #+#             */
/*   Updated: 2024/10/30 15:48:47 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "../../libft/includes/libft.h"
# include "../../token/tokenizer.h"

// doubled linked list
typedef struct s_element
{
	void				*content;
	struct s_element	*next;
	struct s_element	*prev;
}	t_element;

typedef struct s_list
{
	t_element	*first;
	t_element	*last;
	size_t		size;
}	t_list;

// ast stucture

typedef struct s_ast
{
  struct s_ast		    *left;
  struct s_ast		    *right;
  t_list				*exec;
  int					type;
}	t_ast;

#endif
