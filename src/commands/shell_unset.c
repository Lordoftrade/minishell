/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 21:15:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/14 21:15:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_new_array_without_element(char **array, int remove_index, int count)
{
	char	**new_array;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new_array = (char **)malloc(sizeof(char *) * count);
	if (!new_array)
		return (NULL);
	while (array[j])
	{
		if (j != remove_index)
		{
			new_array[k] = ft_strdup(array[j]);
			if (!new_array[k])
			{
				free_string_array(new_array);
				return (NULL);
			}
			k++;
		}
		j++;
	}
	new_array[count - 1] = NULL;
	return (new_array);
}

int	find_element_index(char **array, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (array[i])
	{
		if (ft_strncmp(array[i], name, len) == 0 && (array[i][len] == '=' || array[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}


int	remove_from_export(char ***export, const char *name)
{
	int		i;
	char	**new_export;
	int		count;

	i = find_element_index(*export, name);
	if (i == -1)
		return (FAILURE);
	count = count_elements(*export);
	if (!(*export)[i])
		return (FAILURE);
	new_export = create_new_array_without_element(*export, i, count);
	if (!new_export)
		return (FAILURE);
	free_string_array(*export);
	*export = new_export;
	return (SUCCESS);
}

int	ft_unsetenv(const char *name, t_env **env)
{
	t_env	*prev;
	t_env	*current;
	int		len;

	len = ft_strlen(name);
	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->value, name, len) == 0
			&& (current->value[len] == '=' || current->value[len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->value);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (FAILURE);
}

int	shell_unset(char **args, t_minishell *shell)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		return (0);
	while (args[i])
	{
		ft_unsetenv(args[i], &shell->env);
		remove_from_export(&(shell->export), args[i]);
		i++;
	}
	return (SUCCESS);
}
