/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:09:37 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:09:37 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Checks if the character belongs to the ASCCI table*/
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*
int	main(void)
{
		printf("%d",ft_isascii('A'));
		printf("%d",ft_isascii('z'));
		printf("%d",ft_isascii('0'));
		printf("%d",ft_isascii('-'));
}
*/
