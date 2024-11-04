#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	return write(1, &c, 1), 1;
}

int	isarg(const char *s)
{
	if (*s == '%' && (s[+1] == 's' || s[+1] == 'd' || s[+1] == 'x'))
		return 1;
	return 0;
}

int	ft_putstr(char *s)
{
	int i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
		i += ft_putchar(s[i]);
	return i;
}

int	ft_putnbr(int nb)
{
	long n = nb;
	int len = 0;

	if (n < 0)
	{
		len += ft_putchar('-');
		n *= -1;
	}
	if (n > 9)
	{
		len += ft_putnbr(n / 10);
		len += ft_putchar(n % 10 + '0');
	}
	else
		len += ft_putchar(n + '0');
	return len;
}

int	ft_puthex(unsigned int nb)
{
	int len = 0;
	char *base = "0123456789abcdef";
	if (nb >= 16)
	{
		len += ft_puthex(nb / 16);
		len += ft_putchar(base[nb % 16]);
	}
	else
		len += ft_putchar(base[nb]);
	return len;
}

int	conv(const char *s, va_list(args))
{
	int len = 0;
	if (s[+1] == 's')
		len += ft_putstr(va_arg(args, char *));
	if (s[+1] == 'd')
		len += ft_putnbr(va_arg(args, int));
	if (s[+1] =='x')
		len+= ft_puthex(va_arg(args, unsigned int));
	return len;
}

int	ft_printf(const char *s, ...)
{
	int len = 0;
	va_list args;

	va_start(args, s);
	while (*s)
	{
		if (isarg(s))
		{
			len += conv(s, args);
			s += 2;
		}
		else
			len += ft_putchar(*s++);
	}
	va_end(args);
	return len;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(int ac, char **av)
{
	(void)ac;
	printf("\n%d\n", ft_printf("%x", atoi(av[1])));
}
