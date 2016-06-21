/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 23:17:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 20:09:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "draw.h"
#include "libft.h"
#include "keyboard.h"

static t_v4d	move_vec(int k)
{
	const double	offset = (k & FAST) ? 1.0 : 0.5;
	t_v4d			ret;

	ret = (t_v4d){0.0, 0.0, 0.0, 1.0};
	if (k & ZOOMIN)
		ret.z += offset;
	if (k & ZOOMOUT)
		ret.z -= offset;
	if (k & RIGHT)
		ret.x -= offset;
	if (k & LEFT)
		ret.x += offset;
	if (k & UP)
		ret.y += offset;
	if (k & DOWN)
		ret.y -= offset;
	return (ret);
}

int				movemyass(t_rt *rt)
{
	const int		k = rt->keyboard;
	t_m4			m;
	t_obj			*obj;

	if (k & QUIT)
		return (QUIT);
	if (!rt->root)
	{
		if (k & MENU)
			return (k & MENU);
		ft_putendl_fd("error of doom ! i'm done whith that shit !", 2);
		exit(1);
	}
	obj = (t_obj*)(rt->root->content);
	m = obj->trans;
	m.w = draw_vector_transform_m4(move_vec(k), &m);
	obj->trans = m;
	if (k & (ROTATE | ROLL))
		camera_rotate(rt, 0.1, k);
	return (k & (MOVE | FORCE_DISPLAY | MENU));
}

int				sdl_event(SDL_Event *event, t_rt *rt)
{
	if (event->type == SDL_QUIT)
		return (1);
	else if ((event->type == SDL_WINDOWEVENT) &&
		(event->window.event == SDL_WINDOWEVENT_RESIZED))
	{
		rt->sys.geometry = draw_make_px(event->window.data1,
			event->window.data2);
		if (!(rt->sys.screen = SDL_GetWindowSurface(rt->sys.win)))
			return (2);
		rt->menu.items.x = rt->sys.geometry.x / (rt->menu.thumb.x + 5);
		rt->menu.items.y = rt->sys.geometry.y / (rt->menu.thumb.y + 5);
		rt->keyboard |= FORCE_DISPLAY;
	}
	else if (event->type == SDL_KEYDOWN)
		return (keydown(event->key.keysym.sym, rt));
	else if (event->type == SDL_KEYUP)
		return (keyrlz(event->key.keysym.sym, rt));
	else if ((event->type == SDL_MOUSEBUTTONDOWN) ||
		(event->type == SDL_MOUSEBUTTONUP))
		return (mouseclick(event, rt));
	return (0);
}
