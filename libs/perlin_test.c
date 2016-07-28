/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 00:05:48 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/28 22:32:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "geo.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_v2f		geo;
	double		d;
	double		zoom;
	char		*str;

	zoom = (ac == 2) ? ft_atod(av[1]) : 1.0;
	geo.x = 845.0f;
	geo.y = 30.1f;
	while (geo.x > 1.0f)
	{
		d = (double)geo_perlin(geo);
		str = ft_dtoa(d, 6);
		ft_putendl(str);
		free(str);
		geo.x *= 0.5f;
	}
	return (0);
}
