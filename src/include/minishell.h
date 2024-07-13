/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:19 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:19 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define FAILURE 1
# define SUCCESS 0
# define PATH_SIZE 1024
# define BUFF_SIZE 2048

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define RESET "\033[0m"

extern int	g_error;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

enum token_type
{
	STRING,
	PIPE,
	S_QUOTE, //'
	D_QUOTE, //"
	GT, //>
	LT, //<
	D_GT, //>>
	D_LT, // <<
	MY_SPACE,
	DOLLAR,
};

typedef struct s_token_lexer
{
	enum token_type			type;
	char					*content;
	struct s_token_lexer	*next;
}					t_lexer;

typedef struct
{
	t_lexer	*command;
	t_lexer	*rest;
} 			split_by_pipe_result;

typedef struct s_command
{
	char				**argv;   // Аргументы команды
	char				*input;   // Файл для перенаправления ввода (если есть)
	char				*output;  // Файл для перенаправления вывода (если есть)
	char				*delimiter;
	char				*heredoc;
	int					LT;
	int					GT;
	int					D_GT;
	int					D_LT;
	int					pipe;
	struct s_command	*next;
}					t_command;

typedef struct s_minishell
{
	t_env			*env;
	t_lexer			*lexer;
	t_command		*commands;
	char			**export;
	// char			*args[1024];
	int				stdin;
	int				stdout;
	int				len;
	int				exit_code;
	int				f_success;
}					t_minishell;


void		handle_sigint(int sig);
void		do_sigint_fork(int signal);

void		change_lvl(t_env *env);

size_t		count_env(t_env *env);
void		add_env_node(t_env **env, char *value);
int			is_in_env(t_env *env, char *args);
int			is_in_env_array(char ***export, char *args);
char		*get_env_value(char *arg, t_env *env);
char		*env_value(char *value);
int			len_env_value(const char *env);
char		*getenv_name(char *dest, const char *src);
int			add_env(const char *value, t_env *env);
void		bubble_sort_env(char **env_array, size_t env_count);
int 		is_valid_identifier(const char *str);
int			ft_unsetenv(const char *name, t_env **env);
char		**env_list_to_array(t_env *env_list);

int			shell_cd(char **args, t_minishell *shell);
int			shell_pwd(void);
int			shell_echo(char **args);
int			shell_export(char **args, t_minishell *shell);
int			shell_unset(char **args, t_minishell *shell);
int			shell_env(t_env *env);
void		shell_exit(char **args, t_minishell *shell);

int			execute_command(t_minishell *shell);
int			start_execve(char *path_bin, char **args, t_env *env_list);
char		*check_path_bin(char *bin, char *command);
char		*join_path_com(const char *bin, const char *com);
int			execute_bin(char **args, t_minishell *shell);
int			fork_and_execute(char *path_bin, char **args, char **env);
void		run_execve(char *path_bin, char **args, char **env);
int			is_directory(const char *path);

void		*ft_free_chr(void *ptr);
void		free_string_array(char **array);
void		free_export(char **export);
void		free_env_list(t_env *env);

void		add_to_export(char ***export, char *value);
char		*add_quotes_to_value(const char *name, const char *value);
int			count_elements(char **array);
void		copy_array(char **dest, char **src);
int			update_export_var(char ***export, char *env_name, char *quoted_value, char *env_value_str);

void		do_exit(long value, t_minishell *shell);

int			ft_strcmp(const char *s1, const char *s2);

t_env		*create_env_node(char *value);
void		init_minishell(t_minishell *shell, char **env_in);
void		init_data(t_minishell *shell);

void	free_env(t_env *env); // ?? наверное то же самое что и фри енв лист
void	free_lexer(t_lexer *lexer);
void	free_minishell(t_minishell *shell);
void	ft_error(int error_code, char *errmsg);
void	ft_error_put(int code, char *com, char *arg, char *mesg);

