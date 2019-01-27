/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:47:29 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/26 20:14:33 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		core(t_vars *v)
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
		v->len++;
		ft_putchar_fd(*(v->format), v->fd);
		v->format++;
	}
	return (v->len);
}
