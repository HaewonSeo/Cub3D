/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:04:13 by haseo             #+#    #+#             */
/*   Updated: 2021/02/22 17:04:14 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long n)
{
	size_t len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		pos;
	long	nbr;

	nbr = n;
	pos = 1;
	len = ft_intlen(nbr);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (nbr < 0)
	{
		pos = -1;
		nbr = -nbr;
	}
	while (len)
	{
		str[--len] = '0' + (nbr % 10);
		nbr = nbr / 10;
	}
	if (pos == -1)
		str[0] = '-';
	return (str);
}
