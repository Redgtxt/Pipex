/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:13:37 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:13:37 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Converts characters from lower case to upper case*/
int	ft_toupper(int c)
{
	if ((c >= 'a' && c <= 'z'))
	{
		return (c - 32);
	}
	return (c);
}
