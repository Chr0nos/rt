/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_define.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:39:45 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:40:09 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "sda.h"

SDL_Color	*define_color(SDL_Color *color, Uint8 r, Uint8 g, Uint8 b)
{
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

TTF_Font	*define_police(TTF_Font *police, char *name, int size, int selected)
{

	if ((police = TTF_OpenFont(name, size)) != NULL)
	{
		if (selected)
			TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
		return (police);
	}
	else
		ft_putstr("fail open font\n");
	return (NULL);
}

SDL_Surface	*define_texte(TTF_Font *police, char *txt, SDL_Color *color)
{
	SDL_Surface	*texte;

	if ((texte = TTF_RenderText_Blended(police, txt, *color)) != NULL)
		return (texte);
	else
		ft_putstr("fail define texte\n");
	return (NULL);
}

void define_selected_obj(t_obj *obj, char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	char	*tmp_color;

	tmp_color = sda_export_color(obj, NULL);
	*champs_obj[0] = ft_itoa((int)obj->id);
	if (obj->name)
		*champs_obj[1] = ft_strdup(obj->name);
	else
		*champs_obj[1] = ft_strdup("no data");
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
	*champs_obj[9] = ft_strndup(tmp_color + 1, 2);
	*champs_obj[10] = ft_strndup(tmp_color + 3, 2);
	*champs_obj[11] = ft_strndup(tmp_color + 5, 2);
	*champs_obj[12] = ft_strdup("?????"); //tmp
	if (obj->cfgbits & SDB_TEXTURE)
		*champs_obj[13] = sda_export_texture(obj, NULL);
	else
		*champs_obj[13] = ft_strdup("no data");
	*champs_obj[14] = ft_dtoa(obj->refractive_index, 0);
	if (obj->cfgbits & SDB_SIZE)
		*champs_obj[15] = sda_export_size(obj, NULL);
	else
		*champs_obj[15] = ft_strdup("no data");
}

/*
define_font_size;

define_selected_object;
*/
