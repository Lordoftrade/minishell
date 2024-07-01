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

int	is_in_env_array(char ***export, char *args)
{
	char var_name[PATH_SIZE];
	size_t len;
	int i;

	i = 0;
	getenv_name(var_name, args);
	len = strlen(var_name); // linbft
	while ((*export)[i])
	{
		if (strncmp((*export)[i], var_name, len) == 0 &&
			((*export)[i][len] == '=' || (*export)[i][len] == '\0'))
		{
			///free((*export)[i]);
			add_to_export(export, args);
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}


int	update_export_var(char ***export, char *env_name, char *quoted_value, char *env_value_str)
{
	int i;
	size_t len;

	if (export == NULL || *export == NULL)
		return (0);
	i = 0;
	len = strlen(env_name); // либофт
	while ((*export)[i])
	{
		if (strncmp((*export)[i], env_name, len) == 0 &&
			((*export)[i][len] == '=' ||
				(*export)[i][len] == '\0'))
		{
			free((*export)[i]);
			if (quoted_value)
				(*export)[i] = strdup(quoted_value); // может не надо снова выделять память
            else
				(*export)[i] = strdup(env_name);
			free(env_value_str);
			free(quoted_value);
			return (1);
		}
		i++;
	}
	return (0);
}

void	add_to_export(char ***export, char *value)
{
	int		i;
	char	**new_export;
	char	env_name[BUFF_SIZE];
	char	*env_value_str;
	char	*quoted_value;

	i = 0;
	env_value_str = NULL;
	quoted_value = NULL;
	getenv_name(env_name, value);
	if (strchr(value, '='))
	{
		env_value_str = env_value(value); // надо ли проверку на выделение
		if (env_value_str == NULL)
			return ;
		quoted_value = add_quotes_to_value(env_name, env_value_str);
		if (quoted_value == NULL)
		{
			free(env_value_str);
			return ;
        }
	}
	if (update_export_var(export, env_name, quoted_value, env_value_str))
		return ;
	i = count_elements(*export);
	new_export = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_export)
	{
		free(env_value_str); // решить что делать тут
		free(quoted_value);
		return ;
	}
	copy_array(new_export, *export);
	if (quoted_value) 
		new_export[i] = quoted_value;
	else
		new_export[i] = strdup(env_name);
	new_export[i + 1] = NULL;
	free_string_array(*export);
	*export = new_export;
	free(env_value_str);
}

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
			if (strcmp(array[j], array[j + 1]) > 0) // написать код или подумать из либфт
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
		env_array[i] = strdup(export[i]); // библиотека
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


int	shell_export(char **args, t_minishell *shell)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		print_env_sort(shell->export);
		return (SUCCESS);
	}
	while (args[i])
	{
		if (is_valid_identifier(args[i]) == 0)
			printf("minishell: export: '%s': not a valid identifier\n",
				args[i]);
		else
		{
			if (strchr(args[i], '=')) // либфт
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
	return (SUCCESS);
}
