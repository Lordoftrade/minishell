/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:54:23 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/05 14:49:18 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_dollar(char *str, int *i, t_minishell *shell)
{
	int	start;
	char *var_name;
	char *env_value;

	// if (str[*i] == '$' && str[*i + 1] == '?')
	// 	вызвать функцию для знака вопроса
	
		start = *i;
		(*i)++;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		var_name = ft_strndup(&str[start + 1], *i - start - 1);
		if (!var_name)
			return NULL;
		env_value = get_env_value(var_name, shell->env);
		free(var_name);
		return(env_value);
}

void	process_dollar(char *string, int *i, t_minishell *shell, char **result)
{
	char	*env_value;

	env_value = open_dollar(string, i, shell);
	if (env_value)
	{
		*result = ft_mystrjoin(*result, env_value); // Добавляем значение переменной окружения в результат
		free(env_value);
	}
}

void	process_other_chars(char *string, int *i, char **result)
{
	char *temp;

	temp = ft_strndup(&string[*i], 1);
	*result = ft_mystrjoin(*result, temp); // Добавляем символ в результат
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
	{
		perror("Failed to duplicate token content"); // вызов функции которая все почистит и выдаст ошибку
		exit(EXIT_FAILURE);
	}
	result = ft_strdup(""); // Инициализируем пустой результат
	if (!result)
	{
		free(string);
		perror("Failed to allocate memory for result"); // вызов функции которая все почистит и выдаст ошибку
		exit(EXIT_FAILURE);
	}
	while (string[i])
	{
		if (string[i] == '$')
			process_dollar(string, &i, shell, &result);
		else
			process_other_chars(string, &i, &result);
	}
	(*token)->type = STRING;
	free((*token)->content); // Освобождаем старое содержимое лексемы
	(*token)->content = result; // Присваиваем лексеме новое значение
	free(string); // Освобождаем временную строку
}

int	is_breaking_character(char	c)
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
	if (!string)
	{
        free(shell);
        free(token); // Добавить функцию по очистке списка при необходимости
        return;
	}
	i = 1;
	// if (string[i] == '?')
	// 	написать функцию по знаку вопроса
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
