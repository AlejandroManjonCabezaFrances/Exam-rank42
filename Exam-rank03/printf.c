/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:14:52 by amanjon-          #+#    #+#             */
/*   Updated: 2023/09/14 11:00:13 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
// funcion print_hex de Amir ok. dos ultimas funciones valen las de mi printf -ok-

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
        nbr *= -1;
    while (nbr > 0)
    {
        nbr /= 10;
        count ++;
    }
    return (count);
}

static int  ft_putnbr(int nbr)
{
    int count;

    count = 0;
	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
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
	if (nbr <= 9)
		ft_putchar(nbr + '0');
    return (count);
}

static int ft_print_hex(unsigned int nbr)
{
    int     count;
    int     pos;
    char    hexa[12];

    count = 0;
    pos = 0;
    if (nbr == 0)
    {
        ft_putchar('0');
        return (1);
    }
    while  (nbr > 0)
    {
        hexa[count] = "0123456789abcdef"[nbr % 16];
        nbr /= 16;
        count++;
    }
    pos = count - 1;
    while (pos >= 0)
    {
        ft_putchar(hexa[pos]);
        pos--;
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
	else if (fmt[i] == 'd')
		x = ft_putnbr(va_arg(args, int));
	else if (fmt[i] == 'x')
		x = ft_print_hex(va_arg(args, unsigned int));
	x = x + j;
	return (x);
}

int ft_printf(const char *fmt, ... )
{
	int		i;
	int		j;
	char	*str;
	va_list	args;

	i = 0;
	j = 0;
	str = (char *) fmt;
	va_start(args, fmt);
	while (str[i])
	{
		if (str[i] != '%')
			j = j + ft_putchar(str[i]);
		else if (str[i] == '%')
		{
			i++;
			j = ft_print_format(&str[i], j, args);
		}
		i++;
	}
	va_end(args);
	return (j);
}