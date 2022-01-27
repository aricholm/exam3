/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:07:04 by aricholm          #+#    #+#             */
/*   Updated: 2022/01/27 11:20:14 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

void	print_table(t_table *table)
{
	int	i;
	int	j;

	j = 0;
	while (j < table->height)
	{
		i = 0;
		while (i < table->width)
			printf("%c", table->map[i++][j]);
		printf("\n");
		j++;
	}
}

int	init_table(t_table *table)
{
	int	i;
	int	j;

	if (table->width > 300 || table->height > 300 || table->width < 1 || table->height < 1)
		return (-1);
	table->map = malloc(sizeof(char *) * table->width);
	if (!table->map)
		return (-1);
	i = 0;
	while (i < table->width)
	{
		table->map[i] = malloc(table->height);
		if (!table->map[i])
		{
			i--;
			while (i >= 0)
				free(table->map[i--]);
			free(table->map);
			table->map = NULL;
			return (-1);
		}
		j = 0;
		while (j < table->height)
			table->map[i][j++] = table->ch;
		i++;
	}
	return (0);
}

void	draw_point(t_table *table, int x, int y, char ch)
{
	if (x >= 0 && y >= 0 && x < table->width && y < table->height)
		table->map[x][y] = ch;
}

float	distance(float x, float y, float a, float b)
{
	return (sqrtf((x - a) * (x - a) + (y - b) * (y - b)));
}

int	draw_circle(t_table *table, t_circle circle)
{
	int		i;
	int		j;
	float	dist;

	j = 0;
	if (circle.flr <= 0 || (circle.type != 'c' && circle.type != 'C'))
		return (-1);
	while (j < table->height)
	{
		i = 0;
		while (i < table->width)
		{
			dist = distance((float)i, (float)j, circle.flx, circle.fly);
			if (circle.type == 'c')
			{
				if ((dist - circle.flr) > -1 && (dist - circle.flr) <= 0)
					draw_point(table, i, j, circle.ch);
			}
			if (circle.type == 'C')
			{
				if (dist - circle.flr <= 0)
					draw_point(table, i, j, circle.ch);
			}
			i++;
		}
		j++;
	}
	return (0);
}

int	file_error(FILE *f, t_table *table)
{
	int	i;

	write(1, "Error: Operation file corrupted\n", 32);
	if (f)
		fclose(f);
	if (table->map)
	{
		i = 0;
//		while (i < table->height)
	//		free (table->map[i++]);
//		free (table->map);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	FILE		*f;
	t_table		table;
	t_circle	circle;
	int			flag;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	f = fopen(argv[1], "r");
	table.map = NULL;
	if (!f)
		return (file_error(f, &table));
	if (fscanf(f, "%d %d %c\n", &table.width, &table.height, &table.ch) != 3)
		return (file_error(f, &table));
	if (init_table(&table))
		return (file_error(f, &table));
	flag = 1;
	while (1)
	{
		flag = fscanf(f, "%c %f %f %f %c\n", &circle.type, &circle.flx, &circle.fly, &circle.flr, &circle.ch);
		if (!flag || flag == EOF)
			break ;
		if (flag != 5 || draw_circle(&table, circle))
			return (file_error(f, &table));
		if (flag == EOF)
			break ;
	}
	print_table(&table);
	fclose(f);
	return (0);
}
