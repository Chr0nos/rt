/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_parse_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/19 17:04:48 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/21 16:31:38 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"
#include "libft.h"

static void		yolo_parse_setting(char *setting, t_rtcfg *rset)
{
	char				**split;
	size_t				size;
	int					i;
	const t_parset_cfg	setparse[] = {
			(t_parset_cfg){"ambiant", &yolo_setting_ambiant},
			(t_parset_cfg){"AL", &yolo_setting_ambiant}};

	if ((!setting) || (ft_stronlystr(setting, ":")))
		return ;
	i = 2;
	split = ft_strsplit(setting, ':');
	size = ft_tabcount((void**)split) - 1;
	while (i--)
		if ((!ft_strcmp(split[0], setparse[i].name)) &&
			setparse[i].config(split, size, rset))
			break ;
	ft_free_tab(split, (unsigned int)size);
	free(split);
}

int				yolo_parse_settings(char *line, t_rtcfg *rset)
{
	char				**split;
	size_t				size;
	size_t				i;

	if (ft_strncmp(line, "SETTING", 7))
		return (0);
	split = ft_strsplitstr(line, " \t");
	size = ft_tabcount((void**)split) - 1;
	(void)rset;
	i = 1;
	while (i < size)
		yolo_parse_setting(split[i++], rset);
	ft_free_tab(split, (unsigned int)size);
	free(split);
	return (1);
}
