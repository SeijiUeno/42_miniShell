/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sueno-te <sueno-te@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:14:55 by emorales          #+#    #+#             */
/*   Updated: 2024/10/16 19:44:17 by sueno-te         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* main.c */

#include "shell.h"
#include "token/tokenizer.h"
#include "signal/signals.h"

#define TABLE_SIZE 100

// Define a function pointer type for commands that take argument arrays
typedef void (*CommandFunc)(int argc, char *argv[]);

typedef struct Node {
    char *key;
    CommandFunc func;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *buckets[TABLE_SIZE];
} HashMap;

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % TABLE_SIZE;
}

void init_hashmap(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->buckets[i] = NULL;
    }
}

Node *create_node(const char *key, CommandFunc func) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->func = func;
    new_node->next = NULL;
    return new_node;
}

void hashmap_insert(HashMap *map, const char *key, CommandFunc func) {
    unsigned int index = hash(key);
    Node *new_node = create_node(key, func);
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

CommandFunc hashmap_get(HashMap *map, const char *key) {
    unsigned int index = hash(key);
    Node *current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->func;
        }
        current = current->next;
    }
    return NULL;
}

void hashmap_free(HashMap *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = map->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
}

void cmd_echo(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

void cmd_pwd(int argc, char *argv[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void cmd_exit(int argc, char *argv[]) {
    printf("Exiting...\n");
    exit(0);
}

void execute_commands(t_token *tokens, HashMap *map) {
    while (tokens) {
        // If the token is a command (TOKEN_WORD)
        if (tokens->type == TOKEN_WORD) {
            CommandFunc func = hashmap_get(map, tokens->value);
            if (func) {
                // Collect arguments for the command
                char *argv[10];
                int argc = 0;

                while (tokens && tokens->type == TOKEN_WORD && argc < 10) {
                    argv[argc++] = tokens->value;
                    tokens = tokens->next;
                }
                argv[argc] = NULL;

                // Execute the command function with the collected arguments
                func(argc, argv);
            } else {
                printf("Command not found: %s\n", tokens->value);
                return;
            }
        } else {
            // Handle operators like pipes, redirects, etc.
            tokens = tokens->next;
        }
    }
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	extern char	**environ;
	
	HashMap map;
    init_hashmap(&map);

    // Insert commands into the hashmap
    hashmap_insert(&map, "echo", cmd_echo);
    hashmap_insert(&map, "pwd", cmd_pwd);
    hashmap_insert(&map, "exit", cmd_exit);
	signal_init();
	
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
		tokens = tokenizer(input);
		if (tokens == NULL)
		{
			free (input);
			continue ;
		}
		CommandFunc func = hashmap_get(&map, tokens);
    	if (func)
        	func(argc, args);
		print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	clear_history();
	return (0);
}
