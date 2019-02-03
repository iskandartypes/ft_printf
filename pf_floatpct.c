/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floatpct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:56:40 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/03 11:50:06 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_float(t_vars *v)
{
	(!(v->flags & F_PREC)) ? v->prec = 6 : 0;
	printf("this is for floating nums\n");
}

/*
** Just the % op and some flags
*/

void	pf_pct(t_vars *v)
{
	v->min--;
	if (!(v->flags & F_RPAD))
		while (v->min-- > 0)
			pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
	pf_placechar(v, '%');
	while (v->min-- > 0)
		pf_placechar(v, ' ');
}

void	pf_ptr(t_vars *v)
{
	void				*ptr;
	unsigned long long	adr;

	ptr = va_arg(v->args, void*);
	v->flags |= F_L | F_CONV | F_PTR;
	v->base = 16;
	pf_uint_add(v, (uintmax_t)ptr, 0);
}
