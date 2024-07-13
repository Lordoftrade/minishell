/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:58:06 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 01:38:27 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_lexer *tokens) {
    while (tokens) {
        printf("Token: %s\n", tokens->content);
        tokens = tokens->next;
    }
}

void print_command(t_command *command) {
    printf("Arguments:\n");
    for (int i = 0; command->argv[i] != NULL; i++) {
        printf("\t%s\n", command->argv[i]);
    }
    if (command->input) {
        printf("Input: %s\n", command->input);
    }
    if (command->output) {
        printf("Output: %s\n", command->output);
    }
    if (command->delimiter) {
        printf("Delimiter: %s\n", command->delimiter);
	if (command->LT)
		printf("LT: %d\n", command->LT);
	if (command->GT)
		printf("GT: %d\n", command->GT);
	if (command->D_LT)
		printf("D_LT: %d\n", command->D_LT);
	if (command->D_GT)
		printf("D_GT: %d\n", command->D_GT);
        printf("\n");
    }
}


// void print_command(t_command *cmd)
// {
// 	// printf("Command: %d\n", cmd->type);
// 	printf("Arguments:\n");
// 	char **arg = cmd->argv;
// 	while (*arg)
// 	{
// 	    printf("  %s\n", *arg);
// 	    arg++;
// 	}
// 	if (cmd->input)
// 	    printf("Input redirection: %s\n", cmd->input);
// 	if (cmd->output)
// 	    printf("Output redirection: %s\n", cmd->output);
// 		if (cmd->delimiter)
// 	    printf("Delimetr: %s\n", cmd->delimiter);
// 		if (cmd->LT)
// 			printf("LT: %d\n", cmd->LT);
// 		if (cmd->GT)
// 			printf("GT: %d\n", cmd->GT);
// 		if (cmd->D_LT)
// 			printf("D_LT: %d\n", cmd->D_LT);
// 		if (cmd->D_GT)
// 			printf("D_GT: %d\n", cmd->D_GT);
// 	printf("\n");
// }
// void print_commands(t_minishell *shell)
// {
//     t_command *cmd = shell->commands;
//     while (cmd)
//     {
// 	    print_command(cmd);
// 	    cmd = cmd->next;
//     }
// }

// char *token_type_to_string(enum token_type type) {
// 	if (type == STRING) return "string";
// 	else if (type == PIPE) return "pipe";
// 	else if (type == S_QUOTE) return "single_quote";
// 	else if (type == D_QUOTE) return "double_quote";
// 	else if (type == GT) return "greater_than";
// 	else if (type == LT) return "less_than";
// 	else if (type == D_GT) return "double_greater_than";
// 	else if (type == D_LT) return "double_less_than";
// 	else if (type == MY_SPACE) return "space";
// 	else if (type == DOLLAR) return "dollar";
// 	else {
// 		printf("bug: unhandled token type: %d\n", type);
// 		exit(1);
// 	}
// }

// void print_token(t_lexer *token) {
// 	printf("%s(%s) ", token_type_to_string(token->type), token->content);
// }

// void print_tokens(t_lexer *tokens) {
// 	while (tokens) {
// 		print_token(tokens);
// 		tokens = tokens->next;
// 	}
// 	printf("\n");
// }



split_by_pipe_result	split_by_pipe(t_lexer *tokens)
{
	split_by_pipe_result	result;
	t_lexer					*next_token;

	result.command = 0;
	result.rest = 0;
	while (tokens && tokens->type != PIPE)
	{
		next_token = tokens->next;
		tokens->next = 0;
		add_token_to_list(&result.command, tokens);
		tokens = next_token;
	}
	if (tokens == NULL)
	{
		return result;
	}
	next_token = tokens->next;
	free(tokens->content);
	free(tokens);
	result.rest = next_token;

	return result;
}

void handle_redirection_token_helper(enum token_type type, char *string, t_command *command)
{
	if (type == GT)
	{
		command->GT = 1;
		command->output = string;
	}
	else if (type == LT)
	{
		command->LT = 1;
		command->input = string;
	}
	else if (type == D_GT)
	{
		command->D_GT = 1;
		command->output = string;
	}
	else if (type == D_LT)
	{
		command->D_LT = 1;
		command->delimiter = string;
	}
	else
	{
		printf("bug: unhandled token type: %d\n", type);
		exit(1); // заменить на ретерн
	}
}

