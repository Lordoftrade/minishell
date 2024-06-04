/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:05:55 by opanikov          #+#    #+#             */
/*   Updated: 2024/06/04 20:10:52 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_minishell
{
	char	**line;
}					t_minishell;

typedef struct s_token
{
	WORD;
	SEP;
	FIELD;
	PIPE;
}					t_token;