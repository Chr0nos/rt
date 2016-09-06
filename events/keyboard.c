/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/06 18:38:54 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "libft.h"
#include "menu.h"
#include "sda.h"

static int		keydown_interface(int keycode, t_rt *rt)
{
	int		p;

	if (keycode == SDLK_ESCAPE)
	{
		rt->settings.cfgbits ^= RT_CFG_INTERFEDIT;
		return (0);
	}
	if (keycode == SDLK_DELETE)
	{
		p = rt->interf.line_pos - 1;
		if (p < 0)
			p = 0;
		rt->interf.line[p] = '\0';
		rt->interf.line_pos = p;
		return (0);
	}
	p = rt->interf.line_pos + 1;
	if (p > 31)
		return (0);
	rt->interf.line[p] = (char)(keycode & 0xff);
	rt->interf.line[p + 1] = '\0';
	ft_putendl(rt->interf.line);
	rt->interf.line_pos = p;
	rt->settings.cfgbits |= RT_CFGB_REFRESHINTER;
	return (0);
}

int				keydown(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if (rt->settings.cfgbits & RT_CFG_INTERFEDIT)
		return (keydown_interface(keycode, rt));
	toggle_key(keycode, rt);
	if ((keybit < 0) || (rt->keyboard & QUIT))
		return (0);
	rt->keyboard |= keybit;
	menu_kb_copy(rt);
	return (0);
}

int				keyrlz(int keycode, t_rt *rt)
{
	const int		keybit = getkeybit(keycode);

	if (rt->settings.cfgbits & RT_CFG_INTERFEDIT)
		return (0);
	if ((keybit < 0) || (!(rt->keyboard & keybit)))
		return (0);
	rt->keyboard ^= keybit;
	menu_kb_copy(rt);
	return (0);
}
