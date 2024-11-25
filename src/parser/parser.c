/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:25:18 by marvin            #+#    #+#             */
/*   Updated: 2024/11/25 18:15:59 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
-Casos a considerar:
Comandos sem nome (por exemplo, uma linha começando com um operador)
Redirecionamentos sem arquivo
Pipes sem comandos em um ou ambos os lados
Uso incorreto de operadores (como ||| ou >>|)
*/

t_token	*current_token; //e se ao invés de uma "função global" criarmos uma struct e passarmos para parse_command?
/*
typedef struct s_parser_variable {
	t_token *current_token;
} t_parser_variable;

Substituir todos current_token por context->current_token nas funções
*/

void	advance_token(void)
{
	if (current_token != NULL)
		current_token = current_token->next;
}

void	parse_input(t_token *head_of_tokens)
{
	t_command	*cmd_list;

	current_token = head_of_tokens;
	if (current_token && current_token->type == TOKEN_WORD)
	{
		cmd_list = parse_pipeline();
		if (!cmd_list)
		{
			printf("Error: Parsing failed\n");
			return ;
		}
		/* Futura função de execução de comandos
		execute_commands(cmd_list);*/
		gc_deallocate_command_list(cmd_list);
	}
	else if (current_token && current_token->type == TOKEN_EOF)
		printf("End of input\n");
	else
		printf("Error: Invalid input\n");
}

t_command	*parse_command(void)
{
	t_command	*cmd;

	cmd = create_new_command();
	if (!cmd)
		return (NULL);
	// The command should start with a TOKEN_WORD (command name)
	if (current_token && current_token->type == TOKEN_WORD)
	{
		add_argument_to_command(cmd, current_token->value); //tratar erros pra liberar comando em caso de !add_argument_to_command
		advance_token();
		// While we have TOKEN_WORD, continue as arguments
		while (current_token && current_token->type == TOKEN_WORD)
		{
			add_argument_to_command(cmd, current_token->value); //tratar erros pra liberar comando em caso de !add_argument_to_command
			advance_token();
		}
		// Handle possible redirections
		parse_redirection(/*passar lista de comandos*/); //tratar erros pra liberar comando em caso de !parse_redirection
	}
	else
	{
		printf("Error: Expected a command\n");
		gc_deallocate_command(cmd);
		return (NULL);
	}
	return (cmd);
}

t_command	*parse_pipeline(void)
{
	t_command	*cmd_head;
	t_command	*cmd_current;
	t_command	*cmd_new;

	cmd_head = NULL;
	cmd_current = NULL;
	cmd_new = NULL;
	// Parse first command
	cmd_new = parse_command();
	if (!cmd_new)
		return (NULL); //melhorar tratamento de erro?
	cmd_head = cmd_new; // Inicio da lista
	cmd_current = cmd_new;
	// While in TOKEN_PIPE, keep parsing
	while (current_token && current_token->type == TOKEN_PIPE)
	{
		advance_token();
		// Next command after pipe
		cmd_new = parse_command();
		if (!cmd_new)
		{
			gc_deallocate_command_list(cmd_head);
			return (NULL);
		}
		// Link the command to the rest of the list
		cmd_current->next = cmd_new;
		cmd_current = cmd_new;
	}
	return (cmd_head);
}

int	parse_redirection(t_command *cmd)
{
	t_token_type	redir_type;

	while (current_token &&
	(current_token->type == TOKEN_REDIRECT_IN
	|| current_token->type == TOKEN_REDIRECT_OUT
	|| current_token->type == TOKEN_REDIRECT_APPEND
	|| current_token->type == TOKEN_HEREDOC))
	{
		redir_type = current_token->type;
		advance_token(); // Consume the redirection token
		if (current_token && current_token->type == TOKEN_WORD)
		{
			if (redir_type == TOKEN_REDIRECT_IN)
			{
				cmd->input_file = gc_strdup(current_token->value);
				if (!cmd->input_file)
					return (0); // Falha na alocação
			}
			else if (redir_type == TOKEN_REDIRECT_OUT)
			{
				cmd->output_file = gc_strdup(current_token->value);
				if (!cmd->output_file)
					return (0);
				cmd->append = 0;
			}
			else if (redir_type == TOKEN_REDIRECT_APPEND)
			{
				cmd->output_file = gc_strdup(current_token->value);
				if (!cmd->output_file)
					return (0);
				cmd->append = 1;
			}
			else if (redir_type == TOKEN_HEREDOC)
			{
				cmd->heredoc_delimiter = gc_strdup(current_token->value);
				if (!cmd->heredoc_delimiter)
					return (0);
			}
			advance_token(); // Advance through filename
		}
		else
		{
			printf("Error: Expected a file name after redirection\n");
			return (0);
		}
	}
	return (1); // Success
}
