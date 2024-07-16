/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:32:37 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/14 15:45:29 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_pwd(t_minishell *shell)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (FAILURE);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (FAILURE);
	is_in_env(shell->env, pwd);
	is_in_env_array(&(shell->export), pwd);
	ft_free_chr(pwd);
	return (SUCCESS);
}

char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*prevpwd;
	size_t	i;
	size_t	j;
	size_t	len_alloc;

	while (env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			len_alloc = ft_strlen(env->value) - len;
			prevpwd = malloc(sizeof(char) * len_alloc + 1);
			if (!prevpwd)
				return (NULL);
			i = len + 1;
			j = 0;
			while (env->value[i])
				prevpwd[j++] = env->value[i++];
			prevpwd[j] = '\0';
			return (prevpwd);
		}
		env = env->next;
	}
	return (NULL);
}
