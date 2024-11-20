/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hguerrei <hguerrei@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/10 13:13:42 by hguerrei          #+#    #+#             */
/*   Updated: 2024/04/10 13:13:42 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Converts characters from upper case to lower case*/
int	ft_tolower(int c)
{
	if ((c >= 'A' && c <= 'Z'))
	{
		return (c + 32);
	}
	return (c);
}
