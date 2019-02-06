/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_smallconvs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:17:13 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/06 12:17:29 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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
