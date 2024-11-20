/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:11:20 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:11:20 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*Copies a block of memory from one location to another*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*newdest;
	unsigned char	*newsrc;

	newdest = (unsigned char *)dest;
	newsrc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		newdest[i] = newsrc[i];
		i++;
	}
	return (dest);
}

/*
int	main(void) {
	char src[] = "Texto de exemplo";
	char dest[50]; // Garantindo que temos espaço suficiente

	// Copiando o conteúdo de src para dest
	ft_memcpy(dest, src, sizeof(src));

	// Imprimindo o conteúdo de dest para verificar a cópia
	printf("Conteudo de src: %s\n", src);
	printf("Conteudo copiado para dest: %s\n", dest);

	return (0);
}
*/
