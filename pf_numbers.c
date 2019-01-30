/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikourkji <ikourkji@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:45:00 by ikourkji          #+#    #+#             */
/*   Updated: 2019/01/29 15:53:26 by ikourkji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_int(t_vars *v)
{
	printf("this is for signed nums\n");
}

void	pf_uint(t_vars *v)
{
	printf("this is for unsigned nums\n");
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
