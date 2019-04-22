/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 18:01:28 by ramory-l          #+#    #+#             */
/*   Updated: 2019/02/13 15:17:38 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		**ft_make_array(int columnsz, int **array, char *all_lines)
{
	int		i;
	int		j;
	int		k;
	char	**splited_lines;

	i = 0;
	j = 0;
	k = 0;
	splited_lines = ft_strsplit(all_lines, ' ');
	while (splited_lines[k])
	{
		if (j == columnsz)
		{
			j = 0;
			i++;
		}
		array[i][j] = ft_atoi(splited_lines[k]);
		k++;
		j++;
	}
	free(all_lines);
	return (array);
}

int		**ft_malloc_array(int linesz, int columnsz, char *all_lines)
{
	int i;
	int **array;

	i = 0;
	array = (int **)malloc(sizeof(int *) * linesz);
	while (i < linesz)
	{
		array[i] = (int *)malloc(sizeof(int) * columnsz);
		i++;
	}
	return (ft_make_array(columnsz, array, all_lines));
}

char	*cut_line(char **splited_line, int columnsz)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strnew(1);
	while (i < columnsz && splited_line[i])
	{
		line = ft_strjoin(line, splited_line[i]);
		line = ft_strjoin(line, " ");
		i++;
	}
	return (line);
}

char	*check_line(char *line, int columnsz)
{
	int		i;
	char	**splited_line;

	i = 0;
	splited_line = ft_strsplit(line, ' ');
	while (splited_line[i])
		i++;
	if (i > columnsz)
		return (cut_line(splited_line, columnsz));
	else if (i < columnsz)
		return (NULL);
	else
		return (line);
}

int		**ft_create_map(char *map, int *size)
{
	int		fd;
	char	*line[2];
	char	**splited_line;

	line[1] = ft_strnew(1);
	ft_bzero(size, sizeof(size));
	if ((fd = open(map, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line[0]))
	{
		if (size[0] > 0 && !(line[0] = check_line(line[0], size[1])))
			return (NULL);
		if (size[0] == 0)
		{
			splited_line = ft_strsplit(line[0], ' ');
			while (splited_line[size[1]])
				size[1]++;
		}
		line[1] = ft_strjoin(line[1], line[0]);
		line[1] = ft_strjoin(line[1], " ");
		size[0]++;
	}
	if (close(fd) == -1)
		return (NULL);
	return (ft_malloc_array(size[0], size[1], line[1]));
}
