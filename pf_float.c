/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:56:40 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/11 22:50:10 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*not_numbers(long double n, int up)
{
	char	*ret;

	if (!(ret = ft_strnew(3)))
		return (0);
	if (ft_isnan(n))
	{
		ret[0] = (up) ? 'N' : 'n';
		ret[1] = (up) ? 'A' : 'a';
		ret[2] = (up) ? 'N' : 'n';
		return (ret);
	}
	ret[0] = (up) ? 'I' : 'i';
	ret[1] = (up) ? 'N' : 'n';
	ret[2] = (up) ? 'F' : 'f';
	return (ret);
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
	frac = prec ? (f - dec) * pf_pow(10, prec) : 0;
	dlen = 1;
	while (dec > 9 && dlen++)
		dec /= 10;
	dec = f;
	if (!(ret = ft_strnew(dlen + prec + 1)))
		return (0);
	i = dlen - 1;
	while (i > -1)
	{
		ret[i--] = (dec % 10) + '0';
		dec /= 10;
	}
	(frac || dot) ? ret[dlen++] = '.': 0;
	i = dlen + prec - 1;
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
	char		*str;
	int			ng;

	f = (v->flags & F_LL) ? va_arg(v->args, long double) :\
		(double)va_arg(v->args, double);
	(v->prec == 0 && !(v->flags & F_PREC)) ? v->prec = 6 : 0;
	ng = (f < 0) ? -1 : 1;
	f *= ng;
	if (!(str = (ft_isnan(f) || ft_isinf(f)) ? not_numbers(f, v->flags & F_UP)\
				: ftoa(f, v->prec, v->flags & F_CONV)))
		return ;
	v->clen = ft_strlen(str);
	v->pad = v->min - v->clen;
	(ng == -1 || v->flags & F_SIGN || v->flags & F_BLANK) ? v->pad -=  1 : 0;
	while (!(v->flags & F_RPAD) && v->pad-- > 0)
		pf_placechar(v, ' ');
	(ng == -1) ? pf_placechar(v, '-') : 0;
	if ((v->flags & F_SIGN || v->flags & F_BLANK) && ng != -1)
		v->flags & F_SIGN ? pf_placechar(v, '+') : pf_placechar(v, ' ');
	while (*str)
		pf_placechar(v, *str++);
	while (v->pad-- > 0)
		pf_placechar(v, ' ');
	free(str - v->clen);
}
