/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_defaults.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 21:24:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:22:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "libft.h"
#include "unistd.h"
#include "mesh.h"

static int	sda_defaults(t_obj *obj, int mode, void *userdata)
{
	t_sda_default_config	*cfg;
	int						p;

	(void)mode;
	cfg = userdata;
	p = SDA_COUNT_DEFAULTS;
	while (p--)
		if (obj->type & cfg->def[p].type_mask)
			cfg->def[p].exec(cfg->rt, obj);
	return (OK);
}

void		sda_set_defaults(t_obj *root, t_rt *rt)
{
	t_sda_default_config	cfg;
	const t_sda_default		def[SDA_COUNT_DEFAULTS] = {
		(t_sda_default){CAMERA, &sda_default_camera},
		(t_sda_default){LIGHTTYPE, &sda_default_lights},
		(t_sda_default){CONE, &sda_default_cone},
		(t_sda_default){TRIANGLE, &sda_default_triangle},
		(t_sda_default){SETTING, &sda_default_setting},
		(t_sda_default){SDA_SDISABLE, &sda_default_shaders},
		(t_sda_default){SDA_TEXTURE, &sda_default_texture},
		(t_sda_default){SDA_SIZE, &sda_default_size}
	};

	rt->tree.lnum = rt_obj_count(root, LIGHTTYPE);
	cfg.rt = rt;
	ft_memcpy(&cfg.def, &def, sizeof(t_sda_default) * SDA_COUNT_DEFAULTS);
	rt_node_foreach(root, PREFIX, &sda_defaults, &cfg);
}
