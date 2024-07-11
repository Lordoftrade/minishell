/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:19:18 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/11 21:35:17 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*open_dollar(char *str, int *i, t_minishell *shell)
{
	int	start;
	char *var_name;
	char *env_value;

	if (str[*i + 1] == '?') //  $?
	{
		(*i) += 2;
		env_value = ft_itoa(g_error);
		return (env_value);
	}
	start = *i;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(&str[start + 1], *i - start - 1);
	if (!var_name)
		return (NULL);
	env_value = get_env_value(var_name, shell->env);
	free(var_name);
	return (env_value);
}

void	process_dollar(char *string, int *i, t_minishell *shell, char **result)
{
	char	*env_value;

	env_value = open_dollar(string, i, shell);
	if (env_value)
	{
		*result = ft_mystrjoin(*result, env_value);
		free(env_value);
	}
}

