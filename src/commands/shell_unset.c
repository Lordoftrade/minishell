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


int	remove_from_export(char ***export, const char *name)
{
	int i;
	int k;
	int j;
	int len;
	char **new_export;
	int count;

	i = 0;
	count = count_elements(*export);
	len = strlen(name);
	while ((*export)[i])
	{
		if (strncmp((*export)[i], name, len) == 0 && ((*export)[i][len] == '=' || (*export)[i][len] == '\0'))
			break;
		i++;
	}
	if (!(*export)[i])
		return (FAILURE);
	new_export = (char **)malloc(sizeof(char *) * count);
	if (!new_export)
		return (FAILURE);
	j = 0;
	k = 0;
	while ((*export)[j])
	{
		if (j != i)
		{
			new_export[k] = (*export)[j];
			k++;
		}
		else
			free((*export)[j]);
		j++;
	}
	new_export[count - 1] = NULL;
	free(*export);
	*export = new_export;
	return (SUCCESS);
}


int	ft_unsetenv(const char *name, t_env **env)
{
	t_env	*prev;
	t_env	*current;
	int	len;

	len = strlen(name);
	prev = NULL;
	current = *env;
	while (current)
	{
		if (strncmp(current->value, name, len) == 0
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
