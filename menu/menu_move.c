/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 22:16:23 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 15:48:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

void		menu_kb_copy(t_rt *rt)
{
	size_t			p;

	p = rt->rts_size;
	while (p--)
		rt->rts[p].keyboard = rt->keyboard & ~MENU;
}

void		menu_move(t_rt *rt)
{
	size_t	p;

	ft_putendl("mass move");
	p = rt->rts_size;
	while (p--)
		movemyass(&rt->rts[p]);
	rt->keyboard |= FORCE_DISPLAY;
}
