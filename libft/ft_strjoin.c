/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:12:38 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:12:38 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Concatenate two strings into a new one and
allocate space for the new string*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc((s1len + s2len + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, s1len + 1);
	ft_strlcat(newstr, s2, s1len + s2len + 1);
	return (newstr);
}
/*
int	main(void)
{
	char s1[] = "Bom    ";
	char s2[] = "Dia";
	char *juntos = ft_strjoin(s1,s2);

	printf("%s",juntos);
}

*/
