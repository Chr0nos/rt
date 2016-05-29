/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:15:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 06:15:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

void			rt_puttype(int type)
{
	if (type == CUBE)
		ft_putstr("CUBE");
	else if (type == PLAN)
		ft_putstr("PLAN");
	else if (type == SPHERE)
		ft_putstr("SPHERE");
	else if (type == ROOT)
		ft_putstr("ROOT");
	else if (type == CAMERA)
		ft_putstr("CAMERA");
	else if (type == SPOT)
		ft_putstr("SPOT");
	else if (type == POINTLIGHT)
		ft_putstr("POINTLIGHT");
	else
		ft_putstr("UNKNOW");
}
