/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:45:00 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/30 20:20:38 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_int(t_vars *v)
{
	printf("this is for signed nums\n");
}

/*
** bBoOuUxX
** note that char and short are cast to int, because variadic functions
** implicitly cast to int for all data types narrower than int
*/

void	pf_uint(t_vars *v)
{
	uintmax_t	n;

	n = 0;
//	(v->flags & F_H) && (v->flags & F_HH) ? v->flags &= ~F_H: 0;
	(v->flags & F_L) && (v->flags & F_LL) ? v->flags &= ~F_L: 0;
//	v->flags & F_HH ? n = (uintmax_t)va_arg(*v->args, unsigned char) : 0;
	v->flags & F_H ? n = (uintmax_t)va_arg(*v->args, unsigned int) : 0;
	v->flags & F_L ? n = (uintmax_t)va_arg(*v->args, unsigned long) : 0;
	v->flags & F_LL ? n = (uintmax_t)va_arg(*v->args, unsigned long long) : 0;
	v->flags & F_SIZE ? n = (uintmax_t)va_arg(*v->args, size_t) : 0;
	v->flags & F_MAX ? n = (uintmax_t)va_arg(*v->args, uintmax_t) : 0;
}

void	pf_float(t_vars *v)
{
	printf("this is for floating nums\n");
}

void	pf_char(t_vars *v)
{
	printf("this is for chars\n");
}

void	pf_str(t_vars *v)
{
	printf("this is for strs\n");
}
