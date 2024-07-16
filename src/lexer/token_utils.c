/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgreshne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:01:06 by opanikov          #+#    #+#             */
/*   Updated: 2024/07/14 23:14:59 by mgreshne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*create_new_token(enum e_token_type type,
		char *content, t_minishell *sh)
{
	t_lexer	*new_token;

	new_token = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_token)
		errors_memory(sh, 1);
	new_token->type = type;
	new_token->content = ft_strdup(content);
	if (!new_token->content)
		errors_memory(sh, 1);
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_lexer **head, t_lexer *new_token)
{
	t_lexer	*tmp;

	if (*head == NULL)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

char	*ft_strndup(const char *src, size_t n)
{
	char		*res;
	size_t		len;
	size_t		i;

	i = 0;
	len = ft_strlen(src);
	if (n < len)
		len = n;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

char	*ft_mystrjoin(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	free (s1);
	res[i] = '\0';
	return (res);
}
