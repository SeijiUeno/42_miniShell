/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:42:57 by sueno-te          #+#    #+#             */
/*   Updated: 2024/12/01 21:45:48 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/garbage_collector.h"
# include "../error/error.h" 

# define WHITESPACE " \t\n\r\v\f"
# define SYMBOLS "|<>"
# define QUOTES "'\""

typedef struct s_token t_token;

typedef enum e_token_type {
    WORD,
    OPERATOR,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    HEREDOC,
    APPEND
} t_token_type;

struct s_token {
    t_token_type 	type;
    char 			*content;
    struct s_token *next;
    struct s_token *prev;
};

// Function declarations
void generate_tokens(char *input, t_token **tokens);
int validate_tokens(t_token *tokens);
void assign_operator_token_types(t_token **tokens);

// Utility functions
void initialize_token_list(t_token **tokens);
void append_token(t_token **lst, t_token *new);
void free_all_tokens(t_token **tokens);
void skip_whitespace(char *input, int *i);
void create_new_token(t_token **tokens, char *input, int start, int end);

// Internal helper functions
int validate_all_quotes(char *input);
void skip_quoted_token(char *input, int *i);
void process_operator_token(char *input, t_token **tokens, int *i);
void extract_word_token(char *input, t_token **tokens, int *i);

#endif