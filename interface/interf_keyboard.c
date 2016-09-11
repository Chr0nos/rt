/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 16:24:27 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 16:52:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "keyboard.h"
#include "libft.h"
#include "rt.h"

/*
** this function is called when the user press RETURN in edit mode
*/

static int		keydown_interface_enter(t_rt *rt)
{
	t_interface_cfg		*cfg;

	ft_putstr("enter triggered\n");
	rt->settings.cfgbits ^= RT_CFGB_INTERFEDIT;
	cfg = interf_getflag(&rt->interf, INTER_SELECTED, 0);
	if ((!cfg) || (!cfg->set_value) || (!rt->interf.obj_selected))
	{
		ft_putstr("#warning: operation not permited\n");
		return (0);
	}
	if (interf_setvalue(rt, rt->interf.obj_selected, rt->interf.line) >= 0)
	{
		ft_putendl("#interface edit ok");
		rt->keyboard |= FORCE_DISPLAY;
		interf_resetline(&rt->interf);
	}
	else
		ft_putstr_fd("error: failed to set value\n", 2);
	cfg->flags &= ~INTER_SELECTED;
	return (0);
}

static int		keydown_interface_backspace(int p, t_rt *rt)
{
	if (p < 0)
		p = 0;
	rt->interf.line[p] = '\0';
	rt->interf.line_pos = p;
	rt->settings.cfgbits |= RT_CFGB_REFRESHINTER;
	return (0);
}

static int		keydown_interface_escape(t_rt *rt)
{
	rt->settings.cfgbits ^= RT_CFGB_INTERFEDIT;
	rt->settings.cfgbits |= RT_CFGB_REFRESHINTER;
	interf_resetline(&rt->interf);
	return (0);
}

int				keydown_interface(int keycode, t_rt *rt)
{
	int			p;

	if (keycode == SDLK_ESCAPE)
		return (keydown_interface_escape(rt));
	if (keycode == SDLK_BACKSPACE)
		return (keydown_interface_backspace(rt->interf.line_pos - 1, rt));
	if (keycode == SDLK_RETURN)
		return (keydown_interface_enter(rt));
	if (keycode == SDLK_LSHIFT)
	{
		rt->interf.flags |= INTER_UPCASE;
		return (0);
	}
	p = rt->interf.line_pos;
	if (p > INTERF_LINELEN - 1)
		return (0);
	rt->interf.line[p] = (char)(keycode & 0xff);
	if (rt->interf.flags & INTER_UPCASE)
		rt->interf.line[p] = (char)ft_toupper(rt->interf.line[p]);
	rt->interf.line[p + 1] = '\0';
	rt->interf.line_pos = p + 1;
	rt->settings.cfgbits |= RT_CFGB_REFRESHINTER;
	return (0);
}
