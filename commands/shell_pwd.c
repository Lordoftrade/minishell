<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:35 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:35 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
//pwd         # Выводит полный путь текущего рабочего каталога
//pwd -L      # То же самое, что и выше (логический путь)
//pwd -P      # Выводит физический путь, разрешая все символические ссылки

#include "minishell.h"

int	shell_pwd(void)
{
	char	cwd[PATH_MAX];
<<<<<<< HEAD

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	return (FAILURE);
}
=======
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd); // надо ли свою или можно встроенную?
		return (SUCCESS);
	}
    return (FAILURE);
}
>>>>>>> 5543feee82172faab02e3bef593b84669fe843d9
