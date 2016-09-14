/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:33:02 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/14 01:32:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "draw.h"
#include "rt.h"
#include <stdlib.h>

void				interface_clean(t_interf *interf)
{
	int				n;
	t_interface_cfg	*cfg;

	n = INTERF_FONTS;
	while (n--)
	{
		cfg = &interf->cfg[n];
		if (cfg->title)
			SDL_FreeSurface(cfg->title);
		if (cfg->title_selected)
			SDL_FreeSurface(cfg->title_selected);
		if (interf->fonts[n].font)
			TTF_CloseFont(interf->fonts[n].font);
	}
	if (interf->screen)
		SDL_FreeSurface(interf->screen);
	TTF_Quit();
	interf->flags &= ~INTER_INITIALIZED;
}

int					interface_init(t_rt *rt)
{
	if (rt->interf.flags & INTER_INITIALIZED)
		return (0);
	ft_memcpy(&rt->interf.cfg, &g_interface,
		sizeof(t_interface_cfg) * INTERF_ITEMS);
	if (TTF_Init() < 0)
		return (-1);
	if (!(rt->interf.screen = draw_make_surface(INTERF_GEO)))
	{
		TTF_Quit();
		ft_putstr_fd("error: failed to init menu surface\n", 2);
		return (-2);
	}
	if (interface_font_init(&rt->interf) < 0)
	{
		ft_freesplit((char **)(unsigned long)rt->interf.fonts);
		ft_putstr_fd("error: failed to unit all fonts\n", 2);
		TTF_Quit();
		return (-3);
	}
	ft_putstr("#Menu init ok\n");
	rt->interf.obj_selected = rt->root->content;
	rt->interf.flags |= INTER_INITIALIZED;
	return (0);
}
