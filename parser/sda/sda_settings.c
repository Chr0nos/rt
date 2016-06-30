/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:09:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 19:01:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#define SDA_SETUP_TYPES 10

void		sda_settings_init(t_sda_cfg *cfg)
{
	cfg[0] = (t_sda_cfg){"color:", &sda_setup_color, SDA_COLOR, 1, SDB_COLOR};
	cfg[1] = (t_sda_cfg){"pos:", &sda_setup_pos, SDA_POS, 3, SDB_POS};
	cfg[2] = (t_sda_cfg){"rot:", &sda_setup_rot, SDA_ROT, 3, SDB_ROT};
	cfg[3] = (t_sda_cfg){"size:", &sda_setup_size, SDA_SIZE, 1, SDB_SIZE};
	cfg[4] = (t_sda_cfg){"al:", &sda_setup_al, SDA_AL, 1, SDB_AL};
	cfg[5] = (t_sda_cfg){"fov:", &sda_setup_fov, SDA_FOV, 1, SDB_FOV};
	cfg[6] = (t_sda_cfg){"intensity:", &sda_setup_intensity, SDA_INTEN, 1,
		SDB_INTEN};
	cfg[7] = (t_sda_cfg){"refract:", &sda_setup_refract, SDA_REFRACT, 1,
		SDB_REFRACT};
	cfg[8] = (t_sda_cfg){"include:", &sda_setup_include, SDA_INCLUDE, 1,
		SDB_INCLUDE};
	cfg[9] = (t_sda_cfg){"angle:", &sda_setup_angle, SDA_ANGLE, 1, SDB_ANGLE};
}

static int	sda_warning(t_sda *e, const char *msg, const char *opt, int ret)
{
	ft_putstr("warning: obj: ");
	rt_node_display(e->current_obj, 0, NULL);
	ft_printf("options: [%s] -> %s (fd: %d)\n", opt, msg, e->fd);
	return (ret);
}

int			sda_settings(t_sda *e, int ac, char **av)
{
	int					p;
	int					ret;
	t_sda_cfg			cfg[SDA_SETUP_TYPES];

	sda_settings_init(cfg);
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
			if (ret >= 0)
				e->current_obj->cfgbits |= cfg[p].bit;
			return (ret);
		}
	}
	return (-2);
}
