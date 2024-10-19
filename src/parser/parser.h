/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:26:04 by marvin            #+#    #+#             */
/*   Updated: 2024/10/12 16:26:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

typedef struct s_command {
    char            **args;          // List of arguments
    char            *input_file;     // Input file for redirection
    char            *output_file;    // Output file for redirection
    int             append;          // Flag for '>>' (1 for append, 0 for overwrite)
    char            *heredoc_delimiter;  // Delimiter for heredoc '<<'
    struct s_command *next;          // Next command in the pipeline
} t_command;
