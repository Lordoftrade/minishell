/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:39:32 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/05 13:12:07 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_redirect_pipe(t_command *curr)
{
	if (curr && (curr->GT || curr->LT || curr->D_GT))
		if(execute_redirects(&curr) == 0)
			return(1);
	return(0);
}

void	handle_parent_process(int *prev_fd, int fd[2], t_command **curr)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	*prev_fd = fd[0];
	if ((*curr)->next)
		close(fd[1]);
	*curr = (*curr)->next;
}

void	setup_child_pipes(int prev_fd, int fd[2], t_command *curr)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (curr->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

int	execute_command_for_pipe(t_command *curr, t_minishell *shell)
{

	if (curr->argv[0] && is_command_implemented(curr->argv[0]))
		execute_implemented(curr->argv, shell); // что вернуть должно
	else
		execute_bin(curr->argv, shell);
	return (0);
}

int	create_and_execute_child(t_command *curr, int prev_fd, int fd[2], t_minishell *shell)
{
	int pid;
	pid = fork();
	
	if (pid == 0)
	{
		setup_child_pipes(prev_fd, fd, curr);
		// if (check_redirect(curr))
		if(curr->GT || curr->LT || curr->D_GT || curr->D_LT)
			execute_redirect_pipe(curr);
		execute_command_for_pipe(curr, shell); //добавить проверку что команда выполнилась
		exit(0); 
	}
	return (pid);
}


int	create_pipe(int fd[2])
{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			return -1;
		}
	return (0);
}

void execute_pipeline_one_by_one(t_minishell *shell)
{
	t_command	*curr;
	int			fd[2];
	int			prev_fd;
	int			pid;
	int			status;
	int			i;
	int			last_pid;

	i = 0;
	curr = shell->commands;
	prev_fd = -1;
	last_pid = -1;
	while (curr)
	{
		if (curr->D_LT)
			redir_heredoc(&curr);
		if(curr->next)
		{
			if (create_pipe(fd) == -1)
				exit(EXIT_FAILURE); //подумать как должно выходить 
		}
		last_pid = create_and_execute_child(curr, prev_fd, fd, shell);
		handle_parent_process(&prev_fd, fd, &curr);
	}
	// while(i < shell->len)
	// {
	// 	wait(&(shell->exit_code));
	// 	shell->exit_code = WEXITSTATUS(shell->exit_code);
	// 	i++;
	// }
	while (i < shell->len)
	{
		pid = wait(&status);
		if (pid == last_pid)
			shell->exit_code = WEXITSTATUS(status);
		i++;
	}
}

int	check_pipe(t_minishell *shell)
{
	if(shell->len > 1)
		return(1);
	return(0);
}