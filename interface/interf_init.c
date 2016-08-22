/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:40:34 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

static void init_ttf(void)
{
	if (TTF_Init() == -1)
	{
		ft_printf("Erreur initialisation TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	else
		ft_putstr("TTF_Init : okay.\n");
}

static void init_champs_txt(char *champs_txt[NB_CHAMPS][LARGER_SIZE])
{
	*champs_txt[0] = ft_strdup("Id ................... :");
	*champs_txt[1] = ft_strdup("");
	*champs_txt[2] = ft_strdup("Type .............. :");
	*champs_txt[3] = ft_strdup("Name ........... :");
	*champs_txt[4] = ft_strdup("texture ............ :");
	*champs_txt[5] = ft_strdup("");
	*champs_txt[6] = ft_strdup("pos.X ............. :");
	*champs_txt[7] = ft_strdup("pos.Y .............. :");
	*champs_txt[8] = ft_strdup("pos.Z ............. :");
	*champs_txt[9] = ft_strdup("");
	*champs_txt[10] = ft_strdup("dir.X ............... :");
	*champs_txt[11] = ft_strdup("dir.Y ................ :");
	*champs_txt[12] = ft_strdup("dir.Z ............... :");
	*champs_txt[13] = ft_strdup("");
	*champs_txt[14] = ft_strdup("color.R ............ :");
	*champs_txt[15] = ft_strdup("color.G ........... :");
	*champs_txt[16] = ft_strdup("color.B ........... :");
	*champs_txt[17] = ft_strdup("");
	*champs_txt[18] = ft_strdup("transparence :");
	*champs_txt[19] = ft_strdup("reflection (%) :");
	*champs_txt[20] = ft_strdup("refraction (%) :");
	*champs_txt[21] = ft_strdup("");
	*champs_txt[22] = ft_strdup("size ................ :");
	*champs_txt[23] = NULL;
}

static void init_champs_obj(char *champs_obj[NB_CHAMPS][LARGER_SIZE])
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
		*champs_obj[i] = ft_strdup("");
}

static void init_font(t_interf *interf)
{
	define_color(&interf->color_classic, 255, 255, 255);
	define_color(&interf->color_selected, 210, 255, 50);
	interf->font_size = 26;
	interf->police_classic = define_police(interf->police_classic,
		"interface/font/angelina.ttf", interf->font_size, 0);
	interf->police_selected = define_police(interf->police_selected,
		"interface/font/angelina.ttf", interf->font_size, 1);
	define_position(&interf->pos, 10, 10);
	interf->obj_selected = NULL; //tmp
	interf->scale = 1;
}

/*

construction de la fonction pas finie .... :'(

static	t_lst	*init_button(t_lst	*buton)
{
	t_lst	*head;
	SDL_Surface	*carre;
	SDL_Surface	*arrow_left;
	SDL_Surface	*arrow_right;

	button = lstnewlink()
	head = button;

	return (button);
}

*/
void init_interface(t_rt *rt)
{
	init_ttf();
	init_champs_txt(rt->interf->champs_txt);
	init_champs_obj(rt->interf->champs_txt);
	init_font(rt->interf);
	fill_surfaces(rt->interf->champs_txt, rt->interf->surface_txt,
		rt->interf->police_classic, &rt->interf->color_classic);
//	init_button(rt->interf->button); dessiner les jolis boutons de scale et de ENTRER
	free_champs(rt->interf->champs_txt);
}
