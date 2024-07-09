/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:33:17 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/08 15:59:11 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int redir_heredoc_pipe(t_command *cmd, int i)
{
    int fd;

    cmd->heredoc = create_heredoc_filename(i);

    fd = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open heredoc file");
        return (1);
    }
    execute_heredoc(fd, cmd->delimiter);
    close(fd);
    return (0);
}

char	*create_heredoc_filename(int i)
{
	char	*res;
	char	*tmp;
	
	tmp = ft_itoa(i);
	if(!tmp)
		return (NULL);
	res = ft_strjoin("/tmp/minishell-heredoc-", tmp);
	if(!res)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (res);
}

int	check_argv(t_command *cmd)
{
	if(cmd->argv[0] == NULL)
		return(0);
	return(1);
}

int	list_size(t_command *cmd)
{
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	execute_redirects(t_command **command)
{
	if ((*command)->GT)
		return (gt(command));
	else if ((*command)->D_GT)
		return (d_gt(command));
	else if ((*command)->LT)
		return (lt(command));
	return (0);
}

int	do_redir(t_command **c)
{
	if ((*c) && ((*c)->GT || (*c)->LT || (*c)->D_GT))
	{
		if (execute_redirects(c))
		{
			delete_redirect(c);
			return (1);
		}
		else
			delete_redirect(c);
	}
	return (0);
}
void	delete_heredoc(t_command *command)
{
		free(command->delimiter);
		free(command->heredoc);
		command->D_LT = 0;
		command->delimiter = NULL;
		command->heredoc = NULL;
}

void	execute_heredoc(int i, char *delimiter)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL) // Проверка на случай, если readline возвращает NULL
			break ;
		if (strcmp(input, delimiter) == 0) //написать функцию 
			break ;
		write(i, input, ft_strlen(input));
		write(i, "\n", 1);
		free(input);
	}
	free(input);
}


int redir_heredoc(t_command **command)
{
	int fd;
	t_command *cmd = *command;

	cmd->heredoc = create_heredoc_filename(0);
	fd = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		// error(": No such file or directory\n", shell, 2); //
		return (1);
	}
	execute_heredoc(fd, cmd->delimiter);
	close(fd);
	fd = open(cmd->heredoc, O_RDONLY);
	if (fd < 0)
	{
		// error(": No such file or directory\n", shell, 2);
		return (1);
	}
	unlink(cmd->heredoc);
	dup2(fd, STDIN_FILENO);
	close(fd);
	delete_heredoc(cmd);
	return (0);
}

int	run_redirect(t_command **current) // потом добавить t_minishell **shell
{
	if ((*current)->D_LT)
	{
		if (redir_heredoc(current) != 0)
			return (1);
	}
	else if (do_redir(current) != 0)
		return (1);
	return (0);
}

int	handling_redir(t_minishell **shell) // потом добавить t_command *commands,
{
	t_command	*current;
	int			res;

	res = 0;
	current = (*shell)->commands;
	// if (bad_redirect_syntax(t))
	// {
	// 	pr_err(mh, 258, gemsg("", mh->emsg[15], "")); написать функцию для проверки синтаксиса и вывода ошибки
	// 	return (258);
	// }
	while (check_redirect(current))
	{
		res = run_redirect(&current);
		if (res)
			break ;
	}
	return (res);
}

int	check_redirect(t_command *command)
{	
	if (!command)
		return (0);
	while (command->next)
	{
		if (command->GT || command->LT || command->D_GT || command->D_LT)
			return (1);
		command = command->next;
	}
	if (command->GT || command->LT || command->D_GT || command->D_LT)
		return (1);
	return (0);
}

// int	check_heredoc(t_command *commands)
// {
// 	t_command	*current;

// 	// if (!mh || !mh->token->data)
// 	// 	return (0);
// 	current = commands;
// 	while (current)
// 	{
// 		if (current->type == D_LT)
// 			return (1);
// 		current = current->next;
// 	}
// 	return (0);
// }