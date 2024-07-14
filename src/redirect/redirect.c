/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:33:17 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 20:56:38 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_heredoc(int i, char *delimiter)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strcmp(input, delimiter) == 0)
			break ;
		write(i, input, ft_strlen(input));
		write(i, "\n", 1);
		free(input);
	}
	free(input);
}

int	redir_heredoc(t_command **command)
{
	int			fd;
	t_command	*cmd;

	cmd = *command;
	cmd->heredoc = create_heredoc_filename(0);
	fd = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_error(1, ": No such file or directory\n");
		return (1);
	}
	execute_heredoc(fd, cmd->delimiter);
	close(fd);
	fd = open(cmd->heredoc, O_RDONLY);
	if (fd < 0)
	{
		ft_error(1, ": No such file or directory\n");
		return (1);
	}
	unlink(cmd->heredoc);
	dup2(fd, STDIN_FILENO);
	close(fd);
	delete_heredoc(cmd);
	return (0);
}

int	run_redirect(t_command **current)
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

int	handling_redir(t_minishell **shell)
{
	t_command	*current;
	int			res;

	res = 0;
	current = (*shell)->commands;
	while (check_redirect(current))
	{
		res = run_redirect(&current);
		if (res)
			break ;
	}
	return (res);
}
