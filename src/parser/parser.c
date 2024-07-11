/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:54:23 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/11 21:32:26 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_other_chars(char *string, int *i, char **result)
{
	char *temp;

	temp = ft_strndup(&string[*i], 1);
	*result = ft_mystrjoin(*result, temp);
	free(temp);
	(*i)++;
}

void	symbol_d_quote(t_lexer **token, t_minishell *shell)
{
	char	*string;
	char	*result;
	int		i;

	i = 0;
	string = ft_strdup((*token)->content);
	if (!string)
		errors_memory(shell, 1);
	result = ft_strdup(""); // Инициализируем пустой результат
	if (!result)
		errors_memory(shell, 1);
	while (string[i])
	{
		if (string[i] == '$')
			process_dollar(string, &i, shell, &result);
		else
			process_other_chars(string, &i, &result);
	}
	(*token)->type = STRING;
	free((*token)->content);
	(*token)->content = result;
	free(string);
}

int	is_breaking_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '$')
		return (1);
	return (0);
}

void	symbol_dollar(t_lexer **token, t_minishell *shell)
{
	char	*string;
	char	*new_string;
	char	*temp_string;
	int		i;

	string = ft_strdup((*token)->content);
	i = 1;
	if (string[i] == '?') // $?
	{
		free((*token)->content);
		(*token)->content = ft_itoa(g_error);
		(*token)->type = STRING;
		free(string);
		return ;
	}
	if (is_breaking_character(string[i]) || string[i] == '\0')
		(*token)->type = STRING;
	else
	{
		temp_string = string + 1;
		new_string = get_env_value(temp_string, shell->env);
		if (new_string)
		{
			(*token)->type = STRING;
			free((*token)->content);
			(*token)->content = new_string;
		}
	}
	free(string);
}


void	parser(t_lexer **tokens, t_minishell **shell)
{
	if((*shell)->f_success == 1)
	{
		t_lexer	*tmp;
		tmp = *tokens;
		while(tmp != NULL)
		{
			if(tmp->type == DOLLAR)
				symbol_dollar(&tmp, *shell);
			if(tmp->type == D_QUOTE)
				symbol_d_quote(&tmp, *shell);
			tmp = tmp->next;
		}
		tmp = *tokens;
		connect_tokens(&tmp, shell);
		tmp = *tokens;
		free_empty_token(&tmp, shell);
		tmp = *tokens;
		free_space(&tmp, shell);
	}
}
