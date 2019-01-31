/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 02:36:16 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/31 05:04:42 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_float(t_vars *v)
{
	f->flags & F_PREC ? 0 : f->prec = 6;
	printf("this is for floating nums\n");
}

void	pf_char(t_vars *v)
{
	unsigned char	c;

	if (v->flags & F_L)
	{}
	else
	{
		c = va_arg(v->args, int);
		v->min--;
		if (!(v->flags & F_RPAD))
			while (v->min-- > 0)
				pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
		pf_placechar(v, c);
		while (v->min-- > 0)
			pf_placechar(v, ' ');
	}
}

void	pf_str(t_vars *v)
{
	char	*s;
	int		i;

	if (v->flags & F_L)
	{}
	else
	{
		s = va_arg(v->args, char*);
		v->clen = ft_strlen(s);
		(v->flags & F_PREC) && (v->clen > v->prec) ? v->clen = v->prec : 0;
		v->min -= v->clen;
		if (!(v->flags & F_RPAD))
			while (v->min-- > 0)
				pf_placechar(v, v->flags & F_ZPAD ? '0' : ' ');
		i = 0;
		while (i < v->clen)
			pf_placechar(v, s[i++]);
		while (v->min-- > 0)
			pf_placechar(v, ' ');
	}
}
