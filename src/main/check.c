/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:10:42 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/10 20:38:31 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (0);
	while(str[i])
	{
		if(str[i] && str[i] == '|' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	check_quote(char *str)
{
	int	single_quote_open;
	int	double_quote_open;
	int	i;

	i = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while(str[i])
	{
		if(str[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		if(str[i] == '"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		i++;
	}
	return !single_quote_open && !double_quote_open;
}

int	check_symbol(char *str)
{
	int		i;
	int		j;

	i = 2;
	j = 2;

	i = check_pipe_syntax(str);
	j = check_quote(str);
	if(j == 0 || i == 0)
		return(1);
	return(0);
}
int	check_argv(t_command *cmd)
{
	if(cmd == NULL)
		return (0);
	if(cmd->argv[0] == NULL)
		return(0);
	return(1);
}
void	check_sintax_redir(t_lexer *lexer)
{
	t_lexer *current = lexer;
	t_lexer *next;

	while (current && current->next)
	{
		next = current->next;
		if ((current->type == GT || current->type == D_GT || current->type == LT || current->type == D_LT) &&
			(next->type == GT || next->type == D_GT || next->type == LT || next->type == D_LT))
		{
			ft_error(258, "syntax error near unexpected token\n");
			return;
		}
		current = next; // Переходим к следующему токену
	}
}