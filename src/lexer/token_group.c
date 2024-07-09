/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:44:21 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/05 15:02:49 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lt_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	if(str[*i] && str[*i + 1] == '<')
		(*i) += 2;
	else 
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	if (str[start] && str[start + 1] == '<')
		new_token = create_new_token(D_LT, content);
	else
		new_token = create_new_token(LT, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}

void	gt_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	if(str[*i] && str[*i + 1] == '>')
		(*i) += 2;
	else 
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	if (str[start] && str[start + 1] == '>')
		new_token = create_new_token(D_GT, content);
	else
		new_token = create_new_token(GT, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}

void	dollar_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'|| str[*i] == '?' || str[*i] == '$'))
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(DOLLAR, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}

void	pipe_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	while (str[*i] && str[*i] == '|')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(PIPE, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}

