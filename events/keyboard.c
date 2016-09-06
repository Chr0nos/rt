/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 17:40:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/07 01:01:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "libft.h"
#include "menu.h"
#include "sda.h"

/*
** this function is called when the user press RETURN in edit mode
*/

static int		keydown_interface_enter(t_rt *rt)
{
	t_interface_cfg		*cfg;

	cfg = interf_getflag(&rt->interf, INTER_SELECTED, 0);
	if ((!cfg) || (!cfg->set_value) || (!rt->interf.obj_selected))
		return (0);
	cfg->set_value(rt->interf.obj_selected, rt->interf.line);
	return (0);
}

static int		keydown_interface_backspace(int p, t_rt *rt)
{
	if (p < 0)
		p = 0;
	rt->interf.line[p] = '\0';
	rt->interf.line_pos = p;
	return (0);
}

static int		keydown_interface(int keycode, t_rt *rt)
{
	int		p;

	if (keycode == SDLK_ESCAPE)
	{
		rt->settings.cfgbits ^= RT_CFG_INTERFEDIT;
		return (0);
	}
	if (keycode == SDLK_BACKSPACE)
		return (keydown_interface_backspace(rt->interf.line_pos - 1, rt));
	if (keycode == SDLK_RETURN)
		return (keydown_interface_enter(rt));
	p = rt->interf.line_pos;
	if (p > INTERF_LINELEN - 1)
		return (0);
	rt->interf.line[p] = (char)(keycode & 0xff);
	rt->interf.line[p + 1] = '\0';
	rt->interf.line_pos = p + 1;
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
