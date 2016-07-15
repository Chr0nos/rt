/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 13:25:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 16:52:24 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "rt.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char		*sda_export_ntab(unsigned int lvl)
{
	char	*tbl;

	tbl = malloc(lvl + 1);
	tbl[lvl] = '\0';
	ft_memset(tbl, '\t', lvl);
	return (tbl);
}

static void	sda_export_settings(const t_rt *rt)
{
	char	color_str[12];

	sda_export_color(rt->settings.default_color, color_str);
	ft_printf("SETTING\n\tcolor: #%s\n", color_str);
}

static int	sda_export_item(t_obj *obj, int mode, void *userdata)
{
	const unsigned int	lvl = rt_obj_get_lvl(obj) - 1;
	char				*tbl;
	t_sda_cfg			*cfg;
	int					p;

	cfg = userdata;
	(void)mode;
	tbl = sda_export_ntab(lvl + 1);
	write(1, tbl, lvl);
	rt_puttype(obj->type);
	write(1, "\n", 1);
	p = SDA_SETUP_TYPES;
	while (p--)
	{
		if (((int)obj->type & cfg[p].obj_valid_type) && (cfg[p].export))
		{
			write(1, tbl, lvl + 1);
			ft_putendl("start");
			ft_putstr(cfg[p].str);
			cfg[p].export(obj);
			ft_putendl("end");
		}
	}
	// rt_node_display(obj, mode, NULL);
	free(tbl);
	return (OK);
}

void		sda_export(const t_rt *rt)
{
	t_sda_cfg		cfg[SDA_SETUP_TYPES];

	ft_putstr("#sda export\n");
	sda_export_settings(rt);
	rt_node_foreach(rt->root, INFIX, &sda_export_item, cfg);
}
