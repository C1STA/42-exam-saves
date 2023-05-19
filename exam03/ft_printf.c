/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:35:16 by wcista            #+#    #+#             */
/*   Updated: 2023/05/19 03:10:40 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	ft_putchar(char c)
{
	int	len;

	len = write(1, &c, 1);
	return (len);
}

int	ft_putstr(char *s)
{
	int	len;

	if (s == NULL)
		return (write(1, "(null)", 6));
	len = 0;
	while (s[len])
		ft_putchar(s[len++]);
	return (len);
}

int	ft_putnbr_hexa(unsigned int n)
{
	int		len;
	char	*base;

	len = 0;
	base = "0123456789abcdef";
	if (n < 16)
		len += ft_putchar(base[n]);
	if (n >= 16)
	{
		len += ft_putnbr_hexa(n / 16);
		len += ft_putnbr_hexa(n % 16);
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		n *= -1;
		len += ft_putchar('-');
	}
	if (n > 9)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	else
		len += ft_putchar (n + '0');
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		len;
	int		i;

	va_start(arg, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 's')
				len += ft_putstr(va_arg(arg, char *));
			if (s[i] == 'd')
				len += ft_putnbr(va_arg(arg, int));
			if (s[i] == 'x')
				len += ft_putnbr_hexa(va_arg(arg, unsigned int));
		}
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
