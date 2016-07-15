/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 14:24:34 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 01:02:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

static char	*sda_xyz_short(char *s)
{
	char	*so;

	so = s;
	s += ft_strlen(s) - 1;
	while (((*s == '0') || (*s == '.')) && (s != so))
	{
		*s = '\0';
		s--;
	}
	return (so);
}

char		*sda_export_xyz(const t_v4d *v)
{
	char	*x;
	char	*y;
	char	*z;
	char	*buff;

	if ((v->x == 0.0) && (v->y == 0.0) && (v->z == 0.0))
		return (NULL);
	x = sda_xyz_short(ft_dtoa(v->x, 6));
	y = sda_xyz_short(ft_dtoa(v->y, 6));
	z = sda_xyz_short(ft_dtoa(v->z, 6));
	buff = ft_strmjoin(5, x, " ", y, " ", z);
	ft_mfree(3, x, y, z);
	return (buff);
}

char		*sda_export_pos(t_obj *obj)
{
	return (sda_export_xyz(&obj->trans.w));
}

char	*sda_export_rot(t_obj *obj)
{
	return (sda_export_xyz(&obj->rotation));
}
