/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <jupyo@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:22:03 by jupyo             #+#    #+#             */
/*   Updated: 2025/07/21 13:22:03 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list args, const char *str, size_t *i)
{
	int		buffer;
	t_flags	*flags;

	buffer = 0;
	flags = ft_check_flags(str, i);
	if (str[*i] == 'c')
		buffer += ft_print_chr(va_arg(args, int), flags);
	else if (str[*i] == 's')
		buffer += ft_print_str(va_arg(args, char *), flags);
	else if (str[*i] == 'd' || str[*i] == 'i')
		buffer += ft_print_nbr(va_arg(args, int), flags);
	else if (str[*i] == 'x' || str[*i] == 'X')
		buffer += ft_print_hex(va_arg(args, unsigned int), str[*i], flags);
	else if (str[*i] == 'u')
		buffer += ft_print_unsigned(va_arg(args, unsigned int), flags);
	else if (str[*i] == 'p')
		buffer += ft_print_address(va_arg(args, unsigned long long), flags);
	else if (str[*i] == '%')
		buffer += ft_print_percent();
	free(flags);
	return (buffer);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		buffer;

	buffer = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			buffer += ft_formats(args, str, &i);
		}
		else
		{
			ft_putchar(str[i]);
			buffer++;
		}
		i++;
	}
	va_end(args);
	return (buffer);
}
