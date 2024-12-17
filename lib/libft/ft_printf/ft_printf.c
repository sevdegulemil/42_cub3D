/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:52:29 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 22:04:20 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_router(va_list *args, char op)
{
	if (op == '%')
		return (ft_putchar_c(op), 1);
	if (op == 'c')
		return (ft_putchar_c(va_arg(*args, int)));
	else if (op == 'd' || op == 'i')
		return (ft_putnbr_c(va_arg(*args, int)));
	else if (op == 's')
		return (ft_putstr_c(va_arg(*args, char *)));
	else if (op == 'u')
		return (ft_putnbr_c(va_arg(*args, unsigned int)));
	else if (op == 'p')
		return (ft_putaddr_c(va_arg(*args, void *)));
	else if (op == 'x' || op == 'X')
		return (ft_puthex_c(va_arg(*args, unsigned int), op));
	return (ft_putchar_c(va_arg(*args, int)));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		cc;
	size_t	i;

	va_start(ap, format);
	i = 0;
	cc = 0;
	while (format[i])
	{
		if (format[i] != '%')
		{
			cc += ft_putchar_c(format[i]);
			i++;
		}
		else if (format[i + 1] != '\0')
		{
			cc += ft_printf_router(&ap, format[i + 1]);
			i += 2;
		}
		else
			i++;
	}
	va_end(ap);
	return (cc);
}
