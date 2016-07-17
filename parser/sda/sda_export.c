/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 13:25:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 14:46:56 by snicolet         ###   ########.fr       */
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

	if (!(tbl = malloc(lvl + 1)))
		return (NULL);
	tbl[lvl] = '\0';
	ft_memset(tbl, '\t', lvl);
	return (tbl);
}

static void	sda_export_settings(const t_rt *rt)
{
	char		color_str[12];
	char		reflect_str[4];
	char		background_str[12];
	char		*al;

	ft_itobuff(reflect_str, (int)rt->settings.default_reflect,
		10, "0123456789");
	sda_export_color_raw(rt->settings.default_color, color_str);
	sda_export_color_raw(rt->settings.bgcolor, background_str);
	al = sda_double_short(ft_dtoa(rt->settings.ambiant_light * 100.0, 6));
	ft_printf("SETTING\n\tcolor: %s\n\treflect: %s\n\tal: %s\n",
		color_str, reflect_str, al);
	ft_printf("\tbackground: %s\n", background_str);
	free(al);
}

static void sda_export_line(t_obj *obj, t_sda_export *export,
	const unsigned int lvl, const int p)
{
	char	*value;

	if (!(value = export->cfg[p].export(obj)))
		return ;
	write(export->fd, export->tbl, lvl + 1);
	ft_putstr_fd(export->cfg[p].str, export->fd);
	ft_putchar_fd(' ', export->fd);
	ft_putendl_fd(value, export->fd);
	free(value);
}

static int	sda_export_item(t_obj *obj, int mode, void *userdata)
{
	const unsigned int	lvl = rt_obj_get_lvl(obj) - 1;
	t_sda_export		*export;
	int					p;

	(void)mode;
	export = userdata;
	if (!(export->tbl = sda_export_ntab(lvl + 1)))
		return (-1);
	write(export->fd, export->tbl, lvl);
	rt_puttype(obj->type, export->fd);
	write(export->fd, "\n", 1);
	p = 0;
	while (p < SDA_SETUP_TYPES)
	{
		if (((int)obj->type & export->cfg[p].obj_valid_type) &&
			(export->cfg[p].export))
		{
			sda_export_line(obj, export, lvl, p);
		}
		p++;
	}
	free(export->tbl);
	return (OK);
}

void		sda_export(const t_rt *rt, const int fd)
{
	t_sda_cfg		cfg[SDA_SETUP_TYPES];
	t_sda_export	export;

	sda_settings_init(cfg);
	export = (t_sda_export){(t_sda_cfg*)&cfg, NULL, fd};
	ft_putstr_fd("#sda export\n", fd);
	sda_export_settings(rt);
	rt_node_foreach(rt->root, INFIX, &sda_export_item, &export);
	ft_putstr_fd("#end of file\n", fd);
}
