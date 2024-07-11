/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:27 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:27 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_pwd(t_minishell *shell)
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

static char	*get_env_path(t_env *env, const char *var, size_t len)
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
				return (NULL); // что делать если по памяти пошел сбой
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

static int	change_oldpwd(t_minishell *shell)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (FAILURE);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (FAILURE);
	if (is_in_env(shell->env, oldpwd) == 1)
		add_env(oldpwd, shell->env);
	is_in_env_array(&(shell->export), oldpwd);
	ft_free_chr(oldpwd);
	return (SUCCESS);
}

static int	follow_path(int choice, t_minishell *shell)
{
	int		res;
	char	*env_path;

	env_path = NULL;
	if (choice == 0)
	{
		env_path = get_env_path(shell->env, "HOME", 4);
		if (!env_path)
		{
			printf("minishell : cd: HOME not set\n");
			return (FAILURE);
		}
	}
	else if (choice == 1)
	{
		env_path = get_env_path(shell->env, "OLDPWD", 6);
		if (!env_path)
		{
			printf("minishell : cd: OLDPWD not set\n");
			return (FAILURE);
		}
	}
	change_oldpwd(shell);
	res = chdir(env_path);
	change_pwd(shell);
	return (ft_free_chr(env_path), res);
}

int	shell_cd(char **args, t_minishell *shell)
{
	if (args[1] == NULL || ft_strncmp(args[1], "~", 2) == 0)
		return (follow_path(0, shell));
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (follow_path(1, shell));
	else
	{
		if (change_oldpwd(shell) == FAILURE)
			return (FAILURE);
		if (chdir(args[1]) == -1)
		{
			write(STDERR_FILENO, "minishell: cd: ", 15);
			perror(args[1]);
			return (FAILURE);
		}
		change_pwd(shell);
	}
	return (SUCCESS);
}
