/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzakkabi <wzakkabi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 04:20:26 by wzakkabi          #+#    #+#             */
/*   Updated: 2023/12/04 23:46:35 by wzakkabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	error_mlx(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	strlen_map_big_width_and_height(char **p, char c)
{
	int	i;
	int	big_value;

	i = 0;
	big_value = 0;
	while (p && p[i])
	{
		if (ft_strlen(p[i]) >= (size_t)big_value)
			big_value = ft_strlen(p[i]);
		i++;
	}
	if (c == 'h')
		return (i);
	return (big_value);
}

void	strlen_wight_pointer(t_map *map)
{
	int	i;

	i = -1;
	while (map->map_s[++i])
		map->width_map[i] = ft_strlen(map->map_s[i]);
}
