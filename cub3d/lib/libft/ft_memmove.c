/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:21:33 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/21 13:21:34 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*pdest;
	const char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = dest;
	psrc = src;
	if (pdest < psrc)
	{
		while (n--)
			*pdest++ = *psrc++;
	}
	else
	{
		pdest += n;
		psrc += n;
		while (n--)
			*(--pdest) = *(--psrc);
	}
	return (dest);
}
