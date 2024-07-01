/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:00 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/01 14:49:32 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_list_lexer(char *str, t_minishell *shell)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'')
			single_quote_token(str, &i, shell);
		else if (str[i] == '"')
			double_quote_token(str, &i, shell);
		else if (str[i] == ' ')
			space_token(str, &i, shell);
		else if (str[i] == '|')
			pipe_token(str, &i, shell);
		else if (str[i] == '$')
			dollar_token(str, &i, shell);
		else if (str[i] == '>')
			gt_token(str, &i, shell);
		else if (str[i] == '<')
			lt_token(str, &i, shell);
		else
			string_token(str, &i, shell);
	}
}

void	ft_lexer(char *line, t_minishell **shell)
{
	if(check_symbol(line) == 0)
	{
			printf("Errors quote\n"); // написать функцию для ошибки
			// free_minishell(shell);
	}
	to_list_lexer(line, *shell);
	// t_lexer *temp = (*shell)->lexer;
    // while (temp) {
    //     printf("Token type: %d, content: %s\n", temp->type, temp->content);
    //     temp = temp->next;
    // }
	free(line); // не знаю нужно ли чистить строку в которую ридлайн читал
	// parser((&(*shell)->lexer), shell);
	// t_lexer *tem = (*shell)->lexer;
    // while (tem) {
    //     printf("Token type new: %d, content new: %s\n", tem->type, tem->content);
    //     tem = tem->next;
    // }
}
