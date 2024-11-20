/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:11:27 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:11:27 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Copies a block of memory, handling potential overlaps*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*newdest;
	const char		*newsrc;

	newdest = (char *)dest;
	newsrc = (const char *)src;
	if (newsrc > newdest)
	{
		i = 0;
		while (i < n)
		{
			newdest[i] = newsrc[i];
			i++;
		}
	}
	else if (newdest > newsrc)
	{
		while (n > 0)
		{
			n--;
			newdest[n] = newsrc[n];
		}
	}
	return (newdest);
}
