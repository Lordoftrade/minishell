/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/09 14:30:54 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_error = 130;
	write(1, "\n", 1); 
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	do_sigint_fork(int signal)
{
	(void)signal;
	g_error = 130;
	write(1, "\n", 1);
}
