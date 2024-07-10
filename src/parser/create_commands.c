/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:58:06 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/10 23:40:23 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

split_by_pipe_result split_by_pipe(t_lexer *tokens) {
	split_by_pipe_result result;
	t_lexer *next_token;

	result.command = 0;
	result.rest = 0;
	while (tokens && tokens->type != PIPE) {
		next_token = tokens->next;
		tokens->next = 0;
		add_token_to_list(&result.command, tokens);
		tokens = next_token;
	}

	if (tokens == NULL) {
		return result;
	}

	next_token = tokens->next;
	free(tokens->content);
	free(tokens);
	result.rest = next_token;

	return result;
}

// void	create_commands_from_tokens(t_minishell **shell)
// {
// 	t_lexer *current;
// 	t_command *cmd_list;
// 	t_command *new_cmd;
// 	t_command *last_cmd;

// 	current = (*shell)->lexer;
// 	cmd_list = NULL;
// 	last_cmd = NULL;
// 	while(current && current->type != PIPE)
// 	{
		
// 	}
// }








void add_command_to_list(t_command **cmd_list, t_command **last_cmd, t_command *new_cmd)
{
	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
		(*last_cmd)->next = new_cmd;
	*last_cmd = new_cmd;
}

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
// 	while (temp)
// 	{
// 			if (temp->type == STRING || temp->type == S_QUOTE)
//             	argc++;
// 			temp = temp->next;
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
// 		if ((*current)->type == STRING || (*current)->type == S_QUOTE)
//             cmd->argv[i++] = ft_strdup((*current)->content);
// 		*current = (*current)->next;
// 	}
// 	cmd->argv[i] = NULL;
// }

// void fill_command_argv(t_command *new_cmd, t_lexer **current)
// {
//     int argc = 0;
//     int argv_size = 10;
//     char **argv = malloc(sizeof(char *) * argv_size);

//     if (!argv)
//     {
//         perror("Failed to allocate memory for argv");
//         exit(EXIT_FAILURE);
//     }

//     while (*current && ((*current)->type == STRING || (*current)->type == S_QUOTE || (*current)->type == D_QUOTE))
//     {
//         if (argc >= argv_size)
//         {
//             argv_size *= 2;
//             argv = realloc(argv, sizeof(char *) * argv_size);
//             if (!argv)
//             {
//                 perror("Failed to reallocate memory for argv");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         argv[argc++] = ft_strdup((*current)->content);
//         *current = (*current)->next;
//     }

//     argv[argc] = NULL;
//     new_cmd->argv = argv;
// }

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

// // cat > hi hello | cat > bye goodbye

// // cat > hi hello
// // cat > bye goodbye

// // commands = split_by_pipe();
// // i = 0
// // while (i != commands.size) {
// // 	delete_redirects(commands[i]);
// // }

// // if (token.type == D_LT) {
// // 	if (token->next.type != STRING) {
// // 		ft_error("expected a string after a redirection");
// // 	} else {
// // 		cmd->d_lt = ...;
// // 		token = token->next->next;
// // 	}
// // }

// void add_argument_to_command(t_command *cmd, char *content)
// {
//     int argc = 0;

//     // Считаем количество существующих аргументов
//     while (cmd->argv && cmd->argv[argc])
//         argc++;

//     // Выделяем новую память для аргументов, включая новый аргумент
//     char **new_argv = malloc((argc + 2) * sizeof(char *));
//     if (!new_argv)
//     {
//         perror("Failed to allocate memory for argv");
//         // Добавить функцию очистки и выхода
//         exit(EXIT_FAILURE);
//     }

//     // Копируем старые аргументы в новый массив
//     for (int i = 0; i < argc; i++)
//     {
//         new_argv[i] = cmd->argv[i];
//     }

//     // Освобождаем старый массив аргументов, если он существует
//     if (cmd->argv)
//         free(cmd->argv);

//     // Добавляем новый аргумент в конец массива
//     new_argv[argc] = ft_strdup(content);
//     new_argv[argc + 1] = NULL;

//     // Обновляем указатель argv на новый массив
//     cmd->argv = new_argv;
// }

// void	create_commands_from_tokens(t_minishell **shell)
// {
// 	t_lexer *current;
// 	t_command *cmd_list;
// 	t_command *new_cmd;
// 	t_command *last_cmd;

// 	current = (*shell)->lexer;
// 	cmd_list = NULL;
// 	last_cmd = NULL;
// 	while (current)
// 	{
// 		new_cmd = create_new_command();
// 		while (current && current->type != PIPE)
// 		{
// 			if (current->type == STRING || current->type == S_QUOTE || current->type == D_QUOTE) //  скорее всего двойные кавычки не нужны
// 			{
// 				add_argument_to_command(new_cmd, current->content);
// 				current = current->next;
// 			}
// 			else
// 				handle_redirections_and_heredoc(new_cmd, &current);
// 		}
// 		if (current && current->type == PIPE)
// 		{
// 			new_cmd->pipe = 1; // проверить нужно ли 
// 			current = current->next;
// 		}
// 		add_command_to_list(&cmd_list, &last_cmd, new_cmd);
// 	}
// 	(*shell)->commands = cmd_list;
// 	(*shell)->len = list_size((*shell)->commands);
// }

// void	create_commands_from_tokens(t_minishell **shell)
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
