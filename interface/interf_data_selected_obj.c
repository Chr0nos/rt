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

void fill_surfaces(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (surface[i])
	{
		surface[i] = define_texte(police, *champs[i], color);
	}
}

void	change_all_data_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	free_old_data_obj(obj);
	obj->id	= (t_uint)ft_atoi(*champs_obj[0]);
	obj->type = rt_gettype(*champs_obj[2]);
	obj->name = ft_strdup(*champs_obj[3]);
	((t_cube*)obj->content)->texture->filepath = ft_strdup(*champs_obj[4]);
	obj->trans.w.x = ft_atod(*champs_obj[6]);
	obj->trans.w.y = ft_atod(*champs_obj[7]);
	obj->trans.w.z = ft_atod(*champs_obj[8]);
	obj->rotation.x = ft_atod(*champs_obj[10]);
	obj->rotation.y = ft_atod(*champs_obj[11]);
	obj->rotation.z = ft_atod(*champs_obj[12]);
	((t_cube*)obj->content)->color = (t_uint)(
		((((t_uint)ft_atoi(*champs_obj[14])) & 0x000000ff) |
		((((t_uint)ft_atoi(*champs_obj[15])) << 8) & 0x0000ff00) |
		((((t_uint)ft_atoi(*champs_obj[16])) << 16) & 0x00ff0000) |
		((((t_uint)ft_atoi(*champs_obj[18])) << 24) & 0xff000000)));
	((t_cube*)obj->content)->reflect = ((unsigned char)ft_atoi(*champs_obj[19]));
	obj->refractive_index = ft_atod(*champs_obj[20]);
	((t_cube*)obj->content)->size = (float)ft_atod(*champs_obj[22]);
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
			*champs_obj[18] = ft_strndup(tmp_color + i - 2, 2);
		else
			*champs_obj[18] = ft_strdup("00"); //tmp
		*champs_obj[14] = ft_strndup(tmp_color + i, 2);
		*champs_obj[15] = ft_strndup(tmp_color + (i + 2), 2);
		*champs_obj[16] = ft_strndup(tmp_color + (i + 4), 2);
		free(tmp_color);
		*champs_obj[1] = ft_strdup("");
		*champs_obj[5] = ft_strdup("");
		*champs_obj[9] = ft_strdup("");
		*champs_obj[21] = ft_strdup("");
		*champs_obj[23] = NULL;
}

void fill_champs_obj(t_obj *obj,
		char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	free_champs(champs_obj);
	if ((!obj) || (!obj->content))
		return ;
	*champs_obj[0] = ft_itoa((int)obj->id);
	if (obj->type)
		*champs_obj[2] = search_str_type(obj->type);
	else
		*champs_obj[2] = ft_strdup("INVALID");
	if (obj->cfgbits & SDB_NAME)
		*champs_obj[3] = ft_strdup(obj->name);
	else
		*champs_obj[3] = ft_strdup("no name");
	if (obj->cfgbits & SDB_TEXTURE)
		*champs_obj[4] = sda_export_texture(obj, NULL);
	else
		*champs_obj[4] = ft_strdup("no texture");
	*champs_obj[6] = ft_dtoa(obj->trans.w.x, 0);
	*champs_obj[7] = ft_dtoa(obj->trans.w.y, 0);
	*champs_obj[8] = ft_dtoa(obj->trans.w.z, 0);
	*champs_obj[10] = ft_dtoa(obj->rotation.x, 2);
	*champs_obj[11] = ft_dtoa(obj->rotation.y, 2);
	*champs_obj[12] = ft_dtoa(obj->rotation.z, 2);
	fill_color_selected_obj(obj, champs_obj);
	if (obj->cfgbits & SDB_REFLECT) // bug
		*champs_obj[19] = sda_export_reflect(obj, NULL);
	else
		*champs_obj[19] = ft_strdup("00");
	if (obj->cfgbits & SDB_REFRACT)
		*champs_obj[20] = ft_dtoa(obj->refractive_index, 0);
	else
		*champs_obj[20] = ft_strdup("00");
	if (obj->cfgbits & SDB_SIZE)
		*champs_obj[22] = sda_export_size(obj, NULL);
	else
		*champs_obj[22] = ft_strdup("00");
}
