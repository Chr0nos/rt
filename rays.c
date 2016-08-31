/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 20:13:00 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "filter.h"
#include "threading.h"
#include <unistd.h>

char			rt_rays_pc(const t_v2i *geometry, const t_v2i *px)
{
	float		endx;
	float		posx;
	float		endy;
	float		posy;

	endy = (float)(geometry->y);
	endx = (float)(geometry->x);
	posy = (float)(px->y);
	posx = (float)(px->x);
	return ((char)(
		((1.0f - (posx / endx)) + ((1.0f - (posy / endy)) / endx)) * 100.0f));
}

/*
** this function flush the image to the screen evrey 100 pixels (width)
*/

static void		rt_ray_refresh(const t_v2i *px, const t_rt *rt)
{
	if ((!(rt->settings.cfgbits & RT_CFGB_NOREFRESHX)) && (!(px->x % 200)) &&
		(rt->sys.screen))
		sdl_flush(rt);
}

/*
** preparation of the rt_rays_pixels function
*/

static void		rt_rays_pixels_init(t_v2i *px, const t_thread_args *args,
		t_v4d *rad, t_camera **camp)
{
	t_rt	*rt;

	rt = args->rt;
	*camp = ((t_obj*)args->rt->root->content)->content;
	*px = (t_v2i){0, 0};
	if (!(rt->settings.cfgbits & RT_CFGB_INMENU))
		rt_signal_singletone(&rt->sys.geometry, px, 0);
	*rad = (t_v4d){(*camp)->rayfix.x, 0, (*camp)->rayfix.z, (*camp)->rayfix.w};
	px->x = args->x_start;
	rad->x -= rad->z * (args->rt->sys.geometry.x - px->x);
}

static void		*rt_rays_pixels_threaded(const t_thread_args *args)
{
	t_v2i				px;
	t_v4d				rad;
	t_camera			*camp;
	t_ray				ray;

	rt_rays_pixels_init(&px, args, &rad, &camp);
	ray = (t_ray){args->m.w, (t_v4d){0.0, 0.0, 1.0, 0.0}, 0.0, 0, 0x0, 0};
	while (px.x++ < args->x_end)
	{
		px.y = args->rt->sys.geometry.y - 1;
		rad.y = camp->rayfix.y;
		while (px.y--)
		{
			ray.count = 6;
			ray.dir = geo_m4trans(
				geo_normv4((t_v4d){rad.x, -rad.y, 1.0, 0.0}), &(args->m));
			args->pixels[px.y * args->rt->sys.geometry.x + px.x] =
				args->rt->rayfunc(args->rt, &ray);
			rad.y -= rad.w;
		}
		rt_ray_refresh(&px, args->rt);
		rad.x += rad.z;
	}
	return (NULL);
}

static void		rt_rays_pixels(t_rt *rt, unsigned int *pixels,
	t_m4 m)
{
	pthread_t			threads[THREAD_COUNT];
	t_thread_args		args[THREAD_COUNT];
	int					i;

	i = -1;
	while (++i < THREAD_COUNT)
	{
		args[i].rt = rt;
		args[i].pixels = pixels;
		args[i].m = m;
		args[i].index = i;
		args[i].thread_count = THREAD_COUNT;
		args[i].x_start = rt->sys.geometry.x / THREAD_COUNT * i;
		args[i].x_end = args[i].x_start + rt->sys.geometry.x / THREAD_COUNT;
		pthread_create(threads + i, NULL,
				(void *(*)(void*))&rt_rays_pixels_threaded, args + i);
	}
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_join(threads[i], NULL);
	if (!(rt->settings.cfgbits & RT_CFGB_INMENU))
		rt_signal_singletone(NULL, NULL, 1);
	filter_apply(rt->sys.screen, rt->keyboard);
}

void			rt_rays(t_rt *rt)
{
	t_obj		*cam;

	cam = (t_obj*)rt->root->content;
	rt_update_camera(rt->sys.geometry, cam->content);
	((t_camera*)cam->content)->raypos = cam->trans.w;
	rt_rays_pixels(rt, rt->sys.screen->pixels, cam->trans);
}
