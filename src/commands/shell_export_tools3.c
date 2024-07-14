/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_export_tools3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:15:25 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/14 22:32:10 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_full_arg(char *key, char *current_value, char *new_value)
{
	char	*full_arg;

	full_arg = malloc(ft_strlen(key) + ft_strlen(current_value) + ft_strlen(new_value) + 2);
	if (!full_arg)
		return (NULL);
	ft_strlcpy(full_arg, key, ft_strlen(key) + 1);
	ft_strlcat(full_arg, "=", ft_strlen(key) + 2);
	ft_strlcat(full_arg, current_value, ft_strlen(full_arg) + ft_strlen(current_value) + 1);
	ft_strlcat(full_arg, new_value, ft_strlen(full_arg) + ft_strlen(new_value) + 1);
	return (full_arg);
}

void	add_or_update_variable(char *arg, t_minishell *shell)
{
	if (is_in_env(shell->env, arg) == FAILURE)
		add_env(arg, shell->env);
	if (is_in_env_array(&(shell->export), arg) == FAILURE)
		add_to_export(&(shell->export), arg);
}

char	*concat_value(char *old_value, char *new_value)
{
	char	*result;
	size_t	old_len;
	size_t	new_len;

	old_len = ft_strlen(old_value);
	new_len = ft_strlen(new_value);
	result = (char *)malloc(old_len + new_len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, old_value, old_len);
	ft_strlcpy(result + old_len, new_value, new_len);
	return (result);
}

void	export_concatenation(char *arg, t_minishell *shell)
{
	char	*key;
	char	*new_value;
	char	*current_value;
	char	*full_arg;
	int		key_len;

	key_len = ft_strchr(arg, '+') - arg;
	key = ft_substr(arg, 0, key_len);
	new_value = ft_strdup(ft_strchr(arg, '=') + 1);
	current_value = get_env_value(key, shell->env);
	if (!key || !new_value || !current_value)
	{
		free_multiple(key, new_value, current_value);
		return ;
	}
	full_arg = create_full_arg(key, current_value, new_value);
	if (!full_arg)
	{
		free_multiple(key, new_value, current_value);
		return ;
	}
	free_multiple(key, new_value, current_value);
	add_or_update_variable(full_arg, shell);
	free(full_arg);
}

