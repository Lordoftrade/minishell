/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:21:00 by mgreshne          #+#    #+#             */
/*   Updated: 2024/06/11 21:21:00 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void clean_up(t_minishell *shell)
{
	// Освобождение всех ресурсов, которые необходимо освободить
}*/

void	free_env_list(t_env *env)
{
	t_env	*cur;

	while (env != NULL)
	{
		cur = env;
		env = env->next;
		free(cur->value);
		free(cur);
	}
}

void	free_export(char **export)
{
	int	i;

	if (export == NULL)
		return ;
	i = 0;
	while (export && export[i])
	{
		free(export[i]);
		i++;
	}
	free(export);
}

void	*ft_free_chr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_string_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}
