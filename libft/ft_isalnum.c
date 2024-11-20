/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:09:17 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:09:17 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	 Checks if a character is alphanumeric (letter or digit).*/
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
int	main(void)
{
		printf("%d",ft_isalnum('A'));
		printf("%d",ft_isalnum('z'));
		printf("%d",ft_isalnum('0'));
		printf("%d",ft_isalnum('#'));
}
*/
