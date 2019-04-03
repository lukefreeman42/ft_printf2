/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_nb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelias <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:22:20 by llelias           #+#    #+#             */
/*   Updated: 2019/04/02 19:11:39 by llelias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char		convertion(int dig, t_flags op)
{
	if (dig < 10)
		return (dig + 48);
	else
	{
		if (op.plhld == 'X')
			return (dig + 55);
		else
			return (dig + 87);
	}
}

static	long long	trim_nb(va_list arg, t_flags op)
{
	t_trim size;

	if (op.h == 2 && (size.hh = (char)va_arg(arg, int)))
		return ((long long)size.hh);
	else if (op.h && (size.h = (short)va_arg(arg, int)))
		return ((long long)size.h);
	else if ((op.l == 2 || op.plhld == 'p') && (size.ll = va_arg(arg, long long)))
		return ((long long)size.ll);
	else if (op.l && (size.l = va_arg(arg, long)))
		return ((long long)size.l);
	else if (op.plhld != 'd' && (size.u = va_arg(arg, unsigned int)))
		return ((long long)size.u);
	size.d = va_arg(arg, int);
	return ((long long)size.d);
}

void				evaluate_num(char b[65], long long nb, t_flags op, int base)
{
	int i;
	int neg;

	i = 0;
	neg = 0;
	if (nb == 0)
		b[i++] = '0';
	else if (nb < 0 && (nb *= -1))
		neg = 1;
	while (nb)
	{
		b[i++] = convertion(nb % base, op);
		nb /= base;
	}
	if (neg)
		b[i++] = '-';
	b[i] = 0;
	ft_strrev(b);
}

void				num_ph(char b[65], va_list arg, t_flags op)
{
	long long	nb;
	int			len;

	nb = trim_nb(arg, op);
	if (op.plhld == 'd' || op.plhld == 'u')
		evaluate_num(b, nb, op, 10);
	else if (op.plhld == 'o')
		evaluate_num(b, nb, op, 8);
	else
		evaluate_num(b, nb, op, 16);
	len = ft_strlen(b);
	if (op.plhld == 'p')
		prints_addr(b, op);
	else
		prints_num(b, op);
}