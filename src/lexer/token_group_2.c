/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_group_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:52:50 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/10 18:14:29 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(S_QUOTE, content, shell);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
	(*i)++;
}
void	double_quote_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(D_QUOTE, content, shell);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
	(*i)++;
}

void	space_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(MY_SPACE, content, shell);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}

void	string_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = (*i);
	while (str[*i] && str[*i] != ' ' && str[*i] != '|' && str[*i] != '"' && str[*i] != '\'' && str[*i] != '>' && str[*i] != '<')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	if(!content)
		errors_memory(shell, 1);
	new_token = create_new_token(STRING, content, shell);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}