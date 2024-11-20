/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:11:14 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:11:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Compares two blocks of memory byte by byte.*/
int	ft_memcmp(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*d;
	const unsigned char	*s;

	d = (const unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (d[i] != s[i])
		{
			return (d[i] - s[i]);
		}
		i++;
	}
	return (0);
}

/*
int	main(void) {
	char str1[] = "Hello";
	char str2[] = "Hello";
	int result;
	result = ft_memcmp(str1, str2, 5);

		printf("%d",result);


	return (0);
}
*/
