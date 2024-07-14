/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:51:08 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 20:47:43 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(int *prev_fd, int read, int write,
		t_command **curr)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = read;
	if ((*curr)->next)
		close(write);
	*curr = (*curr)->next;
}

void	setup_child_pipes(int prev_fd, int read, int write,
		t_command *curr)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (curr->next)
	{
		close(read);
		dup2(write, STDOUT_FILENO);
		close(write);
	}
}

int	execute_redirect_pipe(t_command *curr)
{
	if (curr && (curr->GT || curr->LT || curr->D_GT))
		if (execute_redirects(&curr) == 1)
			return (1);
	return (0);
}

int	execute_command_for_pipe(t_command *curr, t_minishell *shell)
{
	if (curr->argv[0] && is_command_implemented(curr->argv[0]))
	{
		if (execute_implemented(curr->argv, shell))
			return (1);
	}
	else
	{
		if (ft_strchr(curr->argv[0], '/') != NULL)
		{
			if (ft_execve_file_and_path(curr->argv, shell))
				return (1);
		}
		else
		{
			if (execute_bin(curr->argv, shell))
				return (1);
		}
	}
	return (0);
}

void	execute_child_command(t_command *curr, t_minishell *shell)
{
	if (curr->GT || curr->LT || curr->D_GT)
	{
		if (execute_redirect_pipe(curr) == 1)
			exit(1);
	}
	if (execute_command_for_pipe(curr, shell) == 1)
		exit(1);
}
