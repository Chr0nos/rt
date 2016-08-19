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

void init_surface_data(char *champs[NB_CHAMPS][LARGER_SIZE],
	SDL_Surface *surface[NB_CHAMPS], TTF_Font *police, SDL_Color *color)
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		surface[i] = define_texte(police, *champs[i], color);
	}
}

static void init_color_selected_obj(t_obj *obj,
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
			*champs_obj[12] = ft_strndup(tmp_color + i - 2, 2);
		else
			*champs_obj[12] = ft_strdup("none transparency"); //tmp
		*champs_obj[9] = ft_strndup(tmp_color + i, 2);
		*champs_obj[10] = ft_strndup(tmp_color + (i + 2), 2);
		*champs_obj[11] = ft_strndup(tmp_color + (i + 4), 2);
		free(tmp_color);
}

void init_selected_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	if ((!obj) || (!obj->content))
		return ;
	*champs_obj[0] = ft_itoa((int)obj->id);
	if (obj->cfgbits & SDB_NAME)
		*champs_obj[1] = ft_strdup(obj->name);
	else
		*champs_obj[1] = ft_strdup("no name");
	if (obj->type)
		*champs_obj[2] = search_str_type(obj->type);
	else
		*champs_obj[2] = ft_strdup("no data");
	*champs_obj[3] = ft_dtoa(obj->trans.w.x, 0);
	*champs_obj[4] = ft_dtoa(obj->trans.w.y, 0);
	*champs_obj[5] = ft_dtoa(obj->trans.w.z, 0);
	*champs_obj[6] = ft_dtoa(obj->rotation.x, 2);
	*champs_obj[7] = ft_dtoa(obj->rotation.y, 2);
	*champs_obj[8] = ft_dtoa(obj->rotation.z, 2);
	init_color_selected_obj(obj, champs_obj);
	if (obj->cfgbits & SDB_TEXTURE)
		*champs_obj[13] = sda_export_texture(obj, NULL);
	else
		*champs_obj[13] = ft_strdup("no texture");
	if (obj->cfgbits & SDB_REFLECT) // bug
		*champs_obj[14] = sda_export_reflect(obj, NULL);
	else
		*champs_obj[14] = ft_strdup("no reflection");
	if (obj->cfgbits & SDB_REFRACT)
		*champs_obj[15] = ft_dtoa(obj->refractive_index, 0);
	else
		*champs_obj[15] = ft_strdup("no refraction");
	if (obj->cfgbits & SDB_SIZE)
		*champs_obj[16] = sda_export_size(obj, NULL);
	else
		*champs_obj[16] = ft_strdup("no size");
}