char	*ft_readline(void);
void	to_array(char *str, t_minishell *info);
void	ft_lexer(char *line, t_minishell **shell);
int	check_pipe_syntax(char *str);
int	check_quote(char *str);
int	check_symbol(char *str);
t_lexer	*create_new_token(enum token_type type, char *content, t_minishell *sh);
void	add_token_to_list(t_lexer **head, t_lexer *new_token);
char	*ft_strndup(const char *src, size_t n);
void	single_quote_token(char *str, int *i, t_minishell *shell);
void	to_list_lexer(char *str, t_minishell *shell);
void	double_quote_token(char *str, int *i, t_minishell *shell);
void	space_token(char *str, int *i, t_minishell *shell);
void	pipe_token(char *str, int *i, t_minishell *shell);
void	dollar_token(char *str, int *i, t_minishell *shell);
void	gt_token(char *str, int *i, t_minishell *shell);
void	lt_token(char *str, int *i, t_minishell *shell);
void	string_token(char *str, int *i, t_minishell *shell);
void	symbol_dollar(t_lexer **tokens, t_minishell *info);
int		is_breaking_character(char	c);
void	parser(t_lexer **tokens, t_minishell **shell);
char	*open_dollar(char *str, int *i, t_minishell *shell);
void	symbol_d_quote(t_lexer **token, t_minishell *shell);
char	*ft_mystrjoin(char *s1, char const *s2);
void	process_other_chars(char *string, int *i, char **result);
void	process_dollar(char *string, int *i, t_minishell *shell, char **result);
void	connect_tokens(t_lexer **token, t_minishell **shell);
void	concatenate_nodes(t_lexer *current, t_minishell **shell);
void	copy_over(t_lexer *current, t_lexer *new);
void	change_current(t_lexer **current, t_lexer **previous);
void	free_empty_token(t_lexer **token, t_minishell **shell);
void	free_space(t_lexer **token, t_minishell **shell);
void add_command_to_list(t_command **list, t_command *new_command);
void handle_redirections_and_here_document(t_command *new_cmd, t_lexer **current);
void fill_command_argv(t_command *cmd, t_lexer **current);
t_command *create_new_command();
void free_command(t_command *cmd);
void free_command_list(t_command *cmd_list);
int	check_redirect(t_command *command);
void	minishell(t_minishell *shell);
int	handling_redir(t_minishell **shell);
int	run_redirect(t_command **current);
int	do_redir(t_command **c);
int	execute_redirects(t_command **command);
int lt(t_command **command);
int	d_gt(t_command **command);
int	gt(t_command **command);
void	delete_redirect(t_command **command);
void	execute_heredoc(int i, char *delimiter);
int redir_heredoc(t_command **command);
void	delete_heredoc(t_command *command);
int	list_size(t_command *cmd);
int	check_argv(t_command *cmd);
int	check_pipe(t_minishell *shell);
void execute_pipeline_one_by_one(t_minishell *shell);
int	create_pipe(int fd[2]);
int	create_and_execute_child(t_command *curr, int prev_fd, int fd[2], t_minishell *shell);
void	setup_child_pipes(int prev_fd, int read, int write, t_command *curr);
void	handle_parent_process(int *prev_fd, int read, int write, t_command **curr);
int	execute_redirect_pipe(t_command *curr);
int	execute_command_for_pipe(t_command *curr, t_minishell *shell);
int	is_command_implemented(char *cmd);
int	execute_implemented(char **args, t_minishell *shell);
int	execute_bin(char **args, t_minishell *shell);
int	check_sintax_redir(t_lexer *lexer);

int redir_heredoc_pipe(t_command *cmd, int i);
char	*create_heredoc_filename(int i);


void	errors_memory(t_minishell *shell, int error_code);

void	handle_input_redirection(t_command *new_cmd, t_lexer **current);
void	handle_output_redirection(t_command *new_cmd, t_lexer **current);
void	handle_append_redirection(t_command *new_cmd, t_lexer **current);
void	handle_redirections(t_command *new_cmd, t_lexer **current);
void	handle_redirections_and_heredoc(t_command *new_cmd, t_lexer **current);


void create_commands_from_tokens(t_minishell *shell);
t_command	*tokens_into_command(t_lexer *tokens);
void handle_argv_tokens(t_lexer **tokens, t_command *command);
int count_argc(t_lexer *tokens);
void handle_argv_tokens_sanity_check(t_lexer *tokens);
void turn_single_quotes_into_strings(t_lexer *tokens);
void handle_redirection_tokens(t_lexer **tokens, t_command *command);
void handle_redirection_token(enum token_type type, t_command *command, t_lexer **tokens);
void handle_redirection_token_helper(enum token_type type, char *string, t_command *command);
split_by_pipe_result	split_by_pipe(t_lexer *tokens);
int	ft_execve_file_and_path(char **args, t_minishell *shell);
void	ft_error_redir(char *arg, char *mesg);

void print_commands(t_minishell *shell);

#endif
