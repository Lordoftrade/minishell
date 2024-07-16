/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:48:31 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:25:31 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_command *command)
{
	if (!command)
		return (0);
	while (command->next)
	{
		if (command->gt || command->lt || command->d_gt || command->d_lt)
			return (1);
		command = command->next;
	}
	if (command->gt || command->lt || command->d_gt || command->d_lt)
		return (1);
	return (0);
}

int	redir_heredoc_pipe(t_command *cmd, int i)
{
	int	fd;

	cmd->heredoc = create_heredoc_filename(i);
	fd = open(cmd->heredoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
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
	if (!tmp)
		return (NULL);
	res = ft_strjoin("/tmp/minishell-heredoc-", tmp);
	if (!res)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (res);
}

int	execute_redirects(t_command **command)
{
	if ((*command)->gt)
		return (gt(command));
	else if ((*command)->d_gt)
		return (d_gt(command));
	else if ((*command)->lt)
		return (lt(command));
	return (0);
}

int	list_size(t_command *cmd)
{
	int	i;

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
