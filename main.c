/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/04 20:12:17 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

char	*ft_readline()
{
	char	*line;

	line = readline("minishell -> ");
	if(line == NULL)
		exit(0);
	add_history(line);
	return(line);
}

int	main(int argc, char *argv)
{
	t_minishell info;

	(void)argv;
	if(argc > 1)
	{
		printf("ошибка в количестве аргументов");
		exit(1);
	}
	info = malloc(sizeof(t_minishell));
	if(!info)
		exit(1);
	info.line = ft_readline("minishell -> ");
	lexer(&info);
}