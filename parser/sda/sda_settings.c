/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 16:09:29 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/07 17:13:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#define T t_sda_cfg

void		sda_settings_stack(t_obj *stack, t_obj *s)
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
}

static void	sda_settings_init_bis(t_sda_cfg *cfg)
{
	cfg[14] = (T){"background:", &sda_setup_background, NULL,
		SDA_BACKGROUND, 1, SDB_BACKGROUND};
	cfg[15] = (T){"normal:", &sda_setup_normal, &sda_export_normal,
		SDA_TEXTURE, 1, SDB_NORMAL};
	cfg[16] = (T){"skybox:", &sda_setup_skybox, &sda_export_skybox, SDA_SKYBOX,
		1, SDB_SKYBOX};
	cfg[17] = (T){"sdisable:", &sda_setup_sdisable, &sda_export_sdisable,
		SDA_SDISABLE, 1, SDB_SDISABLE};
	cfg[18] = (T){"heightmap:", &sda_setup_heightmap, NULL, SDA_HEIGHTMAP,
		1, SDB_HEIGHTMAP};
	cfg[19] = (T){"texture-perlin:", &sda_setup_texture_perlin, NULL,
		SDA_TEX_PERLIN, 2, SDB_TEX_PERLIN};
	cfg[20] = (T){"vertex0:", &sda_setup_vertex_0, &sda_export_vertex0,
		SDA_VERTEX, 3, SDB_VERTEX0};
	cfg[21] = (T){"vertex1:", &sda_setup_vertex_1, &sda_export_vertex1,
		SDA_VERTEX, 3, SDB_VERTEX1};
	cfg[22] = (T){"vertex2:", &sda_setup_vertex_2, &sda_export_vertex2,
		SDA_VERTEX, 3, SDB_VERTEX2};
}

void		sda_settings_init(t_sda_cfg *cfg)
{
	cfg[0] = (T){"color:", &sda_setup_color, &sda_export_color, SDA_COLOR, 1,
		SDB_COLOR};
	cfg[1] = (T){"pos:", &sda_setup_pos, &sda_export_pos, SDA_POS, 3,
		SDB_POS};
	cfg[2] = (T){"rot:", &sda_setup_rot, &sda_export_rot, SDA_ROT, 3, SDB_ROT};
	cfg[3] = (T){"size:", &sda_setup_size, sda_export_size, SDA_SIZE, 1,
		SDB_SIZE};
	cfg[4] = (T){"al:", &sda_setup_al, &sda_export_al, SDA_AL, 1, SDB_AL};
	cfg[5] = (T){"fov:", &sda_setup_fov, NULL, SDA_FOV, 1, SDB_FOV};
	cfg[6] = (T){"intensity:", &sda_setup_intensity, &sda_export_intensity,
		SDA_INTEN, 1, SDB_INTEN};
	cfg[7] = (T){"refract:", &sda_setup_refract, &sda_export_refract,
		SDA_REFRACT, 1, SDB_REFRACT};
	cfg[8] = (T){"include:", &sda_setup_include, NULL, SDA_INCLUDE, 1,
		SDB_INCLUDE};
	cfg[9] = (T){"angle:", &sda_setup_angle, &sda_export_angle, SDA_ANGLE, 1,
		SDB_ANGLE};
	cfg[10] = (T){"copy:", &sda_setup_copy, NULL, SDA_COPY, 1, SDB_COPY};
	cfg[11] = (T){"name:", &sda_setup_name, &sda_export_name, SDA_NAME, 1,
		SDB_NAME};
	cfg[12] = (T){"texture:", &sda_setup_texture, &sda_export_texture,
		SDA_TEXTURE, 1, SDB_TEXTURE};
	cfg[13] = (T){"reflect:", &sda_setup_reflect, &sda_export_reflect,
		SDA_REFLECT, 1, SDB_REFLECT};
	sda_settings_init_bis(cfg);
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
			if (ret > 0)
				e->current_obj->cfgbits |= cfg[p].bit;
			return (ret);
		}
	}
	return (-2);
}
