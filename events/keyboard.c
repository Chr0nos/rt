/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 16:28:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"
#include "sda.h"

int				keydown(int keycode, t_rt *rt)
{
	int		keybit;

	if (rt->settings.cfgbits & RT_CFGB_INTERFEDIT)
		return (keydown_interface(keycode, rt));
	toggle_key(keycode, rt);
	keybit = getkeybit(keycode);
	if ((!keybit) || (rt->keyboard & QUIT))
		return (0);
	rt->keyboard |= keybit;
	menu_kb_copy(rt);
	return (0);
}

int				keyrlz(int keycode, t_rt *rt)
{
	int		keybit;

	if (rt->settings.cfgbits & RT_CFGB_INTERFEDIT)
	{
		if ((keycode == SDLK_LSHIFT) && (rt->interf.flags & INTER_UPCASE))
			rt->interf.flags &= ~INTER_UPCASE;
		return (0);
	}
	keybit = getkeybit(keycode);
	if ((!keybit) || (rt->keyboard & QUIT))
		return (0);
	rt->keyboard ^= keybit;
	menu_kb_copy(rt);
	return (0);
}
