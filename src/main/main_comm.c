
#include "minishell.h"

int	g_error;

void	init_minishell(t_minishell *shell, char **env_in)
{
	int		i;
	t_env	*tmp;

	if (!shell || !env_in)
		return ;
	i = 0;
	g_error = 0;
	shell->env = NULL;
	shell->export = NULL;
	while (env_in[i] != NULL)
	{
		add_env_node(&(shell->env), env_in[i]);
		i++;
	}
	ft_unsetenv("OLDPWD", &shell->env);
	change_lvl(shell->env);
	tmp = shell->env;
	while (tmp)
	{
		add_to_export(&(shell->export), tmp->value);
		tmp = tmp->next;
	}
	add_to_export(&(shell->export), "OLDPWD");
}

void	display_prompt(t_minishell *shell)
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(RESET GREEN "minishell" RED "$ " RESET);
		if (input == NULL)
		{
			printf("exit\n");
			//очистка всего  clean_up
			exit(g_error);
		}
		if (*input)
		{
			add_history(input);
			int i = 0;
			shell->args[i] = strtok(input, " ");
			while (shell->args[i] != NULL)
				shell->args[++i] = strtok(NULL, " ");
			execute_command(shell);
		}
		free(input);
	}
}

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **env)
{
	t_minishell shell;

	init_minishell(&shell, env);
	display_prompt(&shell);
	free_env_list(shell.env);
	free_export(shell.export);
	return (SUCCESS);
}
