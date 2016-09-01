/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_fill_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:01:36 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/01 17:06:59 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"
#include "libft.h"

static void	fill_champs_vide(char *champs[NB_CHAMPS][LARGER_SIZE])
{
	*champs[I_VIDE2] = ft_strdup("\t");
	*champs[I_VIDE3] = ft_strdup("\t");
	*champs[I_VIDE4] = ft_strdup("\t");
	*champs[I_VIDE5] = ft_strdup("\t");
	*champs[I_VIDE6] = ft_strdup("\t");
	*champs[I_VIDE7] = ft_strdup("\t");
	*champs[I_VIDE8] = ft_strdup("\t");
	*champs[I_ENTER] = ft_strdup("\t");
	*champs[I_END] = NULL;
}

static void	fill_color_selected_obj(t_obj *obj,
		char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	t_rgb	color;
	t_uint	alpha;
	t_uint	tmp;

	tmp = ((t_cube*)obj->content)->color;
	color.b = tmp & 0xff;
	color.g = tmp >> 8 & 0xff;
	color.r = tmp >> 16 & 0xff;
	alpha = tmp >> 24 & 0xff;
	*champs_obj[I_COL_R] = ft_itoa((int)color.r);
	*champs_obj[I_COL_G] = ft_itoa((int)color.g);
	*champs_obj[I_COL_B] = ft_itoa((int)color.b);
	*champs_obj[I_ALPHA] = ft_itoa((int)alpha);
}

void		fill_champs_obj(t_obj *obj,
		char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	if ((!obj) || (!obj->content))
		return ;
	ft_freesplit(*champs_obj);
	*champs_obj[I_ID] = ft_itoa((int)obj->id);
	*champs_obj[I_TYPE] = (obj->type) ?
		search_str_type(obj->type) : ft_strdup("INVALID");
	*champs_obj[I_NAME] = (obj->cfgbits & SDB_NAME) ?
		ft_strdup(obj->name) : ft_strdup("no name");
	*champs_obj[I_TEXT] = (obj->cfgbits & SDB_TEXTURE) ?
		sda_export_texture(obj, NULL) : ft_strdup("no texture");
	*champs_obj[I_POSX] = ft_dtoa(obj->trans.w.x, 2);
	*champs_obj[I_POSY] = ft_dtoa(obj->trans.w.y, 2);
	*champs_obj[I_POSZ] = ft_dtoa(obj->trans.w.z, 2);
	*champs_obj[I_DIRX] = ft_dtoa(obj->rotation.x, 6);
	*champs_obj[I_DIRY] = ft_dtoa(obj->rotation.y, 6);
	*champs_obj[I_DIRZ] = ft_dtoa(obj->rotation.z, 6);
	fill_color_selected_obj(obj, champs_obj);
	*champs_obj[I_REFL] = (obj->cfgbits & SDB_REFLECT) ?
		sda_export_reflect(obj, NULL) : ft_strdup("0");
	*champs_obj[I_REFR] = (obj->cfgbits & SDB_REFRACT) ?
		ft_dtoa(obj->refractive_index, 0) : ft_strdup("0");
	if (!(*champs_obj[I_SIZE] = sda_export_size(obj, NULL)))
		ft_strdup("1");
	fill_champs_vide(champs_obj);
}
