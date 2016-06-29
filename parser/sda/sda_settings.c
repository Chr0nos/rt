/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:09:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 21:27:59 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#define SDA_SETUP_TYPES 8

void		sda_settings_init(t_sda_cfg *cfg)
{
	cfg[0] = (t_sda_cfg){"color:", &sda_setup_color, SDA_COLOR, 1, SDB_COLOR};
	cfg[1] = (t_sda_cfg){"pos:", &sda_setup_pos, SDA_POS, 3, SDB_POS};
	cfg[2] = (t_sda_cfg){"rot:", &sda_setup_rot, SDA_ROT, 3, SDB_ROT};
	cfg[3] = (t_sda_cfg){"size:", &sda_setup_size, SDA_SIZE, 1, SDB_SIZE},
	cfg[4] = (t_sda_cfg){"radius:", &sda_setup_size, SDA_SIZE, 1, SDB_SIZE},
	cfg[5] = (t_sda_cfg){"al:", &sda_setup_al, SDA_AL, 1, SDB_AL},
	cfg[6] = (t_sda_cfg){"fov:", &sda_setup_fov, SDA_FOV, 1, SDB_FOV},
	cfg[7] = (t_sda_cfg){"intensity:", &sda_setup_intensity, SDA_INTEN, 1,
		SDB_INTEN};
}

static int	sda_warning(t_obj *obj, const char *msg, const char *opt, int ret)
{
	ft_printf("warning: obj: %d: options: [%s] -> %s\n",
		(int)obj->id,
		opt,
		msg);
	return (ret);
}

int			sda_settings(t_obj *obj, t_rt *rt, int ac, char **av)
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
			if (!((int)obj->type & cfg[p].obj_valid_type))
				return (sda_warning(obj, "not eligible", av[0], -1));
			else if (!cfg[p].config)
				return (0);
			else if (ac - 2 < cfg[p].argc)
				return (sda_warning(obj, "missing params", av[0], -3));
			ret = cfg[p].config(rt, obj, &av[1]);
			if (ret >= 0)
				obj->cfgbits |= cfg[p].bit;
			return (ret);
		}
	}
	return (-2);
}
