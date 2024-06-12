/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//удалить и добавить либфт!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char *ft_strjoin(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return NULL;

    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *new = malloc(len1 + len2 + 1);

    if (!new)
        return NULL;

    strcpy(new, s1);
    strcpy(new + len1, s2);

    return new;
}

int	add_env(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*cur;

	if (!value || !env)
		return (FAILURE);
	if (env && env->value == NULL)
	{
		env->value = strdup(value); // надо ли добавлять код если функция не выделила память?
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1); // вывод ошибки и что делать, раз память не выделена?
	new->value = strdup(value); // надо ли добавлять код если функция не выделила память?
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

	if (strlen(src) >= PATH_SIZE)
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

int	is_in_env(t_env *env, char *args)
{
	char	var_name[PATH_SIZE];
	size_t	var_name_len;

	getenv_name(var_name, args);
	var_name_len = strlen(var_name);
	while (env)
	{
		if (strncmp(env->value, var_name, var_name_len) == 0
			&& env->value[var_name_len] == '=')
		{
			ft_free_chr(env->value);
			env->value = strdup(args); // надо добавить ? if (!env->value) return FAILURE
			return (SUCCESS);
		}
		env = env->next;
	}
	return (FAILURE);
}
