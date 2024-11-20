/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:09:45 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:09:45 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*: Checks if is a digit.*/
int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*
int	main(void)
{
		printf("%d",ft_isdigit('A'));
		printf("%d",ft_isdigit('z'));
		printf("%d",ft_isdigit('0'));
		printf("%d",ft_isdigit('9'));
}
*/
