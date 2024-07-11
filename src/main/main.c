/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:10:52 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/11 00:12:57 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_data(t_minishell *shell)
{
	shell->lexer = NULL;
	shell->commands = NULL;
	shell->exit_code = 0;
	shell->len = 0;
	shell->stdin = dup(STDIN_FILENO);
	shell->stdout = dup(STDOUT_FILENO); 
	shell->f_success = 1;
}

// char	*ft_readline(void)
// {
// 	char	*line;

// 	line = readline("minishell$ ");
// 	if(line == NULL)
// 	{
// 		free(line);
// 		exit(1); // подумать какой код и как запишется 
// 	}
// 	add_history(line);
// 	return(line);
// }

void print_command(t_command *cmd)
{
	// printf("Command: %d\n", cmd->type);
	printf("Arguments:\n");
	char **arg = cmd->argv;
	while (*arg)
	{
	    printf("  %s\n", *arg);
	    arg++;
	}
	if (cmd->input)
	    printf("Input redirection: %s\n", cmd->input);
	if (cmd->output)
	    printf("Output redirection: %s\n", cmd->output);
		if (cmd->delimiter)
	    printf("Delimetr: %s\n", cmd->delimiter);
		if (cmd->LT)
			printf("LT: %d\n", cmd->LT);
		if (cmd->GT)
			printf("GT: %d\n", cmd->GT);
		if (cmd->D_LT)
			printf("D_LT: %d\n", cmd->D_LT);
		if (cmd->D_GT)
			printf("D_GT: %d\n", cmd->D_GT);
	printf("\n");
}
void print_commands(t_minishell *shell)
{
    t_command *cmd = shell->commands;
    while (cmd)
    {
	    print_command(cmd);
	    cmd = cmd->next;
    }
}

