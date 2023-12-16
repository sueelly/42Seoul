/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 06:18:11 by haejokim          #+#    #+#             */
/*   Updated: 2023/05/05 22:24:01 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_print_string(char *str)
{
	size_t	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}

size_t	ft_print_num_base(long long n, const char *base, size_t base_size)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
		len++;
	}
	if (n / base_size)
		len += ft_print_num_base(n / base_size, base, base_size);
	return (len + write(1, &base[n % base_size], 1));
}

size_t	ft_print_address(void *pointer)
{
	size_t	len;
	unsigned long long	address;

	len = 0;
	address = (unsigned long long)pointer;
	write(1, "0x", 2);
	if (pointer == 0)
		return (2 + write(1, "0", 1));
	if (address / 16)
		len += ft_print_num_base(address / 16, "0123456789abcdef", 16);
	return (len + write(1, &"0123456789abcdef"[address % 16], 1) + 2);
}
