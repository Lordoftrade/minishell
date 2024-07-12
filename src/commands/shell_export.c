/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:15:44 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/12 21:15:44 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	bubble_sort_env(char **env_array, size_t env_count)
{
	char	*temp;
	char	**array;
	size_t	i;
	size_t	j;

	array = env_array;
	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			if (ft_strcmp(array[j], array[j + 1]) > 0) // написать код или подумать из либфт
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**sort_env(char **export)
{
	size_t	count;
	size_t	i;
	char	**env_array;

	count = count_elements(export);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_strdup(export[i]);
		if (!env_array[i])
		{
			free_string_array(env_array); // выводим ошибку?
			return (NULL);
		}
		i++;
	}
	env_array[i] = NULL;
	bubble_sort_env(env_array, count);
	return (env_array);
}

void	print_env_sort(char **export)
{
	char	**env_array;
	int		i;

	i = -1;
	env_array = sort_env(export);
	if (!env_array)
	{
		perror("Error sorting environment variables");
		return ;
	}
	while (env_array[++i])
		printf("declare -x %s\n", env_array[i]);
	free_string_array(env_array);
}

void	ft_export_while_varable(char **args, t_minishell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			ft_error_put(1, args[0], args[i], "': not a valid identifier\n");
		else
		{
			if (ft_strchr(args[i], '='))
			{
				if (is_in_env(shell->env, args[i]) == FAILURE)
					add_env(args[i], shell->env);
				if (is_in_env_array(&(shell->export), args[i]) == FAILURE)
					add_to_export(&(shell->export), args[i]);
			}
			else
			{
				if (is_in_env_array(&(shell->export), args[i]) == FAILURE)
					add_to_export(&(shell->export), args[i]);
			}
		}
		i++;
	}
}

int	shell_export(char **args, t_minishell *shell)
{
	g_error = 0;
	if (!args[1])
	{
		print_env_sort(shell->export);
		return (SUCCESS);
	}
	ft_export_while_varable(args, shell);
	return (g_error);
}
