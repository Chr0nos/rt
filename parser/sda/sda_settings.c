/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:09:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 03:20:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

void			sda_settings_stack(t_obj *stack, t_obj *s)
{
	t_setting	*o;
	t_setting	*x;

	x = s->content;
	o = stack->content;
	if (s->cfgbits & SDB_COLOR)
		o->color = x->color;
	if (s->cfgbits & SDB_SIZE)
		o->size = x->size;
	if (s->cfgbits & SDB_REFLECT)
		o->reflect = x->reflect;
	if (s->cfgbits & SDB_BACKGROUND)
		o->bgcolor = x->bgcolor;
}

static int		sda_warning(t_sda *e, const char *msg, const char *opt, int ret)
{
	ft_putstr("warning: obj: ");
	rt_node_display(e->current_obj, 0, NULL);
	ft_printf("options: [%s] -> %s (fd: %d)\n", opt, msg, e->fd);
	return (ret);
}

const t_sda_cfg	*sda_settings_bysetup(const void *setup)
{
	int					p;
	const t_sda_cfg		*cfg;

	p = SDA_SETUP_TYPES;
	while (p--)
	{
		cfg = &g_sda_cfg[p];
		if ((void*)(unsigned long)cfg->config == setup)
			return (cfg);
	}
	return (NULL);
}

int				sda_settings(t_sda *e, int ac, char **av)
{
	int					p;
	int					ret;
	const t_sda_cfg		*cfg;

	cfg = g_sda_cfg;
	p = SDA_SETUP_TYPES;
	while (p--)
	{
		if (!ft_strcmp(cfg[p].str, av[0]))
		{
			if (!((int)e->current_obj->type & cfg[p].obj_valid_type))
				return (sda_warning(e, "not eligible", av[0], -1));
			else if (!cfg[p].config)
				return (0);
			else if (ac - 2 < cfg[p].argc)
				return (sda_warning(e, "missing params", av[0], -3));
			ret = cfg[p].config(e, e->current_obj, &av[1]);
			if (ret > 0)
				e->current_obj->cfgbits |= cfg[p].bit;
			return (ret);
		}
	}
	return (-2);
}
