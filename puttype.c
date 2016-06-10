/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:15:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/10 09:11:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

void			rt_puttype(int type)
{
	t_typecmp		*types[] = {
		&(t_typecmp){CUBE, "CUBE"},
		&(t_typecmp){PLAN, "PLAN"},
		&(t_typecmp){SPHERE, "SPHERE"},
		&(t_typecmp){ROOT, "ROOT"},
		&(t_typecmp){SPOT, "SPOT"},
		&(t_typecmp){CAMERA, "CAMERA"},
		&(t_typecmp){POINTLIGHT, "POINTLIGHT"},
		&(t_typecmp){FACE, "FACE"},
		&(t_typecmp){EMPTY, "EMPTY"}
	};
	int				p;

	p = 9;
	while ((p--) && (types[p]->type != type))
		;
	ft_putstr((p < 0) ? "UNKNOW" : types[p]->str);
}
