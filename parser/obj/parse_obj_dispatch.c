/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_dispatch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 21:20:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 21:21:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int		parse_obj_dispatch(t_sda_obj *s, char *line)
{
	IFRET__(line[0] == '#', 0);
	IFRET__(!sda_spliter(line, &s->av, &s->ac), -2);
	if (!ft_strcmp(s->av[0], "o"))
		ft_printf("#\t-Loading %s object..\n", s->av[1]);
	IFRET__(s->ac < 4, 1);
	IFRET__(!ft_strcmp(s->av[0], "v"), parse_obj_v(s));
	IFRET__(!ft_strcmp(s->av[0], "vn"), parse_obj_n(s));
	IFRET__(!ft_strcmp(s->av[0], "vt"), parse_obj_uv(s));
	IFRET__(!ft_strcmp(s->av[0], "f"), parse_obj_f(s));
	return (1);
}
