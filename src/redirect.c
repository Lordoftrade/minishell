/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:33:17 by lelichik          #+#    #+#             */
/*   Updated: 2024/06/28 18:40:15 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

void delete_redirect(t_command **cmd, t_command **head, t_command **prev)
{
	t_command	*tmp;

	if (!cmd || !*cmd)
        return;
	if (*cmd == *head)
		*head = (*head)->next;
	else
		(*prev)->next = (*cmd)->next;
	tmp = *cmd;
	*cmd = (*cmd)->next; // Перемещаемся к следующей команде
	free_command(tmp); // Освобождаем память, занятую текущей командой
}

void	previous(t_command **previous, t_command **command)
{
	if (!(*previous || *command))
		return ;
	*previous = *command;
	*command = (*command)->next;
}

void	start(t_command **s, t_command **c, t_command **prev, t_minishell **sh)
{
	*s = (*sh)->commands;
	while ((*sh)->commands->type == D_LT)
		previous(prev, c);
}

int	gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		return(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to redirect stdout");
		return(1);
	}
	return (0);
}

int	d_gt(t_command **command)
{
	int	fd;

	fd = open((*command)->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Failed to open output file");
		return(1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to redirect stdout");
		close(fd);
		return(1);
	}
	return (0);
}
int lt(t_command **command)
{
	int fd;

	fd = open((*command)->input, O_RDONLY);
	if (fd < 0)
	{
		perror("Failed to open input file"); // Выводим сообщение об ошибке
		return (1);  // Возвращаем код ошибки
	}
	if (dup2(fd, STDIN_FILENO) < 0)  // Перенаправляем файловый дескриптор ввода
	{
		perror("Failed to redirect stdin"); // Выводим сообщение об ошибке
		close(fd);  // Закрываем файл
		return (1);  // Возвращаем код ошибки
	}
	return (0);  // Возвращаем успешное выполнение
}

int	execute_redirects(t_command **command)
{
	if ((*command)->type == GT)
		return (gt(command));
	else if ((*command)->type == D_GT)
		return (d_gt(command));
	else if ((*command)->type == LT)
		return (lt(command));
	return (0);
}

int	do_redir(t_command **c, t_command **p, t_command **s)
{
	if ((*c) && ((*c)->type == GT || (*c)->type == LT || (*c)->type == D_GT))
	{
		if (execute_redirects(c))
		{
			delete_redirect(c, s, p);
			return (1);
		}
		else
			delete_redirect(c, s, p);
	}
	else
		previous(p, c);
	return (0);
}


int	run_redirect(t_command **current, t_command **previous) // потом добавить t_minishell **shell
{
	t_command	*start;

	start = NULL;
	// if (check_heredoc((*shell)->commands))
	// {
	// 	set_start(&start, command, previous, shell);
	// 	if ((*command)->type == D_LT)
	// 	{
	// 		do_here_doc((*t)->next->data, *mh);
	// 		if (do_dups(t, mh))
	// 			return (1);
	// 		delete_redirs(t, mh, previous, &start);    заняться это частью когда подойду к пайпам
	// 		if (start)
	// 		{
	// 			(*mh)->token = start;
	// 			*t = start;
	// 			*previous = start;
	// 		}
	// 		return (0);
	// 	}
	// }
	if (do_redir(current, previous, &start))
		return (1);
	return (0);
}


int	handling_redir(t_minishell *shell) // потом добавить t_command *commands,
{
	t_command *current;
	t_command *previous;
	int res;

	res = 0;
	current = shell->commands;
	previous = current;
	// if (bad_redirect_syntax(t))
	// {
	// 	pr_err(mh, 258, gemsg("", mh->emsg[15], "")); написать функцию для проверки синтаксиса и вывода ошибки
	// 	return (258);
	// }
		while (current && check_redirect(current))
		{
			res = run_redirect(&current, &previous);
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
		if (command->type == GT || command->type == LT || command->type == D_GT || command->type == D_LT)
			return (1);
		command = command->next;
	}
	if (command->type == GT || command->type == LT || command->type == D_GT || command->type == D_LT)
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