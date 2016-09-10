/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/10 05:42:34 by snicolet         ###   ########.fr       */
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

/*
** this function return the id of the seleceted element: in case of no match
** it will return -1
*/

static int	interface_event_getelem(const t_v2i *mouse_pos, t_rt *rt)
{
	SDL_Rect	area;
	int			p;

	p = INTERF_ITEMS;
	while (p--)
	{
		area = (SDL_Rect){
			rt->interf.cfg[p].offset.x + INTERF_OFFSETX,
			rt->interf.cfg[p].offset.y + INTERF_OFFSETY,
			INTERF_GEO.x + INTERF_OFFSETX,
			28
		};
		if (interface_event_inrect(*mouse_pos, &area))
			return (p);
	}
	return (-1);
}

/*
** this function copy the item value into the current edit buffer
*/

static void	interface_event_loadline(t_interf *me, const int p)
{
	char	*value;

	if ((value = me->cfg[p].get_value(me->obj_selected, NULL)))
	{
		me->line_pos = (int)ft_strlen(value);
		if (me->line_pos)
			ft_memcpy(me->line, value, (size_t)(me->line_pos + 1));
		else
			me->line[0] = '\0';
		free(value);
	}
	else
		interf_resetline(me);
}

static void	interface_event_select_id(t_interf *me, const int id)
{
	int			p;

	p = INTERF_ITEMS;
	while (p--)
	{
		if (p == id)
		{
			me->cfg[p].flags |= INTER_SELECTED;
			if (!me->obj_selected)
				continue ;
			if (!me->cfg[p].get_value)
				interf_resetline(me);
			else
				interface_event_loadline(me, p);
		}
		else if (me->cfg[p].flags & INTER_SELECTED)
			me->cfg[p].flags ^= INTER_SELECTED;
	}
}

/*
** interface mouse event function, return 1 if the mouse clicked on interface
** otherwise 0 will be returned
*/

int			interface_event(const t_v2i *mouse_pos, t_rt *rt)
{
	const int		id = interface_event_getelem(mouse_pos, rt);

	if (id < 0)
		return (0);
	ft_printf("id: %d\n", id);
	interface_event_select_id(&rt->interf, id);
	rt->settings.cfgbits |= (RT_CFGB_REFRESHINTER | RT_CFGB_INTERFEDIT);
	return (1);
}
