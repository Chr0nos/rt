/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 01:06:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 17:14:59 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "filter.h"
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

static void		rt_ray_refresh(const t_v2i *px, t_rt *rt)
{
	if ((!(rt->settings.cfgbits & RT_CFGB_NOREFRESHX)) && (!(px->x % 100)) &&
		(rt->sys.screen))
		sdl_flush(rt);
}

/*
** preparation of the rt_rays_pixels function
*/

static void		rt_rays_pixels_init(t_v2i *px, t_rt *rt, t_v4d *rad,
	t_camera *camp)
{
	*px = (t_v2i){0, 0};
	if (!(rt->settings.cfgbits & RT_CFGB_INMENU))
		rt_signal_singletone((t_v2i*)&rt->sys.geometry, px, 0);
	px->x = rt->sys.geometry.x;
	*rad = (t_v4d){camp->rayfix.x, 0.0, camp->rayfix.z, camp->rayfix.w};
}

#include <pthread.h>

typedef struct	s_rays_thread_args
{
	t_rt			*rt;
	unsigned int	*pixels;
	t_m4			m;
	int				index;
	int				thread_count;
}				t_rays_thread_args;

static void		*rt_rays_pixels_threaded(void *vargs)
{
	t_v2i		px;
	t_v4d		rad;
	t_camera	*camp;
	t_rays_thread_args	*args = (t_rays_thread_args*)vargs;
	camp = ((t_obj*)args->rt->root->content)->content;
	rt_rays_pixels_init(&px, args->rt, &rad, camp);

	t_ray		ray;
	ray.start = args->m.w;
	ray.limit = 0.0;
	ray.dir = (t_v4d){0.0, 0.0, 1.0, 0.0};

	px.x = args->rt->sys.geometry.x / args->thread_count * args->index;
	rad.x -= rad.z * px.x;
	int end = px.x + args->rt->sys.geometry.x / args->thread_count;
	while (px.x++ < end)
	{
		px.y = args->rt->sys.geometry.y;
		rad.y = camp->rayfix.y;
		while (px.y--)
		{
			ray.count = 6;
			ray.dir = geo_m4trans(
				geo_normv4((t_v4d){rad.x, -rad.y, 1.0, 0.0}), &(args->m));
			args->pixels[px.y * args->rt->sys.geometry.x + px.x] = args->rt->rayfunc(args->rt, &ray);
			rad.y -= rad.w;
		}
		if (args->index == 0)
			rt_ray_refresh(&px, args->rt);
		rad.x -= rad.z;
	}
	return NULL;
}

#define THREAD_COUNT 4

static void		rt_rays_pixels(t_rt *rt, unsigned int *pixels,
	t_m4 m)
{
	pthread_t			threads[THREAD_COUNT];
	t_rays_thread_args	args[THREAD_COUNT];
	int			i;
	int			thread_count = THREAD_COUNT;

	for (i = 0; i < thread_count; ++i) {
		args[i].rt = rt;
		args[i].pixels = pixels;
		args[i].m = m;
		args[i].index = i;
		args[i].thread_count = thread_count;
		pthread_create(threads + i, NULL, &rt_rays_pixels_threaded, args + i);
	}
	for (i = 0; i < thread_count; ++i) {
		pthread_join(threads[i], NULL);
	}
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
