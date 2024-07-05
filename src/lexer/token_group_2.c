/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_group_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:52:50 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/01 14:26:01 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quote_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	// if(!content)
	// {
	// 	//free_list (info);
	// 	//free_list(lexer);
	// }
	new_token = create_new_token(D_QUOTE, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
	(*i)++;
}

void	single_quote_token(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*content;
	t_lexer *new_token;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	content = ft_strndup(str + start, *i - start);
	// if(!content)
	// {
	// 	//free_list (info);
	// 	//free_list(lexer);
	// }
	new_token = create_new_token(S_QUOTE, content);
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
	// if(!content)
	// {
	// 	//free_list (info);
	// 	//free_list(lexer);
	// }
	new_token = create_new_token(SPACE, content);
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
	// if(!content)
	// {
	// 	//free_list (info);
	// 	//free_list(lexer);
	// }
	new_token = create_new_token(STRING, content);
	add_token_to_list(&(shell->lexer), new_token);
	free(content);
}