void	minishell(t_minishell *shell)
{
	int	res;

	res = 0;
	if(check_redirect(shell->commands) && shell->len == 1)
	{
		res = handling_redir(&shell);
		if (check_argv(shell->commands) && list_size(shell->commands) && !res)
			execute_command(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else if (check_pipe(shell))
	{
		execute_pipeline_one_by_one(shell);
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
	else if (check_argv(shell->commands) && !check_pipe(shell))
		execute_command(shell);
}

// echo >> file hello

// echo->next = hello

// >> file echo hi

// > a < b >> c << d


void todo(void) {
	printf("todo\n");
	exit(1);
}

char *token_type_to_string(enum token_type type) {
	if (type == STRING) return "string";
	else if (type == PIPE) return "pipe";
	else if (type == S_QUOTE) return "single_quote";
	else if (type == D_QUOTE) return "double_quote";
	else if (type == GT) return "greater_than";
	else if (type == LT) return "less_than";
	else if (type == D_GT) return "double_greater_than";
	else if (type == D_LT) return "double_less_than";
	else if (type == MY_SPACE) return "space";
	else if (type == DOLLAR) return "dollar";
	else {
		printf("bug: unhandled token type: %d\n", type);
		exit(1);
	}
}

void print_token(t_lexer *token) {
	printf("%s(%s) ", token_type_to_string(token->type), token->content);
}

void print_tokens(t_lexer *tokens) {
	while (tokens) {
		print_token(tokens);
		tokens = tokens->next;
	}
	printf("\n");
}

void handle_redirection_token_helper(enum token_type type, char *string, t_command *command) {
	if (type == GT) {
		command->GT = 1;
		command->output = string;
	}
	else if (type == LT) {
		command->LT = 1;
		command->input = string;
	}
	else if (type == D_GT) {
		command->D_GT = 1;
		command->output = string;
	}
	else if (type == D_LT) {
		command->D_LT = 1;
		command->delimiter = string;
	}
	else {
		printf("bug: unhandled token type: %d\n", type);
		exit(1);
	}
}

// Todo: free consumed tokens.

void handle_redirection_token(enum token_type type, t_command *command, t_lexer **tokens) {
	t_lexer *next_token = (*tokens)->next;
	if (next_token == 0 || next_token->type != STRING)
		todo();
	char *string = next_token->content;
	handle_redirection_token_helper(type, string, command);
	*tokens = next_token->next;
}

void handle_redirection_tokens(t_lexer **tokens, t_command *command) {
	// Assummed possible token types at this point: STRING, GT, LT, D_GT, D_LT.

	while (*tokens) {
		if ((*tokens)->type != STRING)
			handle_redirection_token((*tokens)->type, command, tokens);
		else
			tokens = &(*tokens)->next;
	}
}

void turn_single_quotes_into_strings(t_lexer *tokens) {
	while (tokens) {
		if (tokens->type == S_QUOTE)
			tokens->type = STRING;
		tokens = tokens->next;
	}
}

void handle_argv_tokens_sanity_check(t_lexer *tokens) {
	// Sanity check that all tokens are of type STRING.
	while (tokens) {
		if (tokens->type != STRING)
			todo();
		tokens = tokens->next;
	}
}

int count_argc(t_lexer *tokens) {
	int argc = 0;

	while (tokens) {
		argc++;
		tokens = tokens->next;
	}

	return argc;
}

void handle_argv_tokens(t_lexer **tokens, t_command *command) {
	// Assummed possible token types at this point: STRING.
	
	handle_argv_tokens_sanity_check(*tokens);

	int argc = count_argc(*tokens);

	command->argv = malloc(sizeof(command->argv) * (argc + 1));
	command->argv[argc] = 0;

	int i = 0;
	while (*tokens) {
		command->argv[i] = (*tokens)->content;
		i++;
		tokens = &(*tokens)->next;
	}
}

t_command *tokens_into_command(t_lexer *tokens) {
	t_command *command = create_new_command();

	// By this point all dollar expansions should have already happened,
	// so it should be safe to turn single quotes into strings for easier processing
	// (by getting rid of an extra token type to check for).
	turn_single_quotes_into_strings(tokens);
	handle_redirection_tokens(&tokens, command);
	handle_argv_tokens(&tokens, command);

	printf("Command after processing:\n\t");
	print_tokens(tokens);
	print_command(command);

	return command;
}

void	display_prompt(t_minishell *shell)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		init_data(shell);
		// line = readline(RESET GREEN "minishell" RED "$ " RESET);
		line = strdup("command some arguments >> output < input << heredoc > real-output more arguments | b | | c d");
		if (line == NULL)
		{
			printf("exit\n");
			//очистка всего  clean_up
			exit(g_error);
		}
		add_history(line);
		// line = ft_readline();
		ft_lexer(line, &shell);
		parser(&(shell->lexer), &shell);
		printf("Tokens before split into commands:\n\t");
		print_tokens(shell->lexer);

		while (shell->lexer) {
			split_by_pipe_result result = split_by_pipe(shell->lexer);

			printf("Command before processing:\n\t");
			print_tokens(result.command);

			// a | b | c

			// a
			// b | c

			t_command *command = tokens_into_command(result.command);
			(void)command;

			shell->lexer = result.rest;
		}

		// check_sintax_redir(shell->lexer);
		// create_commands_from_tokens(&shell);
		// print_commands(shell);
		// if(g_error == 0)
		// {
		// 	create_commands_from_tokens(&shell);
		// print_commands(shell);
		// minishell(shell);
		// }
		// print_commands(shell);
		// free_lexer(shell->lexer);
		free_command_list(shell->commands);
		// system("leaks minishell");
		break;
	}
}


int	main(int argc, char **argv, char **env)
{
	t_minishell *shell;

	(void)argv;
	if(argc > 1)
		exit (1);
	shell = (t_minishell *)malloc(sizeof(t_minishell));
		if(!shell)
			exit (1);
	init_minishell(shell, env);
	display_prompt(shell);
	// while(1)
	// {
	// 	init_data(shell);
	// 	line = ft_readline();
	// 	ft_lexer(line, &shell);
	// 	parser(&(shell->lexer), &shell);
	// 	create_commands_from_tokens(&shell);
	// 	// print_commands(shell);
	// 	minishell(shell);
	// 	// print_commands(shell);
	// 	free_lexer(shell->lexer);
	// 	free_command_list(shell->commands);
	// 	system("leaks minishell");
	// }
	free_env_list(shell->env);
	free_export(shell->export);
	return (SUCCESS);
}
