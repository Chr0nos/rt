/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 15:10:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 15:32:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <unistd.h>

void	sda_export_camera(t_obj *obj, unsigned int lvl)
{
	char	*pos;
	char	*rot;
	char	*tbl;
	char	*fov;

	if (obj->type != CAMERA)
		return ;

	pos = sda_export_pos(&obj->trans.w);
	rot = sda_export_pos(&obj->rotation);
	tbl = sda_export_ntab(lvl + 1);
	fov = ft_dtoa(((t_camera*)obj->content)->fov, 6);
	if (((!pos) || (!rot) || (!tbl) || (!fov)) &&
		(ft_mfree(4, tbl, rot, pos, fov)))
			return ;
	write(1, tbl, lvl);
	ft_putendl("CAMERA");
	ft_printf("%spos: %s\n%srot: %s\n%sfov: %s\n",
		tbl, pos, tbl, rot, tbl, fov);
	ft_mfree(4, tbl, rot, pos, fov);
}
