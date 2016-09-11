/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 03:45:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/05 03:53:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "objects.h"
#include "libft.h"
#include "sda.h"

char	*interf_getpos_x(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (sda_double_short(ft_dtoa(obj->trans.w.x, 6)));
}

char	*interf_getpos_y(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (sda_double_short(ft_dtoa(obj->trans.w.y, 6)));
}

char	*interf_getpos_z(t_obj *obj, t_sda_export *e)
{
	(void)e;
	return (sda_double_short(ft_dtoa(obj->trans.w.z, 6)));
}
