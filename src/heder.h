/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelichik <lelichik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:05:55 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/28 18:35:32 by lelichik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEDER_H
# define HEDER_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h> // PATH_MAX
# include <stddef.h>

# define FAILURE 1
# define SUCCESS 0
# define PATH_SIZE 1024
# define BUFF_SIZE 2048

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

enum token_type
{
	STRING, //строка
	PIPE,
	S_QUOTE, //'
	D_QUOTE, //"
	GT, //> 
	LT, //< 
	D_GT, //>> 
	D_LT, // << 
	SPACE,
	DOLLAR,
};

typedef struct s_token_lexer
{
	enum token_type	type;
	char			*content;
	struct s_token_lexer	*next;
}					t_lexer;

typedef struct s_command
{
    enum				token_type	type;    // Тип команды или оператора (например, "command", ">", ">>", "|")
    char                **argv;   // Аргументы команды
    char                *input;   // Файл для перенаправления ввода (если есть)
    char                *output;  // Файл для перенаправления вывода (если есть)
	char				*delimiter;
    int                 append;   // Флаг для добавления в файл (если 1 - добавление, если 0 - перезапись)
    struct s_command    *next;    // Указатель на следующую команду в пайпе
} t_command;

typedef struct s_minishell
{
	//t_token			*array;
	t_env			*env;
	t_lexer			*lexer;
	t_command		*commands;
	//char			**export;
}					t_minishell;


/*
echo     hi
echo hi
echo hi'bye'

echo hi
STRING(echo) STRING(hi)
'echo' hi S_QUOTE(echo) STRING(hi)
echo '1 2' STRING(echo) S_QUOTE(1 2)

$ DOLLAR()
| PIPE()
<

STRING($)

"$USER $USER"

$home DOLLAR(home)
$home DOLLAR(/users/)

export a='1 2'
export b='4 5'

printf '%s\n' $a' 3'$b

STRING(printf) SPACE STRING(%s\n) SPACE DOLLAR(a) STRING( 3) DOLLAR(b)

STRING(printf) SPACE STRING(%s\n) SPACE STRING(1) SPACE STRING(2) STRING( 3) STRING(4) SPACE STRING(5)

STRING(printf) STRING(%s\n) STRING(1) STRING(2 34) STRING(5)

['printf', '%s\n', '1', '2 34', '5']

printf '%s\n' "$a' 3'$b"

STRING(printf) STRING(%s\n) D_QUOTE($a' 3'$b)
STRING(printf) STRING(%s\n) STRING(1 2' 3'4 5)

echo > $a

STRING(echo) SPACE GT(>) SPACE DOLLAR(a)
-- dollar
STRING(echo) SPACE GT(>) SPACE STRING(1) SPACE STRING(2)
-- double quote
-- glue
STRING(echo) SPACE GT(>) SPACE STRING(1) SPACE STRING(2)
-- remove spaces
STRING(echo) GT(>) STRING(1) STRING(2)
-- pipes


STRING(echo) GT(>) STRING(1) STRING(2) PIPE STRING(cat)
-- pipes
[STRING(echo) GT(>) STRING(1) STRING(2), STRING(cat)]
-- turn into command structs
[struct command { .name = echo, .arguments = [1] }, struct command { .name = cat }]

STRING(echo) GT(>) PIPE STRING(cat)
-- pipes
[STRING(echo) GT(>), STRING(cat)]
-- turn into command structs
[struct command { .name = echo, .arguments = [1] }, struct command { .name = cat }]

> 1 echo hi
.type != STRING
*/

// echo hi
// echo hi > a
// echo hi >> a

// typedef enum {
// 	output_stdout,
// 	output_append_to_file,
// 	output_rewrite_file,
// } t_output_type;

// typedef struct {
// 	t_output_type type;
// 	char *content;
// } t_output;

// // cat < a
// // cat << heredoc
// // cat

// typedef enum {
// 	input_stdin,
// 	input_file,
// 	input_here_document,
// } t_input_type;

// typedef struct {
// 	t_input_type type;
// 	char *content;
// } t_input;

// >> a >> a < b echo c
// D_GT STRING(a) LT STRING(b) STRING(echo) STRING(c)
/*
t_command c;
c.input.type = input_stdin;
c.input.content = 0;
c.output.type = input_stdout;
c.output.content = 0;

while (tokens != 0)

token = D_GT
tokens = tokens->next
if tokens == 0 or token.type != string then error
D_GT is for output
string = a
if (c.output.content != 0) { free(c.output.content) }
c.output.type = output_append_to_file
c.output.content = strdup(a)
tokens = tokens->next

token = LT
tokens = tokens->next
if tokens == 0 or token.type != string then error
string = b
c.input.type = input_file
if (c.input.content != 0) { free(c.input.content) }
c.input.content = strdup(b)
tokens = tokens->next

tokens = STRING

*/

/*
a < b | c d | e > f

a < b
c d
e > f

*/

// typedef struct s_command
// {
// 	char				*type;
// 	char				**argv;
// 	struct s_command	*next;
// } t_command;

// typedef struct s_tokens_by_command {
// 	t_lexer *command;
// 	struct s_tokens_by_command *next;
// } t_tokens_by_command;

// t_command *tokens_to_command(t_lexer *command) {
// }

// typedef struct s_command
// {
// 	t_input input;
// 	t_output output;
// 	char **argv;
// } t_command;

int		len_env_value(const char *env);
char	*env_value(char *value);
char	*getenv_name(char *dest, const char *src);
char	*get_env_value(char *arg, t_env *env);
void	free_env_list(t_env *env);
t_env *create_env_node(char *value);
void	add_env_node(t_env **env, char *value);
void	init_env(t_minishell *shell, char **env);

void free_env(t_env *env);
void free_lexer(t_lexer *lexer);
void free_minishell(t_minishell *shell);
void	ft_error(char *error_message);

char	*ft_readline(void);
void	to_array(char *str, t_minishell *info);
void	ft_lexer(char *line, t_minishell **shell);
void	init_minishell(t_minishell *shell);
int	ft_strlen(const char *str);
int	check_pipe(char *str);
int	check_quote(char *str);
int	check_symbol(char *str);
t_lexer	*create_new_token(enum token_type type, char *content);
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
void	create_commands_from_tokens(t_minishell **shell);
void add_command_to_list(t_command **cmd_list, t_command **last_cmd, t_command *new_cmd);
void handle_redirections_and_here_document(t_command *new_cmd, t_lexer **current);
void fill_command_argv(t_command *cmd, t_lexer **current);
t_command *create_new_command();
void free_command(t_command *cmd);
void free_command_list(t_command *cmd_list);
int	check_redirect(t_command *command);
void	minishell(t_minishell *shell);
int	handling_redir(t_minishell *shell);
int	run_redirect(t_command **command, t_command **previous);
int	do_redir(t_command **c, t_command **p, t_command **s);
int	execute_redirects(t_command **command);
int lt(t_command **command);
int	d_gt(t_command **command);
int	gt(t_command **command);
void	start(t_command **s, t_command **c, t_command **prev, t_minishell **sh);
void	previous(t_command **previous, t_command **command);
void delete_redirect(t_command **cmd, t_command **head, t_command **prev);

#endif