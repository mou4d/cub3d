/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:41 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/17 22:58:58 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_mlx(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	put_px(t_map *map, mlx_image_t *img, int x, int y, uint32_t color)
{
	int tx, ty;
	tx = x;
	ty = y;
	while(ty < y + map->height_size)
	{
		tx = x;
		while(tx < x + map->width_size)
		{
			mlx_put_pixel(img, 0.2 * tx, 0.2 * ty, color);
			tx++;
		}
		ty++;
	}
}

void	draw_mini_map(t_map *map, mlx_image_t *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (map->map_s[y])
	{
		x = -1;
		while(map->map_s[y][++x])
		{
			if(map->map_s[y][x] == '1')
				put_px(map, img, (x * map->width_size), y * map->height_size, 0xFF0000FF);
			else
				put_px(map, img, (x * map->width_size), y * map->height_size, 0x0);
		}
		y++;
	}
}

double	make_angle_postive(double angle)
{
	angle =  fmod(angle , (2 * M_PI));
	if(angle < 0)
		angle = (2 * M_PI) + angle;
	return angle;
}

// void draw_line(t_map *map, double x1, double y1, double x2, double y2) {
//     double dx = x2 - x1;
//     double dy = y2 - y1;
//     double steps;

//     if (fabs(dx) > fabs(dy)) {
//         steps = fabs(dx);
//     } else {
//         steps = fabs(dy);
//     }
// 	printf("step == %f \n", dy);
//     double x_increment = dx / steps;
//     double y_increment = dy / steps;
//     double x = x1;
//     double y = y1;

//     for (int i = 0; i < steps; i++) {
//         mlx_put_pixel(map->img, x, y, 0x007258);
//         x += x_increment;
//         y += y_increment;
//     }
// }
double calculate_distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void	angle_facing(t_angle_facing *mongol, double rayangle)
{
	if (rayangle > 0 && rayangle < M_PI) {
	    mongol->r_anglefacingdown = true;
	    mongol->r_anglefacingup = false;
	}
	else
	{
	    mongol->r_anglefacingup = true;
	    mongol->r_anglefacingdown = false;
	}

	if (rayangle < (1.5 * M_PI) && rayangle > M_PI_2) {
	    mongol->r_anglefacingleft = true;
	    mongol->r_anglefacingright = false;
	}
	else
	{
	    mongol->r_anglefacingright = true;
	    mongol->r_anglefacingleft = false;
	}
}

double  find_y_horztouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	int x, y;
	double x_wallhit = 0;
	double y_wallhit = 0;
	double distance = 0;
	double xintercept, yintercept;
	double xstep, ystep;
	yintercept = floor(map->plr->y / map->height_size) * map->height_size;
	if (a_f->r_anglefacingdown == true)
	    yintercept += map->height_size;
	xintercept = map->plr->x + (((yintercept - map->plr->y) )/ tan(rayangle));
	ystep = map->height_size;
	if (a_f->r_anglefacingup == true)
	    ystep *= -1;

	xstep = map->width_size / tan(rayangle);
	if(a_f->r_anglefacingleft && xstep > 0)
		xstep *= -1;
	if(a_f->r_anglefacingright && xstep < 0)
		xstep *= -1;
	if ((a_f->r_anglefacingleft == true && xstep > 0) || (a_f->r_anglefacingright == true && xstep < 0))
	    xstep *= -1;

	x_wallhit = xintercept;
	y_wallhit = yintercept;

	if(a_f->r_anglefacingup)
		y_wallhit--;
	x = x_wallhit / map->width_size;
	y = y_wallhit / map->height_size;
	while (x >= 0 && y >= 0 && y < map->height_map &&  x <= map->width_map[y] && y_wallhit >= 0)
	{
	    if (map->map_s[y][x] == '1')
	        break;
		else
		{
	        x_wallhit += xstep;
	        y_wallhit += ystep;
	        x = x_wallhit / map->width_size;
	    	y = y_wallhit / map->height_size;
	    }
	}
	return calculate_distance(map->plr->x, map->plr->y, x_wallhit, y_wallhit);
}

