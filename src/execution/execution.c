


#include "minishell.h"

int start_execve(char *path_bin, char **args, t_env *env_list)
{
	char **env;
	pid_t	pid;
	int		status;

	env = env_list_to_array(env_list); //надо ли проверка на выделение?
	pid = fork();
	if (pid == 0)
	{
		if (execve(path_bin, args, env) == -1)
		{
			perror("execve");
			free_string_array(env);
			exit(EXIT_FAILURE); // или что то другое делать?
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		free_string_array(env);
		return (FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	free_string_array(env);
	return (0);
}

char		*join_path_com(const char *bin, const char *com)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(bin, "/");
	path = ft_strjoin(tmp, com);
	ft_free_chr(tmp);
	return (path);
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
		if (strcmp(file->d_name, command) == 0)
		{
			path_bin = join_path_com(bin, file->d_name);
			break ;
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (path_bin);
}

int	execute_bin(char **args, t_minishell *shell)
{
	char	*path;
	char	**bin;
	char	*path_bin;
	int		i;
	int		result;

	i = 0;
	result = 0;
	path_bin = NULL;
	path = get_env_value("PATH", shell->env);
	bin = ft_split(path, ':');
	if (!args[0] && !bin[0])
	{
		free_string_array(bin);
		free(path);
		return (FAILURE);
	}
	while (args[0] && bin[i])
	{
		path_bin = check_path_bin(bin[i++], args[0]);
		if (path_bin && access(path_bin, X_OK) == 0)
			break;
		free(path_bin);
		path_bin = NULL;
	}
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
	free(path);
	return (result);
}

int	execute_implemented(char **args, t_minishell *shell)
{
	int result;

	result = 0;
	if (strcmp(args[0], "cd") == 0)
		result = shell_cd(shell->commands->argv, shell); // но может возвращен быть и - 1 елси чдир не откроет (0 и 1 )
	if (strcmp(args[0], "pwd") == 0)
		result = shell_pwd();
	if (strcmp(args[0], "echo") == 0)
		result = shell_echo(shell->commands->argv);
	if (strcmp(args[0], "export") == 0)
		result = shell_export(shell->commands->argv, shell);
	if (strcmp(args[0], "unset") == 0)
		result = shell_unset(shell->commands->argv, shell);
	if (strcmp(args[0], "env") == 0)
		result = shell_env(shell->env);
	if (strcmp(args[0], "exit") == 0)
		shell_exit(shell->commands->argv); // она ничего не возвращает
	/*else {
		printf("minishell: %s: command not found\n", shell->args[0]);
		// или другое использование вывода ошибки
	}*/
	return (result);
}

int	is_command_implemented(char *cmd)
{
	if (strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (strncmp(cmd, "env", 4) == 0)
		return (1);
	if (strncmp(cmd, "export", 7) == 0)
		return (1);
	if (strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_command(t_minishell *shell)
{

	if (shell->commands->argv[0] && is_command_implemented(shell->commands->argv[0]))
		execute_implemented(shell->commands->argv, shell); // что вернуть должно
	else
		execute_bin(shell->commands->argv, shell);
	return (0);
}
