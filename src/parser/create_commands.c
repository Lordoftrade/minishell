/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:58:06 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/05 14:29:35 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_command_to_list(t_command **cmd_list, t_command **last_cmd, t_command *new_cmd)
{
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
	}
	else
	{
		(*last_cmd)->next = new_cmd;
	}
	*last_cmd = new_cmd;
}

void handle_redirections_and_here_document(t_command *new_cmd, t_lexer **current)
{
    while (*current && (*current)->type != STRING)
    {
        if (strcmp((*current)->content, "<") == 0)
        {
            *current = (*current)->next;
            if (*current && (*current)->type == STRING)
            {
                // new_cmd->type = LT;
                new_cmd->LT = 1;
                new_cmd->input = ft_strdup((*current)->content);
                *current = (*current)->next;
            }
        }
        else if (strcmp((*current)->content, ">") == 0)
        {
            *current = (*current)->next;
            if (*current && (*current)->type == STRING)
            {
                // new_cmd->type = GT;
                new_cmd->GT = 1;
                new_cmd->output = ft_strdup((*current)->content);
                *current = (*current)->next;
            }
        }
        else if (strcmp((*current)->content, ">>") == 0)
        {
            *current = (*current)->next;
            if (*current && (*current)->type == STRING)
            {
                // new_cmd->type = D_GT;
                new_cmd->D_GT = 1;
                new_cmd->output = ft_strdup((*current)->content);
                *current = (*current)->next;
            }
        }
        else if (strcmp((*current)->content, "<<") == 0)
        {
            *current = (*current)->next;
            if (*current && (*current)->type == STRING)
            {
                // new_cmd->type = D_LT;
                new_cmd->D_LT = 1;
                new_cmd->delimiter = ft_strdup((*current)->content);
                *current = (*current)->next;
            }
        }
        else if (strcmp((*current)->content, "|") == 0)
        {
            *current = (*current)->next;
            break;
        }
    }
}


void fill_command_argv(t_command *cmd, t_lexer **current)
{
	int argc;
	int i;
	t_lexer *temp;

	argc = 0;
	temp = *current;
	while (temp && (temp->type == STRING || temp->type == S_QUOTE))
	{
		argc++;
		temp = temp->next;
	}
	cmd->argv = malloc((argc + 1) * sizeof(char *));
	if (!cmd->argv)
    {
        perror("Failed to allocate memory for arguments"); //написать функцию очистки 
        exit(EXIT_FAILURE);
    }
	i = 0;
	while (*current && ((*current)->type == STRING || (*current)->type == S_QUOTE))
	{
		cmd->argv[i++] = ft_strdup((*current)->content);
		*current = (*current)->next;
	}
	cmd->argv[i] = NULL;
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
    // new_cmd->type = 0;
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

void create_commands_from_tokens(t_minishell **shell)
{
	t_lexer *current;
	t_command *cmd_list;
	t_command *last_cmd;
	t_command *new_cmd;

	current = (*shell)->lexer;
	cmd_list = NULL;
	last_cmd = NULL;
	while (current)
	{
		new_cmd = create_new_command();
		fill_command_argv(new_cmd, &current);
		handle_redirections_and_here_document(new_cmd, &current);
		add_command_to_list(&cmd_list, &last_cmd, new_cmd);
	}
	(*shell)->commands = cmd_list;
    (*shell)->len = list_size((*shell)->commands);
}
