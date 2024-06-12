<<<<<<< HEAD
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

=======
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h> // getcwd
# include <limits.h> // PATH_MAX
# include <stdio.h>
# include <stdlib.h>
<<<<<<< HEAD
# include <stddef.h>
=======
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9

# include <string.h> // !!!!


# define FAILURE 1
# define SUCCESS 0
# define PATH_SIZE 1024

<<<<<<< HEAD
typedef struct s_env
=======
typedef struct	s_env
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
{
	char			*value;
	struct s_env	*next;
}				t_env;

int			shell_cd(char **args, t_env *env);
<<<<<<< HEAD

int			is_in_env(t_env *env, char *args);
char		*getenv_name(char *dest, const char *src);
int			add_env(const char *value, t_env *env);

int			shell_pwd(void);

void		*ft_free_chr(void *ptr);



char		*ft_strjoin(char const *s1, char const *s2); // удалить

#endif
=======
static int	follow_path(int choice, t_env *env);
static int	change_oldpwd(t_env *env);
static char	*get_env_path(t_env *env, const char *var, size_t len);

int	is_in_env(t_env *env, char *args);
char	*getenv_name(char *dest, const char *src);
int	add_env(const char *value, t_env *env);

int	shell_pwd(void);

void	*ft_free_chr(void *ptr);



char	*ft_strjoin(char const *s1, char const *s2); // удалить

#endif
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
