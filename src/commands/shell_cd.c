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

static char	*get_path(int choice, t_minishell *shell)
{
	if (choice == 0)
		return (get_env_path(shell->env, "HOME", 4));
	else if (choice == 1)
		return (get_env_path(shell->env, "OLDPWD", 6));
	return (NULL);
}

static int	handle_no_path(int choice)
{
	if (choice == 0)
		printf("minishell : cd: HOME not set\n");
	else if (choice == 1)
		printf("minishell : cd: OLDPWD not set\n");
	return (FAILURE);
}

static int	follow_path(int choice, t_minishell *shell)
{
	int		res;
	char	*env_path;

	env_path = get_path(choice, shell);
	if (!env_path)
		return (handle_no_path(choice));
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
