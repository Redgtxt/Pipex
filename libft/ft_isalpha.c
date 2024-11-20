/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:09:23 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:09:23 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Checks if a character is an alphabetic letter.*/
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*
int	main(void)
{
	printf("%d",ft_isalpha('A'));
		printf("%d",ft_isalpha('z'));
		printf("%d",ft_isalpha('0'));
		printf("%d",ft_isalpha('"'));
}
*/
