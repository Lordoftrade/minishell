/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/07/02 23:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_execve(char *path_bin, char **args, t_env *env_list)
{
	char	**env;
	int		result;

	signal(SIGINT, SIG_IGN);
	env = env_list_to_array(env_list);
	if (!env)
	{
		perror("malloc");
		return FAILURE;
	}
	result =  fork_and_execute(path_bin, args, env);
	free_string_array(env);
	return (result);
}

char *check_path_bin(char *bin, char *command)
{
	DIR				*dir;
	struct dirent	*file;
	char 			*path_bin;

	path_bin = NULL;
	dir = opendir(bin);
	if (!dir)
		return (NULL);
	file = readdir(dir);
	while (file != NULL)
	{
		if (ft_strcmp(file->d_name, command) == 0)
		{
			path_bin = join_path_com(bin, file->d_name);
			break ;
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (path_bin);
}

char	**get_bin_paths(t_minishell *shell)
{
	char *path;;
	char **bin_paths;

	path = get_env_value("PATH", shell->env);
	bin_paths = ft_split(path, ':');
	free(path);
	return (bin_paths);
}

char	*find_executable(char **bin_paths, char *command)
{
	char	*path_bin;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		path_bin = check_path_bin(bin_paths[i++], command);
		if (path_bin && access(path_bin, X_OK) == 0)
			return (path_bin);
		free(path_bin);
	}
	return (NULL);
}

int	execute_bin(char **args, t_minishell *shell)
{
	char	**bin;
	char	*path_bin;
	int		result;

	result = 0;
	path_bin = NULL;
	bin = get_bin_paths(shell);
	if (!args[0] && !bin[0])
	{
		free_string_array(bin);
		return (FAILURE);
	}
	path_bin = find_executable(bin, args[0]);
	if (path_bin)
	{
		result = start_execve(path_bin, args, shell->env);
		free(path_bin);
	}
	else
	{
		printf("minishell: %s: command not found\n", args[0]);
		result = FAILURE;
	}
	free_string_array(bin);
	return (result);
}

