/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 13:25:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 03:19:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "rt.h"
#include "libft.h"
#include "objects.h"
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

static void	sda_export_line(t_obj *obj, t_sda_export *export,
	const unsigned int lvl, const int p)
{
	char	*value;

	if (!(value = export->cfg[p].export(obj, export)))
		return ;
	write(export->fd, export->tbl, lvl + 1);
	ft_putstr_fd(export->cfg[p].str, export->fd);
	ft_putchar_fd(' ', export->fd);
	ft_putendl_fd(value, export->fd);
	free(value);
}

static void	sda_export_item_loop(t_obj *obj, t_sda_export *export,
	const unsigned int lvl, int p)
{
	while (p < SDA_SETUP_TYPES)
	{
		if (((int)obj->type & export->cfg[p].obj_valid_type) &&
			(export->cfg[p].export))
		{
			sda_export_line(obj, export, lvl, p);
		}
		p++;
	}
}

static int	sda_export_item(t_obj *obj, int mode, void *userdata)
{
	const unsigned int	lvl = rt_obj_get_lvl(obj) - 1;
	t_sda_export		*export;

	(void)mode;
	if (obj->cfgbits & SDB_NOEXPORT)
		return (STOP_NODE);
	export = userdata;
	if (obj->type == SETTING)
		sda_settings_stack(export->setting_obj, obj);
	if (!(export->tbl = sda_export_ntab(lvl + 1)))
		return (-1);
	write(export->fd, export->tbl, lvl);
	rt_puttype(obj->type, export->fd);
	write(export->fd, "\n", 1);
	sda_export_item_loop(obj, export, lvl, 0);
	free(export->tbl);
	return (OK);
}

void		sda_export(const t_rt *rt, const int fd)
{
	const t_sda_cfg	*cfg;
	t_sda_export	export;
	t_setting		stack_setting;
	t_obj			setting_obj;

	cfg = g_sda_cfg;
	rt_obj_init(&setting_obj, SETTING | NOSHADER);
	setting_obj.content = &stack_setting;
	stack_setting = (t_setting){0x000000, 1.0f, NULL, 0, 0.0,
		rt->settings.bgcolor};
	export = (t_sda_export){cfg, &stack_setting, &setting_obj, NULL, fd};
	ft_putstr_fd("#sda export\n", fd);
	rt_node_foreach(rt->root, INFIX, &sda_export_item, &export);
	ft_putstr_fd("#end of file\n", fd);
}
