/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:43:45 by lelichik          #+#    #+#             */
/*   Updated: 2024/07/14 18:31:08 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_memory(t_minishell *shell, int error_code)
{
	free_minishell(shell);
	printf("Error: Unable to allocate memory.\n");
	exit(error_code);
}

void	ft_error_redir(char *arg, char *mesg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(mesg, 2);
}

void	ft_error_put(int code, char *com, char *arg, char *mesg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(com, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(mesg, 2);
	g_error = code;
}

void	ft_error(int error_code, char *errmsg)
{
	g_error = error_code;
	write(2, "minishell: ", 12);
	ft_putstr_fd(errmsg, 2);
}
void	ft_contral_d(t_minishell *shell)
{
			printf("exit\n");
			free_minishell(shell);
			exit(g_error);
}