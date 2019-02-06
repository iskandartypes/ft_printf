/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:56:40 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/06 13:23:31 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	not_numbers(t_vars *v, long double n, int up)
{
	long double ninf;

	ninf = -1.0 / 0.0;
	if (!(n == n))
	{
		pf_placechar(v, (up) ? 'N' : 'n');
		pf_placechar(v, (up) ? 'A' : 'a');
		pf_placechar(v, (up) ? 'N' : 'n');
		return ;
	}
	if (n == ninf)
		pf_placechar(v, '-');
	pf_placechar(v, (up) ? 'I' : 'i');
	pf_placechar(v, (up) ? 'N' : 'n');
	pf_placechar(v, (up) ? 'F' : 'f');
}

/*
** cheap power function
*/

static int	pf_pow(int val, int pow)
{
	int	ret;

	ret = 1;
	while (pow-- > 0)
		ret *= val;
	return (ret);
}

static char	*ftoa(long double f, int prec, int dot)
{
	uintmax_t	dec;
	uintmax_t	frac;
	char		*ret;
	int			dlen;
	int			i;

	dec = f;
	frac = prec ? (dec - f) * pf_pow(10, prec) : 0;
	dlen = 1;
	while (dec > 9 && dlen++)
		dec /= 10;
	if (!(ret = ft_strnew(dlen + prec + 1)))
		return (0);
	i = dlen - 1;
	while (i > -1)
	{
		ret[i--] = (dec % 10) + '0';
		dec /= 10;
	}
	(frac || dot) ? ret[dlen++] = '.': 0;
	i = dlen + prec;
	while (i > dlen - 1)
	{
		ret[i--] = frac ? (frac % 10) + '0' : '0';
		frac /= 10;
	}
	return (ret);
}

/*
** I'm just going to print pad sign dec . frac pad (no zpad for float)
** The method above *works*, but for small input. (small here meaning int-size)
** What floats are good for is very large or very small numbers.
** We're unlikely to be printing at that scale, but if we were?
** This is a bad solution. An int won't be able to store the number.
*/

void		pf_float(t_vars *v)
{
	long double	f;

	f = (long double)va_arg(v->args, v->flags & F_LL ? long double : double);
	(v->prec == 0 && !(v->flags & F_PREC)) ? v->prec = 6 : 0;
	
}
