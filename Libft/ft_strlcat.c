/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:22:57 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:59:43 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;
	size_t	space;

	if (!dst && size == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	space = size - len_dst - 1;
	i = 0;
	if (size <= len_dst)
		return (size + len_src);
	while ((src[i] != '\0') && space > 0)
	{
		dst[len_dst + i] = src[i];
		i++;
		space--;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
