/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_alex_ok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:23:43 by amanjon-          #+#    #+#             */
/*   Updated: 2023/09/12 12:56:19 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

static int ft_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}

static int ft_putstr(char *str)
{
    int i;
    
    if (str == NULL)
    {
        write(1, "(null)", 6);
        return (6);
    }
    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

static int ft_count_digits(int nbr)
{
    int count;

    count = 0;
    if (nbr == -2147483648)
        return (10);
    if (nbr == 0)
        return (1);
    if (nbr < 0)
        nbr = nbr * -1;
    while (nbr > 0)
    {
        nbr = nbr / 10;
        count++;
    }
    return (count);
}

static int  ft_putnbr(int nbr)
{
    int count;

	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
    count = 0;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = nbr * -1;
        count++;
	}
    count = count + ft_count_digits(nbr);
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else if (nbr <= 9)
		ft_putchar(nbr + '0');
    return (count);
}

static int ft_print_hex(unsigned int nbr)
{
    int count;

    count = 0;

    if (nbr >= 16)
    {
        count += print_hex(nbr / 16);
        count += print_hex(nbr % 16);
    }
    if (nbr <= 9)
    {
        count = nbr + '0';
        write(1, &count, 1);
    }
    else if (nbr < 16)
    {
        count = nbr + 'W';
        write(1, &count, 1);
    }
    return (count);
}

static int ft_print_format(char *fmt, int j, va_list args)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (fmt[i] == 's')
		x = ft_putstr(va_arg(args, char *));
	else if (fmt == 'd')
		x = ft_putnbr(va_arg(args, int));
	else if (fmt[i] == 'x' || fmt[i] == 'X')
		x = ft_print_hex(va_arg(args, unsigned int));
	x = x + j;
	return (x);
}

int ft_printf(const char *fmt, ... )
{
	int		i;
	int		j;
	va_list	args;

	i = 0;
	j = 0;
	va_start(args, fmt);
	while (fmt[i])
	{
		if (fmt[i] != '%')
			j = j + ft_putchar(fmt[i]);
		else if (fmt[i] == '%')
		{
			i++;
			j = ft_print_format(args, j, &fmt[i]);
		}
		i++;
	}
	va_end(args);
	return (j);
}
