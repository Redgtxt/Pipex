/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:13:25 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:13:25 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Trim the beginning and end of the string with the specified characters.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char		*newstr;
	int			start;
	int			end;

	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	newstr = malloc(end - start + 2);
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, &s1[start], end - start + 2);
	return (newstr);
}

/*
int	main(void)
 {
	char const *s1 = "   Hello,World!   ";
	char const *set = " ";
	printf("Original string: \"%s\"\n", s1);
	char *trimmed = ft_strtrim(s1, set);
	printf("Trimmed string: \"%s\"\n", trimmed);
	return (0);
}
*/
