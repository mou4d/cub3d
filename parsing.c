/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousbaa <mbousbaa@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:57:09 by mbousbaa          #+#    #+#             */
/*   Updated: 2023/12/03 18:24:01 by mbousbaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_type_id(char	*type_id, int count)
{
	int		ret;
	char	**tmp;

	ret = count;
	tmp = ft_split(type_id, ' ');
	if (ft_strncmp(tmp[0], "NO", 3) == 0
		|| ft_strncmp(tmp[0], "SO", 3) == 0
		||ft_strncmp(tmp[0], "WE", 3) == 0
		|| ft_strncmp(tmp[0], "EA", 3) == 0)
	{
		check_texture_file(tmp);
		ret += 1;
	}
	else if ((!ft_strncmp(tmp[0], "F", 2) || !ft_strncmp(tmp[0], "C", 2))
		&& check_color_formula(tmp))
		ret += 1;
	else
		ret = 0;
	free_2d_array(tmp);
	return (ret);
}

void	init_type_ids(t_map *map, char *type)
{
	char	**tmp;

	tmp = ft_split(type, ' ');
	if (tmp == NULL)
		return ;
	if (tmp[1] == NULL)
	{
		free_2d_array(tmp);
		error_("All type identifers need to have a value !", NULL);
	}
	if (tmp[0][0] == 'F' && tmp[0][1] == '\0')
		map->F = ft_strdup(tmp[1]);
	else if (tmp[0][0] == 'C' && tmp[0][1] == '\0')
		map->C = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "NO", 2) == 0)
		map->NO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "SO", 2) == 0)
		map->SO = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "WE", 2) == 0)
		map->WE = ft_strdup(tmp[1]);
	else if (ft_strncmp(tmp[0], "EA", 2) == 0)
		map->EA = ft_strdup(tmp[1]);
	free_2d_array(tmp);
}

/// @brief process map and initialize the type ids in map struct
/// @param map pointer to t_map struct
/// @return processed type ids count 
int	process_type_ids(t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0; // representing how many type id parocessed
	while (map->map_s[i] && i < 6)
	{
		//removing spaces & tabs from the beginning of type ids
		trim_type_ids(map);
		// Checking the first char of type id && if we reached all type ids
		if (!ft_isalpha(map->map_s[i][0]) && count <= 6) 
			break ;
		// check content of line 
		count = check_type_id(map->map_s[i], count);
		// break if this line doesn't contain a type id
		if (count == 0)
			break ;
		//initialize type id in the map struct
		init_type_ids(map, map->map_s[i]);
		i++;
	}
	// if something happened and we didn't get all type ids
	if (count != 6)
		error_("Check if all the 6 type identifiers are in a correct format !", NULL);
	return (count);
}

/// @brief Read map file and return a pointer to t_map
/// @param file pointer to map file path
/// @return a poiter to t_map struct
t_map	*read_map(char *file)
{
	int		fd;
	int		r_count;
	char	buff[BUFSIZ];
	t_map	*ret;

	ret = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 3)
		error_(NULL, file);
	r_count = read(fd, buff, BUFSIZ);
	if (r_count <= 0)
		error_(NULL, NULL);
	buff[r_count] = '\0';
	ret = (t_map *) malloc(sizeof(t_map));
	if (!ret)
		return (NULL);
	ret->map_fd = fd;
	ret->map_s = ft_split(buff, '\n');
	ret->map_s_copy = ft_split(buff, '\n');
	ret->init_player_x = -1;
	ret->init_player_y = -1;
	return (ret);
}

void	adapt_lines(char **map)
{
	int		curr_l_len;
	int		n_len;
	int		i, j;
	char	*tmp;

	i = 6;
	while (map[i])
	{
		curr_l_len = ft_strlen(map[i]);
		if (map[i + 1])
		{
			n_len = ft_strlen(map[i + 1]);
			if (curr_l_len > n_len)
			{
				
				tmp = ft_strdup(map[i + 1]);
				free(map[i + 1]);
				map[i + 1] = malloc(sizeof(char) * (curr_l_len + 1));
				ft_memset(map[i + 1], 'V', curr_l_len);
				j = -1;
				while (tmp[++j])
				{
					map[i + 1][j] = tmp[j];
				}
			}
		}
		i++;
	}
}

void	fill_map(char **map)
{
	int	i;
	int	j;

	i = 5;
	while (map[++i])
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
			j++;
		while (map[i][j] && map[i][j] == '1')
			j++;
		if (map[i][j] == '0')
		{
			while (map[i][j])
			{
				if ((map[i][j] == '0' || ft_strchr("NSWE", map[i][j]))
					&& map[i][j + 1])
				{
					if ((map[i][j - 1] && map[i][j - 1] == '1')
						&& (map[i - 1][j] && map[i - 1][j] == '1')
						&& (map[i + 1] && map[i + 1][j] != 'V')
						&& (map[i] [j + 1] && map[i][j + 1] != 'V'))
						map[i][j] = '1';
				}
				j++;
			}
		}
	}
}

int	process_map(t_map *map)
{
	int	ret;

	ret = 0;
	if (check_map_elements(map, map->map_s, "NSEW01 	") != 1)
		return (printf("Map elements not valid\n"));
	// ret = check_top_border(map);
	// ret = check_bottom_border(map);
	// ret = check_side_borders(map);
	/// Temporary 
	adapt_lines(map->map_s_copy);
	fill_map(map->map_s_copy);
	ret  = 5;
	
	while (map->map_s_copy[++ret])
		printf("%s\n", map->map_s_copy[ret]);
	ret = 6;
	while (map->map_s_copy[ret])
	{
		while (*(map->map_s_copy[ret]))
		{
			if (*(map->map_s_copy[ret]) == '0')
				error_("Map not closed :(", NULL);
			(map->map_s_copy[ret])++;
		}
		ret++;
	}
	printf("\nmap closed (y)\n");
	exit(0);
	/// ##############
	if (!ret)
		return (printf("Map not closed properly\n"));
	return (ret);
}