void handle_redirection_token(enum token_type type, t_command *command, t_lexer **tokens)
{
	t_lexer *next_token = (*tokens)->next;
	if (next_token == 0)
		printf("ошибка\n"); // замнеить на вывод ошибки 
	char *string = next_token->content;
	handle_redirection_token_helper(type, string, command);
	*tokens = next_token->next;
}

void handle_redirection_tokens(t_lexer **tokens, t_command *command)
{
	// Assummed possible token types at this point: STRING, GT, LT, D_GT, D_LT.

	while (*tokens)
	{
		if ((*tokens)->type != STRING)
			handle_redirection_token((*tokens)->type, command, tokens);
		else
			tokens = &(*tokens)->next;
	}
}

void turn_single_quotes_into_strings(t_lexer *tokens)
{
	while (tokens)
	{
		if (tokens->type == S_QUOTE)
			tokens->type = STRING;
		tokens = tokens->next;
	}
}

void handle_argv_tokens_sanity_check(t_lexer *tokens)
{
	// Sanity check that all tokens are of type STRING.
	while (tokens)
	{
		if (tokens->type != STRING)
			printf("ошибка\n"); // надо написать чтобы выходил обратно в цикл 
		tokens = tokens->next;
	}
}

int count_argc(t_lexer *tokens)
{
	int argc = 0;

	while (tokens)
	{
		argc++;
		tokens = tokens->next;
	}

	return argc;
}

void handle_argv_tokens(t_lexer **tokens, t_command *command)
{
	// Assummed possible token types at this point: STRING.
	
	handle_argv_tokens_sanity_check(*tokens);

	int argc = count_argc(*tokens);

	command->argv = malloc(sizeof(command->argv) * (argc + 1));
	command->argv[argc] = NULL;

	int i = 0;
	t_lexer *current_token;
    while (*tokens)
    {
        current_token = *tokens;
        command->argv[i] = current_token->content;
        i++;
        *tokens = current_token->next;

        // Освобождение памяти для текущего токена, но не для его содержимого
        // так как оно используется в command->argv
        free(current_token);
    }
	// while (*tokens)
	// {
	// 	command->argv[i] = (*tokens)->content;
	// 	i++;
	// 	tokens = &(*tokens)->next;
	// }
}

t_command *create_new_command()
{
	t_command *new_cmd;
	
	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
    {
        perror("Failed to allocate memory for new command"); //написать функцию очистки
        exit(EXIT_FAILURE);
    }
    new_cmd->argv = NULL;
	new_cmd->input = NULL;
	new_cmd->output = NULL;
    new_cmd->delimiter = NULL;
    new_cmd->heredoc = NULL;
    new_cmd->D_GT = 0;
    new_cmd->D_LT = 0;
    new_cmd->GT = 0;
    new_cmd->LT = 0;
    new_cmd->pipe = 0;
	new_cmd->next = NULL;
	return new_cmd;
}

t_command	*tokens_into_command(t_lexer *tokens)
{
	t_command *command = create_new_command();

	// By this point all dollar expansions should have already happened,
	// so it should be safe to turn single quotes into strings for easier processing
	// (by getting rid of an extra token type to check for).
	turn_single_quotes_into_strings(tokens);
	handle_redirection_tokens(&tokens, command);
	handle_argv_tokens(&tokens, command);

	
	// printf("Command after processing:\n\t");
    // print_tokens(tokens);
	// printf("\n");
    // print_command(command);
	// printf("\n");
	// printf("Command after processing:\n\t");
	// print_tokens(tokens);
	//print_command(command);

	return command;
}

// void create_commands_from_tokens(t_minishell *shell)
// {
// 	while (shell->lexer)
// 	{
// 		split_by_pipe_result result = split_by_pipe(shell->lexer);

// 		// printf("Command before processing:\n\t");
// 		// print_tokens(result.command);
// 		shell->commands = tokens_into_command(result.command);
// 		// (void)command;
// 		shell->lexer = result.rest;
// 	}
// 	printf("COMMANDS = \n");
//     print_command(shell->commands);
// 	shell->len = list_size(shell->commands);
// }


