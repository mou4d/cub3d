/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:33:41 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/11/17 19:36:03 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_mlx(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	*get_window_size(t_map *map)
{
	int	i;
	int	j;
	int	*ret;

	if (!check_top_border(map))
		return (NULL);
	ret = malloc(sizeof(int) * 2);
	if (!ret)
		return (NULL);
	i = -1;
	ret[1] = 0;
	while (map->map_s[++i])
	{
		if (map->map_s[i][0] == '1'
			|| (map->map_s[i][0] == ' ' || map->map_s[i][0] == '\t'))
		{
			j = -1;
			while (map->map_s[i][++j])
				if (map->map_s[i][j] != '1' 
				&& map->map_s[i][j] != ' ' && map->map_s[i][j] != '\t')
				break ;
			ret[0] = ft_strlen(map->map_s[i]);
			ret[1] += 1;
		}
	}
	if (j == ret[0])
		return (ret);
	free(ret);
	return (NULL);
}

void mlx_put_square(mlx_image_t *image, int x, int y)
{
	int	i;
	int	px;
	int	py;

	i = 0;
	py = y;
	while (i++ < SCALLE)
	{
		px = x;
		while (px < x + SCALLE)
		{
			mlx_put_pixel(image, px, py, 0x0000FFFF);
			px++;
		}
		py += 1;
	}
}

void	init_mini_map(mlx_image_t *img, t_map *map)
{
	int		i;
	int		j;
	int		map_start = -1;
	char	**map_s;

	map_s = map->map_s;
	i = 0;
	while (map_s[i])
	{
		if (map_s[i][0] == ' ' || map_s[i][0] == '\t' || map_s[i][0] == '1')
		{
			if (map_start < 0)
				map_start = i;
			j = 0;
			while (map_s[i][j])
			{
				if (map_s[i][j] == '1' || map_s[i][j] == '0')
					mlx_put_square(img, j * SCALLE, (i - map_start ) * SCALLE);
				j++;
			}
		}
		i++;
	}
	
}

mlx_t	*init_mlx(t_map *map)
{
	mlx_t	*ret;
	int		*window_size;

	window_size = get_window_size(map);
	printf("w = %d, h = %d\n", window_size[0], window_size[1]);
	ret = mlx_init(window_size[0] * 32, window_size[1] * 32, "Test", true);
	if (!ret)
		error_mlx();
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(ret, ret->width, ret->height);
	if (!img || (mlx_image_to_window(ret, img, 0, 0) < 0))
		error_mlx();
	init_mini_map(img, map);
	return (ret);
}