/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haejokim <haejokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:58:03 by haejokim          #+#    #+#             */
/*   Updated: 2023/04/07 23:20:48 by haejokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_print_char(char c);
size_t	ft_print_string(char *str);
size_t	ft_print_num_base(long long n, const char *base, size_t base_size);
size_t	ft_print_address(void *pointer);
size_t	ft_print_arg(char type, va_list ap);
size_t	ft_printf(const char *format, ...);

#endif
