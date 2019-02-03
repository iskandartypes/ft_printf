/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_floatpct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 03:56:40 by ikourkji          #+#    #+#             */
/*   Updated: 2019/02/03 04:00:07 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_float(t_vars *v)
{
	(!(v->flags & F_PREC)) ? v->prec = 6 : 0;
	printf("this is for floating nums\n");
}

/*
** I hate that I need this
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
