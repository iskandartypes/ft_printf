/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floatpct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:56:40 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/03 22:05:30 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	not_numbers(t_vars *v, long double n, int up)
{
	if (!(n == n))
	{
		pf_placechar(v, (up) ? 'N' : 'n');
		pf_placechar(v, (up) ? 'A' : 'a');
		pf_placechar(v, (up) ? 'N' : 'n');
		return ;
	}
	if (n == -1.0 / 0.0)
		pf_placechar(v, '-');
	pf_placechar(v, (up) ? 'I' : 'i');
	pf_placechar(v, (up) ? 'N' : 'n');
	pf_placechar(v, (up) ? 'F' : 'f');
}

/*
** current problems: the above (and below!) infinity checks don't work
** below doesn't print out shit yet
** need to figure out what it is that Jackson did that is so hard?
** bc otherwise I'm just going to print pad sign zpad dec . frac pad
*/

void		pf_float(t_vars *v)
{
	long double	n;
	int			ng;
	long long	dec;
	long long	frac;


	if (v->flags & F_LL)
		n = va_arg(v->args, long double);
	else
		n = (long double)(double)va_arg(v->args, double);
	if (/*ft_isinf(n) || */ft_isnan(n))
	{
		not_numbers(v, n, v->flags & F_UP);
		return ;
	}
	ng = (n < 0) ? -1 : 1;
	(!(v->flags & F_PREC)) ? v->prec = 6 : 0;
	dec = (long long)(n / 1);
	frac = (long long)((n - dec) * (v->prec * 10));
}

/*
** Just the % op and some flags
*/

void		pf_pct(t_vars *v)
{
	v->min--;
	if (!(v->flags & F_RPAD))
		while (v->min-- > 0)
			pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
	pf_placechar(v, '%');
	while (v->min-- > 0)
		pf_placechar(v, ' ');
}

void		pf_ptr(t_vars *v)
{
	void				*ptr;
	unsigned long long	adr;

	ptr = va_arg(v->args, void*);
	v->flags |= F_L | F_CONV | F_PTR;
	v->base = 16;
	pf_uint_add(v, (uintmax_t)ptr, 0);
}
