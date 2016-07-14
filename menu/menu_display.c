/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 15:47:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 15:47:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "menu.h"
#include "libft.h"
#include "keyboard.h"

static void		*menu_display_flush(void *userdata)
{
	t_menu_id		*id;
	SDL_Rect		*rect;

	id = userdata;
	rect = &((const t_rt *)id->src)->menu.positions[id->id];
	if (((!rt_checkcamera((t_rt *)id->dest))) ||
		(!((t_rt *)id->dest)->sys.screen))
	{
		((t_rt *)id->dest)->keyboard = 0;
		return (NULL);
	}
	if (movemyass(id->dest))
		rt_rays((t_rt *)id->dest);
	draw_blitsurface(((const t_rt *)id->src)->sys.screen,
		((t_rt *)id->dest)->sys.screen, (t_point){rect->x, rect->y});
	pthread_mutex_unlock(&id->mutex);
	return (userdata);
}

void			menu_display(t_rt *rt)
{
	const size_t	size = (size_t)(rt->sys.geometry.x * rt->sys.geometry.y);
	size_t			p;
	size_t			max;

	max = (size_t)(rt->menu.items.x * rt->menu.items.y);
	if (rt->menu.background)
		ft_memcpy(rt->sys.screen->pixels, rt->menu.background->pixels,
			size * sizeof(unsigned int));
	if (rt->rts_size < max)
		max = rt->rts_size;
	p = 0;
	while (p < max)
	{
		rt->menu.id[p].id = (int)p;
		//menu_display_flush(&rt->menu.id[p]);
		pthread_create(&rt->menu.id[p].thread, NULL,
			&menu_display_flush, &rt->menu.id[p]);
		p++;
	}
	while (p--)
		pthread_join(rt->menu.id[p].thread, NULL);
	rt->keyboard &= MENU_ALLOW;
}
