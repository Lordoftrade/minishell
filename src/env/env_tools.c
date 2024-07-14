/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:21:27 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/15 21:21:27 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_env(t_env *env)
{
	size_t	count;
	t_env	*cur;

	count = 0;
	cur = env;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

int	len_env_value(const char *env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] == '=')
		i++;
	while (env[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	*env_value(char *value)
{
	int		i;
	int		j;
	int		len_alloc;
	char	*env_value;

	len_alloc = len_env_value(value) + 1;
	env_value = (char *)malloc(sizeof(char) * len_alloc);
	if (!env_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (value[i] == '=')
		i++;
	while (value[i])
		env_value[j++] = value[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*value;
	size_t	arg_len;

	arg_len = ft_strlen(arg);
	value = NULL;
	while (env && env->value)
	{
		getenv_name(env_name, env->value);
		if (ft_strncmp(arg, env_name, arg_len) == 0
			&& env->value[arg_len] == '=')
		{
			value = env_value(env->value);
			return (value);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

