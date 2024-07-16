/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*cur;

	if (!value || !env)
		return (FAILURE);
	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	new->next = NULL;
	cur = env;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new;
	return (SUCCESS);
}

char	*getenv_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[PATH_SIZE];
	size_t	var_name_len;

	getenv_name(var_name, args);
	var_name_len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->value, var_name, var_name_len) == 0
			&& (env->value[var_name_len] == '='
				|| env->value[var_name_len] == '\0'))
		{
			ft_free_chr(env->value);
			env->value = ft_strdup(args);
			if (!env->value)
				return (FAILURE);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (FAILURE);
}
