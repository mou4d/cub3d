/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_rays_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 02:23:21 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/04 23:45:50 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

typedef struct s_horz_and_verticle_touch
{
	int		x;
	int		y;
	double	x_wallhit;
	double	y_wallhit;
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
}	t_varb_horz;

double	find_y_horztouch_helper(t_map *map, t_varb_horz *p,
		t_angle_facing *a_f)
{
	double	rtn_value;

	if (a_f->r_anglefacingup)
		p->y_wallhit--;
	p->x = p->x_wallhit / map->size_wall_y_x;
	p->y = p->y_wallhit / map->size_wall_y_x;
	while (p->x >= 0 && p->y >= 0 && p->y < map->height_map
		&& p->x <= map->width_map[p->y] && p->y_wallhit >= 0)
	{
		if (map->map_s[p->y][p->x] == '1')
			break ;
		else
		{
			p->x_wallhit += p->xstep;
			p->y_wallhit += p->ystep;
			p->x = p->x_wallhit / map->size_wall_y_x;
			p->y = p->y_wallhit / map->size_wall_y_x;
		}
	}
	rtn_value = calculate_distance(map->plr->x, map->plr->y,
			p->x_wallhit, p->y_wallhit);
	free(p);
	return (rtn_value);
}

double	find_y_horztouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	t_varb_horz	*p;

	p = malloc(sizeof(t_varb_horz));
	p->yintercept = floor(map->plr->y / map->size_wall_y_x)
		* map->size_wall_y_x;
	if (a_f->r_anglefacingdown == true)
		p->yintercept += map->size_wall_y_x;
	p->xintercept = map->plr->x + (((p->yintercept - map->plr->y))
			/ tan(rayangle));
	p->ystep = map->size_wall_y_x;
	if (a_f->r_anglefacingup == true)
		p->ystep *= -1;
	p->xstep = map->size_wall_y_x / tan(rayangle);
	if (a_f->r_anglefacingleft && p->xstep > 0)
		p->xstep *= -1;
	if (a_f->r_anglefacingright && p->xstep < 0)
		p->xstep *= -1;
	if ((a_f->r_anglefacingleft == true && p->xstep > 0)
		|| (a_f->r_anglefacingright == true && p->xstep < 0))
		p->xstep *= -1;
	p->x_wallhit = p->xintercept;
	p->y_wallhit = p->yintercept;
	return (find_y_horztouch_helper(map, p, a_f));
}

double	find_x_vertical_helper(t_map *map, t_varb_horz *p, t_angle_facing *a_f)
{
	double	rtn_value;

	if (a_f->r_anglefacingleft)
		p->x_wallhit--;
	p->x = p->x_wallhit / map->size_wall_y_x;
	p->y = p->y_wallhit / map->size_wall_y_x;
	while (p->x >= 0 && p->y >= 0 && p->y < map->height_map
		&& p->x <= map->width_map[p->y] && p->y_wallhit >= 0)
	{
		if (map->map_s[p->y][p->x] == '1')
			break ;
		else
		{
			p->x_wallhit += p->xstep;
			p->y_wallhit += p->ystep;
			p->x = (int)p->x_wallhit / map->size_wall_y_x;
			p->y = (int)p->y_wallhit / map->size_wall_y_x;
		}
	}
	rtn_value = calculate_distance(map->plr->x, map->plr->y,
			p->x_wallhit, p->y_wallhit);
	free(p);
	return (rtn_value);
}

double	find_x_verticletouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	t_varb_horz	*p;

	p = malloc(sizeof(t_varb_horz));
	p->xintercept = floor(map->plr->x / map->size_wall_y_x)
		* map->size_wall_y_x;
	if (a_f->r_anglefacingright == true)
		p->xintercept += map->size_wall_y_x;
	p->yintercept = map->plr->y + ((p->xintercept - map->plr->x)
			* tan(rayangle));
	p->xstep = map->size_wall_y_x;
	if (a_f->r_anglefacingleft == true)
		p->xstep *= -1;
	p->ystep = map->size_wall_y_x * tan(rayangle);
	if (a_f->r_anglefacingup && p->ystep > 0)
		p->ystep *= -1;
	if (a_f->r_anglefacingdown && p->ystep < 0)
		p->ystep *= -1;
	p->x_wallhit = p->xintercept;
	p->y_wallhit = p->yintercept;
	return (find_x_vertical_helper(map, p, a_f));
}
