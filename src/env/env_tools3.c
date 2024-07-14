/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:21:27 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/15 21:21:27 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_list_to_array(t_env *env_list)
{
	char	**env_array;
	size_t	count;
	t_env	*current;
	size_t	i; 

	count = count_env(env_list);
	current = env_list;
	env_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return NULL;
	current = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i++] = ft_strdup(current->value);
		current = current->next;
	}
	env_array[count] = NULL;
	return env_array;
}

t_env	*create_env_node(char *value)
{
	t_env	*new_node;

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
	t_env	*new_node;
	t_env	*cur;

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