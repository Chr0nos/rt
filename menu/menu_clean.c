/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 13:22:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/26 04:05:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"
#include "libft.h"
#include <SDL2/SDL.h>

void			menu_clean(t_rt *rt, int keep_id)
{
	size_t		size;

	ft_putendl("menu clean");
	size = rt->rts_size;
	rt->rts_size = 0;
	while (size--)
	{
		if ((int)size != keep_id)
		{
			rt_node_free(rt->rts[size].root);
			SDL_FreeSurface(rt->rts[size].sys.screen);
			rt->rts[size].sys.screen = NULL;
		}
	}
	if (rt->menu.background)
	{
		SDL_FreeSurface(rt->menu.background);
		rt->menu.background = NULL;
	}
	free(rt->menu.id);
	free(rt->rts);
}
