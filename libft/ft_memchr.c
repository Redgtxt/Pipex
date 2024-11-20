/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:11:08 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:11:08 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Searches for the first occurrence of a character
 in a block of memory.*/
void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t		i;
	const char	*s;

	s = (const char *)str;
	i = 0;
	while (i < n)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void) {
	char str[] = "Hello, world!";
	char *ptr;

	ptr = ft_memchr(str, 'l',19);

	printf("%s",ptr);
	return (0);
}
*/
