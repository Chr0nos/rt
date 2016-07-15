/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:09:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 16:34:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#define SDA_SETUP_TYPES 15
#define T (t_sda_cfg)

void		sda_settings_init(t_sda_cfg *cfg)
{
	cfg[0] = T{"color:", &sda_setup_color, NULL, SDA_COLOR, 1,
		SDB_COLOR};
	cfg[1] = T{"pos:", &sda_setup_pos, &sda_export_pos, SDA_POS, 3,
		SDB_POS};
	cfg[2] = T{"rot:", &sda_setup_rot, NULL, SDA_ROT, 3, SDB_ROT};
	cfg[3] = T{"size:", &sda_setup_size, NULL, SDA_SIZE, 1, SDB_SIZE};
	cfg[4] = T{"al:", &sda_setup_al, NULL, SDA_AL, 1, SDB_AL};
	cfg[5] = T{"fov:", &sda_setup_fov, NULL, SDA_FOV, 1, SDB_FOV};
	cfg[6] = T{"intensity:", &sda_setup_intensity, NULL, SDA_INTEN, 1,
		SDB_INTEN};
	cfg[7] = T{"refract:", &sda_setup_refract, NULL, SDA_REFRACT, 1,
		SDB_REFRACT};
	cfg[8] = T{"include:", &sda_setup_include, NULL, SDA_INCLUDE, 1,
		SDB_INCLUDE};
	cfg[9] = T{"angle:", &sda_setup_angle, NULL, SDA_ANGLE, 1, SDB_ANGLE};
	cfg[10] = T{"copy:", &sda_setup_copy, NULL, SDA_COPY, 1, SDB_COPY};
	cfg[11] = T{"name:", &sda_setup_name, NULL, SDA_NAME, 1, SDB_NAME};
	cfg[12] = T{"texture:", &sda_setup_texture, NULL, SDA_TEXTURE, 1,
		SDB_TEXTURE};
	cfg[13] = T{"reflect:", &sda_setup_reflect, NULL, SDA_REFLECT, 1,
		SDB_REFLECT};
	cfg[14] = T{"background:", &sda_setup_background, NULL,
		SDA_BACKGROUND,	1, SDB_BACKGROUND};
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
