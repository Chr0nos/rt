/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:08:36 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/26 21:19:21 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture.h"
#include "libft.h"
#include "draw.h"

static void	perlin_init(unsigned char *map, int p, float **g2)
{
	const float		unit = 1.0f / sqrtf(2.0f);

	while (p--)
		map[p] = (unsigned char)(rand() & 0xff);
	g2[0] = (float [2]){unit, unit};
	g2[1] = (float [2]){-unit, unit};
	g2[2] = (float [2]){unit, -unit};
	g2[3] = (float [2]){-unit, -unit};
	g2[4] = (float [2]){1.0, 0.0};
	g2[5] = (float [2]){-1.0, 1.0};
	g2[6] = (float [2]){1.0, 1.0};
	g2[7] = (float [2]){0.0, 1.0};
	g2[8] = (float [2]){0.0, -1.0};
}

static unsigned int		perlin_v(const unsigned char *perm, const t_v2i px)
{
	unsigned int	v;

	v = (perm[px.x + perm[px.y] % 8] |
		(perm[px.x + 1 + perm[px.y] % 8] << 8) |
		(perm[px.x + perm[px.y + 1] % 8]) << 16 |
		(perm[px.x + 1 + perm[px.y + 1] % 8]) << 24);
	return (v);
}

static unsigned int		perlin_ponderate(const t_v2i tmp,
	const unsigned char index, const float **g2)
{
	return (g2[index][0]* tmp.x + g2[index][1] * tmp.y);
}

double		perlin_noise(t_v2f geo, float res)
{
	float			g2[8][2];
	unsigned char	perm[256];
	t_v2i			px;
	t_v4i			color;
	unsigned int	v;

	perlin_init(perm, 256, (float**)g2);
	geo = (t_v2f){geo.x * res, geo.y * res};
	px = (t_v2i){(int)geo.x, (int)geo.y};
	v = perlin_v(perm, px);
	color.x = perlin_ponderate(
		(t_v2i){geo.x - (float)px.x, geo.y - (float)px.y},
		v & 0xff, (const float **)g2);
	color.y = perlin_ponderate(
		(t_v2i){geo.x - (float)(px.x + 1), geo.y - (float)px.y},
		(v & 0xff00) >> 8, (const float **)g2);
	color.z = perlin_ponderate(
		(t_v2i){geo.x - (float)px.x, geo.y - (float)(px.y + 1)},
		(v & 0xff0000) >> 16, (const float **)g2);
	color.w = perlin_ponderate(
		(t_v2i){geo.x - (float)(px.x + 1), geo.y - (float)(px.y + 1)},
		(v & 0xff000000) >> 24, (const float **)g2);
	return (0.0);
}
