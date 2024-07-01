/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:33:17 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/01 12:56:41 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

// void	previous(t_command **previous, t_command **command)
// {
// 	if (!(*previous || *command))
// 		return ;
// 	*previous = *command;
// 	*command = (*command)->next;
// }

// void	start(t_command **s, t_command **c, t_command **prev, t_minishell **sh)
// {
// 	*s = (*sh)->commands;
// 	while ((*sh)->commands->type == D_LT)
// 		previous(prev, c);
// }

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

int	do_redir(t_command **c)
{
	if ((*c) && ((*c)->type == GT || (*c)->type == LT || (*c)->type == D_GT))
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


int	run_redirect(t_command **current) // потом добавить t_minishell **shell
{
	// t_command	*start;

	// start = NULL;
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
	if (do_redir(current))
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
	printf("%d\n", res);
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