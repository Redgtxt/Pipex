/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:12:26 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:12:26 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* Duplicates a string by dynamically allocating
memory and copying the original string into it.*/
char	*ft_strdup(const char *str1)
{
	char	*new;
	size_t	lenght;
	int		i;

	lenght = ft_strlen(str1);
	new = malloc((lenght + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str1[i] != '\0')
	{
		new[i] = str1[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
