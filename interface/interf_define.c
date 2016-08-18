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
	/*t_uint	color;

	if (obj->type == SETTING)
	{
		color = ((t_setting*)obj->content)->color;
	}
	else
		color = ((t_cube*)obj->content)->color;
		*/
	ft_putstr("plop1\n");
	*champs_obj[0] = ft_itoa((int)obj->id);
	ft_putstr("plop2\n");
	if (obj->name)
		*champs_obj[1] = ft_strdup(obj->name);
	else
		*champs_obj[1] = ft_strdup("no data");
	ft_putstr("plop3\n");
	if (obj->type)
		*champs_obj[2] = ft_strdup(search_str_type(obj->type)); //tmp
	else
		*champs_obj[2] = ft_strdup("no data"); //tmp
	ft_putstr("plop4\n");
	*champs_obj[3] = ft_dtoa(obj->trans.w.x, 2);
	ft_putstr("plop5\n");
	*champs_obj[4] = ft_dtoa(obj->trans.w.y, 2);
	ft_putstr("plop6\n");
	*champs_obj[5] = ft_dtoa(obj->trans.w.z, 2);
	ft_putstr("plop7\n");
	*champs_obj[6] = ft_dtoa(obj->rotation.x, 2);
	ft_putstr("plop8\n");
	*champs_obj[7] = ft_dtoa(obj->rotation.y, 2);
	ft_putstr("plop9\n");
	*champs_obj[8] = ft_dtoa(obj->rotation.z, 2);
	ft_putstr("plop10\n");
	*champs_obj[9] = ft_strdup("");
	//ft_itoa((int)(color >> 16 & 0xFF));
	ft_putstr("plop11\n");
	*champs_obj[10] = ft_strdup("");
	//ft_itoa((int)(color >> 8 & 0xFF));
	ft_putstr("plop12\n");
	*champs_obj[11] = ft_strdup("");
	//ft_itoa((int)(color >> 0 & 0xFF));
	ft_putstr("plop13\n");
	*champs_obj[12] = ft_strdup("");
	//ft_itoa((int)(color >> 24 & 0xFF));
	ft_putstr("plop14\n");
	*champs_obj[13] = ft_strdup(""); //tmp
	ft_putstr("plop15\n");
	*champs_obj[14] = ft_dtoa(obj->refractive_index, 2);
	ft_putstr("plop16\n");
	*champs_obj[15] = ft_strdup("obj->size");
ft_putstr("plop17\n");
/*int i = -1;
(void)obj;
while (++i < NB_CHAMPS)
{
	*champs_obj[i] = ft_itoa(i);
}
*/
}

/*
define_font_size;

define_selected_object;
*/