double find_x_verticletouch(t_map *map, double rayangle, t_angle_facing *a_f)
{
	int x, y;
	double x_wallhit = 0;
	double y_wallhit = 0;
	double distance = 0;
	double xintercept, yintercept;
	double xstep, ystep;
	bool hit_or_not;

	xintercept = floor(map->plr->x / map->width_size) * map->width_size;
	if (a_f->r_anglefacingright == true)
	    xintercept += map->width_size;
	yintercept = map->plr->y + ((xintercept - map->plr->x)  * tan(rayangle));
	xstep = map->width_size;
	if (a_f->r_anglefacingleft  == true)
	    xstep *= -1;

	ystep = map->height_size * tan(rayangle);
	if(a_f->r_anglefacingup && ystep > 0)
		ystep *= -1;
	if(a_f->r_anglefacingdown && ystep < 0)
		ystep *= -1;

	x_wallhit = xintercept;
	y_wallhit = yintercept;

	if(a_f->r_anglefacingleft)
		x_wallhit--;
	x = x_wallhit / map->width_size;
	y = y_wallhit / map->height_size;
	hit_or_not = false;
	while (x >= 0 && y >= 0 && y < map->height_map &&  x <= map->width_map[y] && y_wallhit >= 0)
	{
	    if (map->map_s[y][x] == '1') {
			hit_or_not = true;
	        break;
	    }
		else
		{
	        x_wallhit += xstep;
	        y_wallhit += ystep;
	        x = x_wallhit / map->width_size;
	    	y = y_wallhit / map->height_size;
	    }
	}
	return calculate_distance(map->plr->x, map->plr->y, x_wallhit, y_wallhit);
}

double	hm_px_bw_pyr_and_wall(t_map *map,double rayangle)
{
	int x, y;
	double xdistance;
	double ydistance;
	t_angle_facing  *a_f;
	a_f = malloc(sizeof(t_angle_facing));
	if(!a_f)
		exit(33);
	angle_facing(a_f, rayangle);
	ydistance = find_y_horztouch(map, rayangle, a_f);
	xdistance = find_x_verticletouch(map, rayangle, a_f);
	if(ydistance < xdistance)
		return ydistance;
	else
		return xdistance;
}
//draw_line_direction(map, rayangle, xdistance);
void	cast_rays(t_map *map)
{
	double rayangle;
	int px_line;
	rayangle = make_angle_postive(map->plr->retactionangle - (map->plr->fovue_angle / 2));

	int i = 0;
	while(i < map->plr->num_arys)
	{
		map->wall3d->rays_angle[i] = rayangle;
		map->wall3d->small_distance[i] = hm_px_bw_pyr_and_wall(map, rayangle);
		draw_line_direction(map, map->wall3d->rays_angle[i], map->wall3d->small_distance[i]);
		rayangle = make_angle_postive(rayangle + (map->plr->fovue_angle / map->plr->num_arys));
		i++;
	} 
}

void	draw_line_direction(t_map *map, double ray_angle, double line_px)
{
	double x;
	x = 0;
	while(x < line_px)
	{
		mlx_put_pixel(
				map->img,
				0.2 * (map->plr->x + x * cos(ray_angle)),
				0.2 * (map->plr->y + x * sin(ray_angle)),
				0x007258
			);
		x++;
	}
}

void	draw_player(t_map *map, mlx_image_t *img)
{
	int x;
	int y;
	t_plr *ply;

	ply = map->plr;
	x = ply->x  - ply->radius;
	while (x <= ply->x + ply->radius)
	{
		y = ply->y - ply->radius;
		while(y <= ply->y + ply->radius)
		{
			if(((x - ply->x) * (x - ply->x)) + ((y - ply->y) * ((y - ply->y))) <= (ply->radius * ply->radius))
				mlx_put_pixel(img, 0.2 * x, 0.2 * y, 0x007258);
			y++;
		}
		x++;
	}
}


void	clear_windows(t_map *map)
{
	int x;
	int y;
	x = 0;
	while(x < map->Xwindows_width)
	{
		y = 0;
		while (y < map->Ywindows_height)
		{
			mlx_put_pixel(map->img, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

void	init_mlx(t_map *map)
{
	clear_windows(map);
	draw_mini_map(map, map->img);
	draw_player(map, map->img);
	cast_rays(map);
	// wall_3d(map);
}