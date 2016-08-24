/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/24 20:03:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "draw.h"

static void			init_ttf(t_rt *rt)
{
	if (TTF_Init() == -1)
	{
		ft_printf("Erreur initialisation TTF_Init : %s\n", TTF_GetError());
		rt_quit(rt, EXIT_FAILURE);
	}
	else
		ft_putstr("TTF_Init : okay.\n");
}

static void			init_champs_txt(char *champs_txt[NB_CHAMPS][LARGER_SIZE])
{
	*champs_txt[I_SCALE] = ft_strdup("-100  -10  -1  +1  +10 +100");
	*champs_txt[I_VIDE1] = ft_strdup("");
	*champs_txt[I_ID] = ft_strdup("Id ......... :");
	*champs_txt[I_VIDE2] = ft_strdup("");
	*champs_txt[I_TYPE] = ft_strdup("Type ....... :");
	*champs_txt[I_NAME] = ft_strdup("Name ....... :");
	*champs_txt[I_TEXT] = ft_strdup("Texture .... :");
	*champs_txt[I_VIDE3] = ft_strdup("");
	*champs_txt[I_POSX] = ft_strdup("pos.X ...... :");
	*champs_txt[I_POSY] = ft_strdup("pos.Y ...... :");
	*champs_txt[I_POSZ] = ft_strdup("pos.Z ...... :");
	*champs_txt[I_VIDE4] = ft_strdup("");
	*champs_txt[I_DIRX] = ft_strdup("dir.X ...... :");
	*champs_txt[I_DIRY] = ft_strdup("dir.Y ...... :");
	*champs_txt[I_DIRZ] = ft_strdup("dir.Z ...... :");
	*champs_txt[I_VIDE5] = ft_strdup("");
	*champs_txt[I_COL_R] = ft_strdup("color.R ... :");
	*champs_txt[I_COL_G] = ft_strdup("color.G ... :");
	*champs_txt[I_COL_B] = ft_strdup("color.B ... :");
	*champs_txt[I_VIDE6] = ft_strdup("");
	*champs_txt[I_ALPHA] = ft_strdup("Transparence :");
	*champs_txt[I_REFL] = ft_strdup("Reflection . :");
	*champs_txt[I_REFR] = ft_strdup("Refraction . :");
	*champs_txt[I_VIDE7] = ft_strdup("");
	*champs_txt[I_SIZE] = ft_strdup("Size ....... :");
	*champs_txt[I_VIDE8] = ft_strdup("");
	*champs_txt[I_ENTER] = ft_strdup("----------- ENTER ----------");
	*champs_txt[I_END] = NULL;
}

static void			init_font(t_interf *interf)
{
	define_color(&interf->color_classic, 255, 255, 255);
	define_color(&interf->color_selected, 210, 255, 50);
	interf->font_size = 18;
	interf->police_classic = define_police(interf->police_classic,
		"interface/font/monkey.ttf", 25, 0);
	interf->police_selected = define_police(interf->police_selected,
		"interface/font/pointfree.ttf", interf->font_size, 0);
}

/*
** static	void	init_button(t_draw	*win)
** {
**	win->win = NULL;
**	win->screen = NULL;
**	win->geometry = (t_v2i){275, 768};
**	draw_init(win, win->geometry, "interface");
** }
*/

void				init_champs_obj(char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	int	i;

	i = -1;
	while (++i != I_END)
	{
		if (i == I_ID)
			*champs_obj[I_ID] = ft_strdup("no object");
		else if ((i != I_VIDE1) && (i != I_VIDE2) && (i != I_VIDE3)
			&& (i != I_VIDE4) && (i != I_VIDE5) && (i != I_VIDE6) &&
			(i != I_VIDE7) && (i != I_VIDE8) && (i != I_ENTER) &&
			(i != I_SCALE))
			*champs_obj[i] = ft_strdup("0");
		else
			*champs_obj[i] = ft_strdup("");
	}
	*champs_obj[I_END] = NULL;
}

void				init_interface(t_rt *rt)
{
	init_ttf(rt);
	init_font(rt->interf);
	define_position(&rt->interf->pos, 0, 0);
	init_champs_txt(rt->interf->champs_txt);
	init_champs_obj(rt->interf->champs_obj);
	if (rt->interf->obj_selected != NULL)
		fill_champs_obj(rt->interf->obj_selected, rt->interf->champs_obj);
	fill_surfaces(rt->interf->champs_txt, rt->interf->surface_txt,
		rt->interf->police_classic, &rt->interf->color_classic);
	rt->interf->scale = 0;
//	init_button(&rt->interf->win);
	free_champs(rt->interf->champs_txt);
}
