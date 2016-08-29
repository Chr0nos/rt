/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_data_selected_obj.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 15:01:36 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/29 18:30:39 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"
#include "libft.h"

/*
** set la texture filepath sur current en utilisant le parseur de sda
** retours: -1 en cas d erreur
** 0 si la texture existe deja ( n a rien fait en dehors de set a l objet)
** 1 = ok ca a bien load et set
*/

static void	interf_settexture(char *filepath, t_rt *rt, t_obj *current)
{
	t_sda	s;
	char	**av;
	int		ret;

	s = (t_sda){0, rt, rt->root, current, 0, 0};
	if (!(av = ft_strsplit(filepath, ' ')))
		return ;
	ret = sda_setup_texture(&s, current, av);
	ft_freesplit(av);
	if (ret == -1)
		current->cfgbits ^= SDB_TEXTURE;
}

static void	fill_champs_vide(char *champs[NB_CHAMPS][LARGER_SIZE])
{
	*champs[I_SCALE] = ft_strdup(" ");
	*champs[I_VIDE1] = ft_strdup(" ");
	*champs[I_VIDE2] = ft_strdup(" ");
	*champs[I_VIDE3] = ft_strdup(" ");
	*champs[I_VIDE4] = ft_strdup(" ");
	*champs[I_VIDE5] = ft_strdup(" ");
	*champs[I_VIDE6] = ft_strdup(" ");
	*champs[I_VIDE7] = ft_strdup(" ");
	*champs[I_VIDE8] = ft_strdup(" ");
	*champs[I_ENTER] = ft_strdup(" ");
	*champs[I_END] = NULL;
}

static void	set_color(t_obj *obj, char *champs[NB_CHAMPS][LARGER_SIZE])
{
	unsigned char	vals[4];

	vals[3] = (unsigned char)(ft_atoi(*champs[I_ALPHA]));
	vals[2] = (unsigned char)(ft_atoi(*champs[I_COL_R]));
	vals[1] = (unsigned char)(ft_atoi(*champs[I_COL_G]));
	vals[0] = (unsigned char)(ft_atoi(*champs[I_COL_B]));
	((t_cube*)obj->content)->color = *(unsigned int*)(unsigned long long)vals;
}

void		change_all_data_obj(t_rt *rt, char *champs[NB_CHAMPS][LARGER_SIZE])
{
	t_obj	*obj;

	obj = rt->interf->obj_selected;
	obj->id = (t_uint)ft_atoi(*champs[I_ID]);
	obj->type = rt_gettype(*champs[I_TYPE]);
	if (obj->cfgbits & SDB_NAME)
	{
		free(obj->name);
		if (!(obj->name = ft_strdup(*champs[I_NAME])))
				obj->cfgbits ^= SDB_NAME;
	}
	if (obj->cfgbits & SDB_TEXTURE)
		interf_settexture(*champs[I_TEXT], rt, obj);
	obj->trans.w = (t_v4d){
		ft_atod(*champs[I_POSX]), ft_atod(*champs[I_POSY]),
		ft_atod(*champs[I_POSZ]), 0.0};
	rt_obj_rotate(obj, (t_v4d){
			ft_atod(*champs[I_DIRX]),
			ft_atod(*champs[I_DIRY]),
			ft_atod(*champs[I_DIRZ]), 0.0});
	set_color(obj, champs);
	((t_cube*)obj->content)->reflect = (unsigned char)ft_atoi(*champs[I_REFL]);
	obj->refractive_index = ft_atod(*champs[I_REFR]);
	obj->refractive_index = ft_atod(*champs[I_REFR]);
	((t_cube*)obj->content)->size = (float)ft_atod(*champs[I_SIZE]);
	fill_champs_obj(obj, champs);
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
