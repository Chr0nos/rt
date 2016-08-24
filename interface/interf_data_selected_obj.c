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
	*champs[I_SCALE] = ft_strdup(" ");
	*champs[I_VIDE1] = ft_strdup("");
	*champs[I_VIDE2] = ft_strdup("");
	*champs[I_VIDE3] = ft_strdup("");
	*champs[I_VIDE4] = ft_strdup("");
	*champs[I_VIDE5] = ft_strdup("");
	*champs[I_VIDE6] = ft_strdup("");
	*champs[I_VIDE7] = ft_strdup("");
	*champs[I_VIDE8] = ft_strdup("");
	*champs[I_ENTER] = ft_strdup(" ");
	*champs[I_END] = NULL;
}
void fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (++i != I_END)
	{
		if (i != I_VIDE1 && i != I_VIDE2 && i != I_VIDE3
			&& i != I_VIDE4 && i != I_VIDE5 && i != I_VIDE6 && i != I_VIDE7
			&& i != I_VIDE8)
			surface[i] = define_texte(police, *champs[i], color);
	}
	surface[I_END] = NULL;
}

/*
static int	clamp(int x)
{
	if (x < 0)
		return (0);
	return ((x > 0xff) ? 0xff : x);
}

static void set_color(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	unsigned char	vals[4];

	vals[0] = (unsigned char)clamp(ft_atoi(*champs_obj[I_ALPHA]));
	vals[1] = (unsigned char)clamp(ft_atoi(*champs_obj[I_COL_R]));
	vals[2] = (unsigned char)clamp(ft_atoi(*champs_obj[I_COL_G]));
	vals[3] = (unsigned char)clamp(ft_atoi(*champs_obj[I_COL_B]));
	((t_cube*)obj->content)->color = *(unsigned int *)(unsigned long)vals;
}
*/

void	change_all_data_obj(t_rt *rt, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	t_obj	*obj;


	obj = rt->interf->obj_selected;
	obj->id = (t_uint)ft_atoi(*champs_obj[I_ID]);
	obj->type = rt_gettype(*champs_obj[I_TYPE]);
	//if (rt->interf->obj_selected->cfgbits & SDB_NAME)
	//	free(rt->interf->obj_selected->name);
	//rt->interf->obj_selected->cfgbits |= SDB_NAME;
	//rt->interf->obj_selected->name = ft_strdup(*champs_obj[3]);
	//if (rt->interf->obj_selected->cfgbits & SDB_TEXTURE)
	//	free(((t_cube*)rt->interf->obj_selected->content)->texture->filepath);
	//rt->interf->obj_selected->cfgbits |= SDB_TEXTURE;
	//((t_cube*)rt->interf->obj_selected->content)->texture->filepath = ft_strdup("textures/cadeau1.jpg"); // test
	obj->trans.w = (t_v4d){
		ft_atod(*champs_obj[I_POSX]),
		ft_atod(*champs_obj[I_POSY]),
		ft_atod(*champs_obj[I_POSZ]), 0.0};
	rt_obj_rotate(obj, (t_v4d){
		ft_atod(*champs_obj[I_DIRX]),
		ft_atod(*champs_obj[I_DIRY]),
		ft_atod(*champs_obj[I_DIRZ]), 0.0});
	//sda_setup_color(NULL, rt->interf->obj_selected, &color);
	((t_cube*)obj->content)->color = (t_uint)(
			((t_uint)(ft_atoi(*champs_obj[I_COL_B]) & 0x000000ff) |
			((t_uint)(ft_atoi(*champs_obj[I_COL_G]) << 8) & 0x0000ff00) |
			((t_uint)(ft_atoi(*champs_obj[I_COL_R]) << 16) & 0x00ff0000) |
			((t_uint)(ft_atoi(*champs_obj[I_ALPHA]) << 24) & 0xff000000)
			));
	((t_cube*)obj->content)->reflect = ((unsigned char)ft_atoi(*champs_obj[I_REFL]));
	obj->cfgbits |= SDB_REFRACT | SDB_REFLECT | SDB_SIZE;
	obj->refractive_index = ft_atod(*champs_obj[I_REFR]);
	((t_cube*)obj->content)->size = (float)ft_atod(*champs_obj[I_SIZE]);
	fill_champs_obj(obj, champs_obj);
}

static void fill_color_selected_obj(t_obj *obj,
	char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
		t_rgb color;
		t_uint alpha;
		t_uint tmp;

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
	*champs_obj[I_POSX] = ft_dtoa(obj->trans.w.x, 2);
	*champs_obj[I_POSY] = ft_dtoa(obj->trans.w.y, 2);
	*champs_obj[I_POSZ] = ft_dtoa(obj->trans.w.z, 2);
	*champs_obj[I_DIRX] = ft_dtoa(obj->rotation.x, 6);
	*champs_obj[I_DIRY] = ft_dtoa(obj->rotation.y, 6);
	*champs_obj[I_DIRZ] = ft_dtoa(obj->rotation.z, 6);
	fill_color_selected_obj(obj, champs_obj);
	if (obj->cfgbits & SDB_REFLECT) // bug
		*champs_obj[I_REFL] = sda_export_reflect(obj, NULL);
	else
		*champs_obj[I_REFL] = ft_strdup("0");
	*champs_obj[I_REFR] = (obj->cfgbits & SDB_REFRACT) ?
		ft_dtoa(obj->refractive_index, 0) : ft_strdup("0");
	if (obj->cfgbits & SDB_SIZE)
		*champs_obj[I_SIZE] = ft_itoa((int)((t_cube*)obj->content)->size);
	else
		*champs_obj[I_SIZE] = ft_strdup("0");
	fill_champs_vide(champs_obj);
}
