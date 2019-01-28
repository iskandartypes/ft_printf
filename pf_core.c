/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:47:29 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/27 23:04:34 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	core(t_vars *v)
{
	while (*(v->format))
	{
		if (*(v->format) == '%')
		{
			if (*(v->format + 1) != '%')
				{ /*do stuff */}
			else
				v->format++;
		}
		v->buf[v->buf_i] = *(v->format);
		v->buf_i++;
		if (v->buf_i == v->buf_len)
		{
			if (!(v->buf = ft_rememalloc(v->buf, v->buf_len, v->buf_len * 2)))
				return ;
			else
				v->buf_len *= 2;
		}
		v->format++;
	}
//	v->buf = ft_rememalloc(v->buf, v->buf_len, v->len);
}
