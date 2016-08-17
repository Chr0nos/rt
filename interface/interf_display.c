/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:41:00 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/17 10:41:19 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"


static void print_debug_champs_str(char *interface[NB_CHAMPS][LARGER_SIZE])
{
	int	i;

	i = -1;
	while (++i < NB_CHAMPS)
	{
		ft_putstr(*interface[i]);
		ft_putstr("\n");
	}
}

static void print_debug_champs_txt(SDL_Surface *interface[NB_CHAMPS],
	SDL_Surface *screen, SDL_Rect *pos, int font_size)
{
	int	i;

	i = -1;
	pos->y = 0;
	while (++i < NB_CHAMPS)
	{
		if (!(i % 3))
			pos->y += font_size;
		pos->y += font_size;
		SDL_BlitSurface(interface[i], NULL, screen, pos);
	}
}

/*
int   fill_elem_surface(t_interf_elem *elem, font, color)
{
	t_interf_elem		elem;

	init_struct_interface(&elem, head);
	define_color(&(elem.color), 120, 50, 200);
	if ((interface.police = TTF_OpenFont("interface/font/another.ttf", 65)) != NULL)
	{
		elem.texte = TTF_RenderText_Blended(elem.police,
			"Merry Christmas !", elem.color);
	}
	else
		ft_putstr("fail open font\n");
	return (1);
}
*/

void draw_interface(t_rt *rt)
{
	print_debug_champs_str(rt->interf->champs_str);
	print_debug_champs_txt(rt->interf->champs_txt, rt->sys.screen,
		&rt->interf->pos, rt->interf->font_size);
}
