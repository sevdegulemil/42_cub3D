/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seemil <seemil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:52:43 by hkizrak-          #+#    #+#             */
/*   Updated: 2024/12/14 22:04:27 by seemil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_c(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_c(char *str)
{
	int	i;

	if (str == NULL)
		return (ft_putstr_c("(null)"));
	i = 0;
	while (*str)
	{
		i += ft_putchar_c(*str);
		str++;
	}
	return (i);
}

int	ft_putnbr_c(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i += ft_putchar_c('-');
		n *= -1;
	}
	if (n > 9)
		i += ft_putnbr_c(n / 10);
	i += ft_putchar_c((n % 10) + '0');
	return (i);
}

int	ft_puthex_c(unsigned int n, char op)
{
	char	*c;
	int		i;

	if (op == 'x')
		c = "0123456789abcdef";
	else
		c = "0123456789ABCDEF";
	i = 0;
	if (n > 15)
		i += ft_puthex_c(n / 16, op);
	i += ft_putchar_c(c[n % 16]);
	return (i);
}
