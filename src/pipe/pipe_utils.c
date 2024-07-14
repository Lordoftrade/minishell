/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:49:54 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 20:45:44 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_minishell *shell)
{
	if (shell->len > 1)
		return (1);
	return (0);
}

int	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}
