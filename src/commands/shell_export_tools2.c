/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_tools2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:21:27 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/06 11:21:27 by mgreshne         ###   ########.fr       */
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
	len = ft_strlen(var_name);
	while ((*export)[i])
	{
		if (ft_strncmp((*export)[i], var_name, len) == 0 &&
			((*export)[i][len] == '=' || (*export)[i][len] == '\0'))
		{
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
	len = ft_strlen(env_name);
	while ((*export)[i])
	{
		if (ft_strncmp((*export)[i], env_name, len) == 0 &&
			((*export)[i][len] == '=' ||
				(*export)[i][len] == '\0'))
		{
			free((*export)[i]);
			if (quoted_value)
				(*export)[i] = ft_strdup(quoted_value);
			else
				(*export)[i] = ft_strdup(env_name);
			free(env_value_str);
			free(quoted_value);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*process_env_value(char *value, char *env_name, char **env_value_str)
{
	char *quoted_value;

	quoted_value = NULL;
	if (ft_strchr(value, '='))
    {
		*env_value_str = env_value(value);
		if (*env_value_str == NULL)
			return (NULL);
		quoted_value = add_quotes_to_value(env_name, *env_value_str);
		if (quoted_value == NULL)
		{
			free(*env_value_str);
			return (NULL);
		}
	}
	return (quoted_value);
}

char	**create_new_export(char **export, char *env_name, char *quoted_value, int count)
{
    char **new_export;
	
	new_export = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_export)
		return NULL;
	copy_array(new_export, export);
	if (quoted_value)
		new_export[count] = quoted_value;
	else
		new_export[count] = ft_strdup(env_name);
	new_export[count + 1] = NULL;
	return (new_export);
}

void	add_to_export(char ***export, char *value)
{
	int		i;
	char	**new_export;
	char	env_name[BUFF_SIZE];
	char	*quoted_value;
	char 	*env_value_str;

	env_value_str = NULL;
	i = 0;
	getenv_name(env_name, value);
	quoted_value = process_env_value(value, env_name, &env_value_str);
	if (quoted_value == NULL && ft_strchr(value, '='))
		return ;
	if (update_export_var(export, env_name, quoted_value, env_value_str))
		return ;
	i = count_elements(*export);
	new_export = create_new_export(*export, env_name, quoted_value, i);
	if (!new_export)
	{
		free(env_value_str); // решить что делать тут
		free(quoted_value);
		return ;
	}
	free_string_array(*export);
	*export = new_export;
	free(env_value_str);
}