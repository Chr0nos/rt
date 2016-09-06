/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/06 17:29:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "libft.h"

static int	interface_event_inrect(t_v2i px, const SDL_Rect *rect)
{
	if ((px.x < rect->x) || (px.x > rect->w + rect->x))
		return (0);
	if ((px.y < rect->y) || (px.y > rect->h + rect->y))
		return (0);
	return (1);
}

static int	interface_event_getelem(const t_v2i *mouse_pos, t_rt *rt)
{
	SDL_Rect	area;
	int			p;

	p = INTERF_ITEMS;
	while (p--)
	{
		area = (SDL_Rect){
			rt->interf.cfg[p].offset.x + INTERF_OFFSETX,
			rt->interf.cfg[p].offset.y - 14 + INTERF_OFFSETY,
			INTERF_GEO.x + INTERF_OFFSETX,
			INTERF_GEO.y + INTERF_OFFSETY + 14
		};
		if (interface_event_inrect(*mouse_pos, &area))
			return (p);
	}
	return (-1);
}

void		interface_event(const t_v2i *mouse_pos, t_rt *rt)
{
	const int		id = interface_event_getelem(mouse_pos, rt);

	ft_printf("id: %d\n", id);
}
