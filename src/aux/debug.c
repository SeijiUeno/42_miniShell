#include "../includes/shell.h"

void	debug_print_tree(t_command *node, int level)
{
	t_token	*redir;

	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("  ");
	if (node->type == PIPE)
		printf("PIPE\n");
	else if (node->argv && node->argv[0])
	{
		printf("COMMAND: %s\n", node->argv[0]);
		if (node->argv[1])
		{
			printf("  Arguments:\n");
			for (int i = 1; node->argv[i]; i++)
				printf("    %s\n", node->argv[i]);
		}
		if (node->redir)
		{
			printf("  Redirections:\n");
			redir = node->redir;
			while (redir)
			{
				printf("    Type: %d, Content: %s\n", redir->type,
					redir->content);
				redir = redir->next;
			}
		}
	}
	else
		printf("UNKNOWN NODE\n");
	debug_print_tree(node->left, level + 1);
	debug_print_tree(node->right, level + 1);
}

void	debug_print_commands_array(t_command **commands)
{
	t_token	*r;

	int i, j;
	if (!commands)
	{
		printf("Debug: command array is NULL.\n");
		return ;
	}
	printf("Debug: command array contents:\n");
	for (i = 0; commands[i]; i++)
	{
		printf("Command %d:\n", i);
		if (commands[i]->argv)
		{
			for (j = 0; commands[i]->argv[j]; j++)
			{
				printf("  argv[%d]: %s\n", j, commands[i]->argv[j]);
			}
		}
		else
		{
			printf("  No arguments for this command.\n");
		}
		if (commands[i]->redir)
		{
			r = commands[i]->redir;
			printf("  Redirections:\n");
			while (r)
			{
				printf("    Type: %d, File: %s\n", r->type, r->content);
				r = r->next;
			}
		}
	}
	printf("End of command array.\n");
}

void	debug_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("Tokens:\n");
	while (current)
	{
		printf("Type: %d, Content: '%s'\n", current->type, current->content);
		current = current->next;
	}
	printf("End of tokens\n");
}
