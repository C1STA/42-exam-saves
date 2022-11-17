/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:01:01 by wcista            #+#    #+#             */
/*   Updated: 2022/11/16 19:37:10 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	sign = 1;
	res = 0;
	while (s[i])
	{
		if (s[i] == '-')
			sign = -1;
		if (s[i] >= '0' && s[i] <= '9')
			res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	add_prime_sum(int n)
{
	int	i;
	int	j;
	int	res;

	i = n;
	res = 0;
	j = 0;
	while (n > 1)
	{
		i = n - 1;
		while (i > 1)
		{
			if (n % i == 0)
				j = 1;
			i--;
		}
		if (j == 0)
			res += n;
		j = 0;
		n--;
	}
	ft_putnbr(res);
}

int	main(int ac, char **av)
{
	int	n;

	if (ac == 2)
	{
		n = ft_atoi(av[1]);
		if (n >= 0)
			add_prime_sum(n);
	}
	if (ac != 2 || n < 0)
		write(1, "0", 1);
	write(1, "\n", 1);
}
