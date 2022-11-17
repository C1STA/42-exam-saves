/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:54:34 by wcista            #+#    #+#             */
/*   Updated: 2022/11/16 16:39:17 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	repeat_alpha(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			j = (str[i] - 'A') + 1;
		if (str[i] >= 'a' && str[i] <= 'z')
			j = (str[i] - 'a') + 1;
		if (j == 0)
			ft_putchar(str[i]);
		while (j)
		{
			ft_putchar(str[i]);
			j--;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		repeat_alpha(av[1]);
	write (1, "\n", 1);
}
