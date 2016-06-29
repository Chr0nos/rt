/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 01:14:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 01:22:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sda.h"
#include "parser.h"
#include "libft.h"

t_obj	*rt_parser(const char *filepath, t_rt *rt)
{
	const char	*end = ft_strrchr((char*)(unsigned long)filepath, '.');

	if (!end)
		return (NULL);
	else if (!ft_strcmp(end, ".yolo"))
		return (yolo_parse(filepath, &rt->settings));
	else if (!ft_strcmp(end, ".sda"))
		return (sda_parse(filepath, rt));
	ft_putstr_fd("unknow file type: ", 2);
	ft_putendl_fd(end, 2);
	return (NULL);
}