void add_command_to_list(t_command **list, t_command *new_command) {
    if (*list == NULL) {
        *list = new_command;
    } else {
        t_command *current = *list;
        while (current->next) {
            current = current->next;
        }
        current->next = new_command;
    }
}

void create_commands_from_tokens(t_minishell *shell)
{
	split_by_pipe_result result;
	t_command *command;

	command = NULL;
	shell->commands = NULL;
	
	while (shell->lexer)
	{
		result = split_by_pipe(shell->lexer);
		command = tokens_into_command(result.command);
		add_command_to_list(&shell->commands, command);
		shell->lexer = result.rest;
    }

    shell->len = list_size(shell->commands);
}


// void add_command_to_list(t_command **cmd_list, t_command **last_cmd, t_command *new_cmd)
// {
// 	if (!*cmd_list)
// 		*cmd_list = new_cmd;
// 	else
// 		(*last_cmd)->next = new_cmd;
// 	*last_cmd = new_cmd;
// }

// void handle_redirections_and_heredoc(t_command *new_cmd, t_lexer **current)
// {
//     while (*current && (*current)->type != STRING)
//     {
//         if (strcmp((*current)->content, "<") == 0)
//         {
//             *current = (*current)->next;
//             if (*current && (*current)->type == STRING)
//             {
//                 // new_cmd->type = LT;
//                 new_cmd->LT = 1;
//                 new_cmd->input = ft_strdup((*current)->content);
//                 *current = (*current)->next;
//             }
//         }
//         else if (strcmp((*current)->content, ">") == 0)
//         {
//             *current = (*current)->next;
//             if (*current && (*current)->type == STRING)
//             {
//                 // new_cmd->type = GT;
//                 new_cmd->GT = 1;
//                 new_cmd->output = ft_strdup((*current)->content);
//                 *current = (*current)->next;
//             }
//         }
//         else if (strcmp((*current)->content, ">>") == 0)
//         {
//             *current = (*current)->next;
//             if (*current && (*current)->type == STRING)
//             {
//                 // new_cmd->type = D_GT;
//                 new_cmd->D_GT = 1;
//                 new_cmd->output = ft_strdup((*current)->content);
//                 *current = (*current)->next;
//             }
//         }
//         else if (strcmp((*current)->content, "<<") == 0)
//         {
//             *current = (*current)->next;
//             if (*current && (*current)->type == STRING)
//             {
//                 // new_cmd->type = D_LT;
//                 new_cmd->D_LT = 1;
//                 new_cmd->delimiter = ft_strdup((*current)->content);
//                 *current = (*current)->next;
//             }
//         }
//         else if (strcmp((*current)->content, "|") == 0)
//         {
//             *current = (*current)->next;
//             break;
//         }
//     }
// }

// void fill_command_argv(t_command *cmd, t_lexer **current)
// {
// 	int argc;
// 	int i;
// 	t_lexer *temp;

// 	argc = 0;
// 	temp = *current;
// 	while (temp && (temp->type == STRING || temp->type == S_QUOTE))
// 	{
// 		argc++;
// 		temp = temp->next;
// 	}
// 	cmd->argv = malloc((argc + 1) * sizeof(char *));
// 	if (!cmd->argv)
//     {
//         perror("Failed to allocate memory for arguments"); //написать функцию очистки 
//         exit(EXIT_FAILURE);
//     }
// 	i = 0;
// 	while (*current && ((*current)->type == STRING || (*current)->type == S_QUOTE))
// 	{
// 		cmd->argv[i++] = ft_strdup((*current)->content);
// 		*current = (*current)->next;
// 	}
// 	cmd->argv[i] = NULL;
// }


// void create_commands_from_tokens(t_minishell **shell)
// {
// 	t_lexer *current;
// 	t_command *cmd_list;
// 	t_command *last_cmd;
// 	t_command *new_cmd;

// 	current = (*shell)->lexer;
// 	cmd_list = NULL;
// 	last_cmd = NULL;
// 	while (current)
// 	{
// 		new_cmd = create_new_command();
// 		fill_command_argv(new_cmd, &current);
// 		handle_redirections_and_heredoc(new_cmd, &current);
// 		add_command_to_list(&cmd_list, &last_cmd, new_cmd);
// 	}
// 	(*shell)->commands = cmd_list;
// 	(*shell)->len = list_size((*shell)->commands);
// }
