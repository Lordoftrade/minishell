/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:31:35 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/16 20:31:35 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder.h"

int		len_env_value(const char *env)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] ==  '=')
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
	env_value = malloc(sizeof(char) * len_alloc);
	if (!env_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (value[i] ==  '=')
		i++;
	while (value[i])
		env_value[j++] = value[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*getenv_name(char *dest, const char *src)
{
	int		i;

	if (ft_strlen(src) >= PATH_SIZE)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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
		if (ft_strncmp(arg, env_name, arg_len) == 0 && env->value[arg_len] == '=')
		{
			value = env_value(env->value);
			return (value);
		}
		env = env->next;
	}
	return (ft_strdup(""));
}


t_env *create_env_node(char *value)
{
	t_env *new_node;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		perror("Failed to duplicate string");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env **env, char *value)
{
	t_env *new_node;
	t_env *cur;
	
	new_node = create_env_node(value);
	if (*env == NULL)
		*env = new_node;
	else
	{
		cur = *env;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_node;
	}
}
