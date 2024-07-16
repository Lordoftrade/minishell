/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opanikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:45:31 by opanikov          #+#    #+#             */
/*   Updated: 2024/02/04 19:56:40 by opanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size && (count > 2147483647 / size))
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (0);
	ft_bzero (ptr, (count * size));
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	size_t	num_elements = SIZE_MAX;
// 	size_t	element_size = SIZE_MAX;
// 	size_t i = 0;
// 	int* array = (int*)ft_calloc(num_elements, element_size);
// 	if (array != NULL)
// 	{
// 		while(i < num_elements)
// 		{
// 			printf("%d", array[i]);
// 			i++;
// 		}
// 		free(array);
// 	}
// 	else
// 	{
// 		printf("Ошибка при выделении памяти\n");
// 	}
// 	return 0;
// }