<<<<<<< HEAD
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

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*prevpwd;
	size_t	i;
	size_t	j;
	size_t	len_alloc;

	while (env)
=======
#include "minishell.h"

static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*prevpwd;
	size_t		i;
	size_t		j;
	size_t		len_alloc;
	// надо ли использоваться через указатель cur?

	while (env) // && env->next != NULL
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
	{
		if (strncmp(env->value, var, len) == 0)
		{
			len_alloc = strlen(env->value) - len;
<<<<<<< HEAD
			prevpwd = malloc(sizeof(char) * len_alloc + 1);
			if (!prevpwd)
=======
			if (!(prevpwd = malloc(sizeof(char) * len_alloc + 1))) // надо ли тут + 1 ? так как = не копируем
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
				return (NULL); // что делать если по памяти пошел сбой
			i = len + 1;
			j = 0;
			while (env->value[i])
<<<<<<< HEAD
				prevpwd[j++] = env->value[i++];
=======
			{
				prevpwd[j++] = env->value[i++];
			}
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
			prevpwd[j] = '\0';
			printf("prewPVD = %s\n", prevpwd);
			return (prevpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	change_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
<<<<<<< HEAD
		return (FAILURE);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
=======
		return (FAILURE); // либо EXIT_FAILURE константа встроенная, но не точно, может варироваться?
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd))) // указываем текущий путь 
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
		return (FAILURE);
	if (is_in_env(env, oldpwd) == 1)
		add_env(oldpwd, env);
	ft_free_chr(oldpwd);
	return (SUCCESS);
}

static int	follow_path(int choice, t_env *env)
{
	int		res;
	char	*env_path;

	env_path = NULL;
	if (choice == 0)
	{
		change_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
		{
<<<<<<< HEAD
			printf("minishell : cd: HOME not set\n");
=======
			//ft_putendl_fd("HOME not set", STDERR);
			printf("minishell : cd: HOME not set\n"); // удалить
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
			return (FAILURE);
		}
	}
	else if (choice == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
		{
<<<<<<< HEAD
			printf("minishell : cd: OLDPWD not set\n");
=======
			//ft_putendl_fd("OLDPWD not set", STDERR);
			printf("minishell : cd: OLDPWD not set\n"); // удалить
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
			return (FAILURE);
		}
		change_oldpwd(env);
	}
<<<<<<< HEAD
	res = chdir(env_path);
	return (ft_free_chr(env_path), res);
=======
	res = chdir(env_path); // 0 успешно изменен каталог, -1 если не успешно
	ft_free_chr(env_path);
	return (res == 0 ? SUCCESS : FAILURE);
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
}

int	shell_cd(char **args, t_env *env)
{
	if (args[1] == NULL  || strcmp(args[1], "~") == 0)
<<<<<<< HEAD
		return (follow_path(0, env));
=======
		return (follow_path(0, env)); // 0 если ок, и -1 если не успешно
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
	if (strcmp(args[1], "-") == 0) // libft
		return (follow_path(1, env)); // 0 если ок, и -1 если не успешно
	else
	{
<<<<<<< HEAD
		change_oldpwd(env);
=======
		change_oldpwd(env); // ??
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
		if (change_oldpwd(env) == FAILURE)
			return (FAILURE);
		if (chdir(args[1]) == -1) // 0 - ok  и -1 если фейл
		{
			//print_error(args); ???????
<<<<<<< HEAD
			printf("cd: no such file or directory: %s\n", args[1]);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
=======
			printf("Error chdir: The PATH is not right\n");
			return (FAILURE);
		}
	}
	// реализация если . или ..
	return (SUCCESS); // 1 если оишбка?
}
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
