/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init_data_selected_obj.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:01:36 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/19 15:01:40 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"

/*
** fontion pour definir l'objet selecteionne a ajouter
*/
static void	fill_champs_vide(char *champs[NB_CHAMPS][LARGER_SIZE])
{
	*champs[I_SCALE] = ft_strdup("");
	*champs[I_VIDE1] = ft_strdup("");
	*champs[I_VIDE2] = ft_strdup("");
	*champs[I_VIDE3] = ft_strdup("");
	*champs[I_VIDE4] = ft_strdup("");
	*champs[I_VIDE5] = ft_strdup("");
	*champs[I_VIDE6] = ft_strdup("");
	*champs[I_VIDE7] = ft_strdup("");
	*champs[I_VIDE8] = ft_strdup("");
	*champs[I_END] = NULL;
}
void fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS - 1)
	{
		if (i != I_VIDE1 && i != I_VIDE2 && i != I_VIDE3
			&& i != I_VIDE4 && i != I_VIDE5 && i != I_VIDE6 && i != I_VIDE7
			&& i != I_VIDE8)
			surface[i] = define_texte(police, *champs[i], color);
	}
	surface[I_END] = NULL;
}

void	change_all_data_obj(t_rt *rt, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	rt->interf->obj_selected->id = (t_uint)ft_atoi(*champs_obj[I_ID]);
	rt->interf->obj_selected->type = rt_gettype(*champs_obj[I_TYPE]);
	//rt->interf->obj_selected->name = ft_strdup(*champs_obj[3]);
	//((t_cube*)obj->content)->texture->filepath = ft_strdup("textures/cadeau1.jpg");
	rt->interf->obj_selected->trans.w.x = ft_atod(*champs_obj[I_POSX]);
	rt->interf->obj_selected->trans.w.y = ft_atod(*champs_obj[I_POSY]);
	rt->interf->obj_selected->trans.w.z = ft_atod(*champs_obj[I_POSZ]);
	rt->interf->obj_selected->rotation.x = ft_atod(*champs_obj[I_DIRX]);
	rt->interf->obj_selected->rotation.y = ft_atod(*champs_obj[I_DIRY]);
	rt->interf->obj_selected->rotation.z = ft_atod(*champs_obj[I_DIRZ]);
	((t_cube*)rt->interf->obj_selected->content)->color = (t_uint)(
		((((t_uint)ft_atoi(*champs_obj[I_COL_B])) & 0x000000ff) |
		((((t_uint)ft_atoi(*champs_obj[I_COL_G])) << 8) & 0x0000ff00) |
		((((t_uint)ft_atoi(*champs_obj[I_COL_R])) << 16) & 0x00ff0000) |
		((((t_uint)ft_atoi(*champs_obj[I_ALPHA])) << 24) & 0xff000000)));
	((t_cube*)rt->interf->obj_selected->content)->reflect = ((unsigned char)ft_atoi(*champs_obj[I_REFL]));
	rt->interf->obj_selected->refractive_index = ft_atod(*champs_obj[I_REFR]);
	((t_cube*)rt->interf->obj_selected->content)->size = (float)ft_atod(*champs_obj[I_SIZE]);
	//init_selected_obj(rt->interf->obj_selected, rt->interf->champs_obj);
}

static void fill_color_selected_obj(t_obj *obj,
	char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
		char	*tmp_color;
		int		i;

		i = 1;
		if (obj->type & SDA_COLOR)
			tmp_color = sda_export_color(obj, NULL);
		else
			tmp_color = ft_strdup("#000000");
		if (ft_strlen(tmp_color) == 9 && (i = 3))
			*champs_obj[I_ALPHA] = ft_strndup(tmp_color + i - 2, 2);
		else
			*champs_obj[I_ALPHA] = ft_strdup("00"); //tmp
		*champs_obj[I_COL_R] = ft_strndup(tmp_color + i, 2);
		*champs_obj[I_COL_G] = ft_strndup(tmp_color + (i + 2), 2);
		*champs_obj[I_COL_B] = ft_strndup(tmp_color + (i + 4), 2);
		free(tmp_color);
}

void fill_champs_obj(t_obj *obj,
		char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	if ((!obj) || (!obj->content))
		return ;
	free_champs(champs_obj);
	*champs_obj[I_ID] = ft_itoa((int)obj->id);
	if (obj->type)
		*champs_obj[I_TYPE] = search_str_type(obj->type);
	else
		*champs_obj[I_TYPE] = ft_strdup("INVALID");
	if (obj->cfgbits & SDB_NAME)
		*champs_obj[I_NAME] = ft_strdup(obj->name);
	else
		*champs_obj[I_NAME] = ft_strdup("no name");
	if (obj->cfgbits & SDB_TEXTURE)
		*champs_obj[I_TEXT] = sda_export_texture(obj, NULL);
	else
		*champs_obj[I_TEXT] = ft_strdup("no texture");
	*champs_obj[I_POSX] = ft_dtoa(obj->trans.w.x, 0);
	*champs_obj[I_POSY] = ft_dtoa(obj->trans.w.y, 0);
	*champs_obj[I_POSZ] = ft_dtoa(obj->trans.w.z, 0);
	*champs_obj[I_DIRX] = ft_dtoa(obj->rotation.x, 2);
	*champs_obj[I_DIRY] = ft_dtoa(obj->rotation.y, 2);
	*champs_obj[I_DIRZ] = ft_dtoa(obj->rotation.z, 2);
	fill_color_selected_obj(obj, champs_obj);
	if (obj->cfgbits & SDB_REFLECT) // bug
		*champs_obj[I_REFL] = sda_export_reflect(obj, NULL);
	else
		*champs_obj[I_REFL] = ft_strdup("0");
	*champs_obj[I_REFR] = (obj->cfgbits & SDB_REFRACT) ?
		ft_dtoa(obj->refractive_index, 0) : ft_strdup("0");
	if (obj->cfgbits & SDB_SIZE)
		*champs_obj[I_SIZE] = sda_export_size(obj, NULL);
	else
		*champs_obj[I_SIZE] = ft_strdup("0");
	fill_champs_vide(champs_obj);
}
