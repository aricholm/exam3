/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:27:31 by aricholm          #+#    #+#             */
/*   Updated: 2022/01/26 15:45:17 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_table{
	int		width;
	int		height;
	char	ch;
	char	**map;
}	t_table;

typedef struct s_circle{
	char	type;
	float	flx;
	float	fly;
	float	flr;
	char	ch;
}	t_circle;
#endif