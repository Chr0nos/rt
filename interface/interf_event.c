/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 10:32:51 by dboudy            #+#    #+#             */
/*   Updated: 2016/09/10 16:58:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rt.h"
#include "libft.h"

/*
** this function is used to check if "px" is inside rect
** return 1 if it's inside, otherwise 0
*/

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
			INTERF_GEO.x + INTERF_OFFSETX - 100,
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

/*
** this function unset any INTER_SELECTED flag in the list,
** then enable the only item select if suitable (mask ok and obj selected)
** return 0 in case of no suitable item
** return 1 in case of successfull object set
*/

static int	interface_event_select_id(t_interf *me, const int id)
{
	interf_removeflag(me, INTER_SELECTED);
	if ((!me->obj_selected) ||
		(!(me->obj_selected->type & (unsigned int)me->cfg[id].mask)))
	{
		return (0);
	}
	me->cfg[id].flags |= INTER_SELECTED;
	if (!me->cfg[id].get_value)
		interf_resetline(me);
	else
		interface_event_loadline(me, id);
	return (1);
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
	if (interface_event_select_id(&rt->interf, id) > 0)
		rt->settings.cfgbits |= (RT_CFGB_REFRESHINTER | RT_CFGB_INTERFEDIT);
	return (1);
}
