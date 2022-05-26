/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:21:12 by kyolee            #+#    #+#             */
/*   Updated: 2022/05/26 17:38:30 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_color
{
	unsigned int	blue:8;
	unsigned int	green:8;
	unsigned int	red:8;
	unsigned int	padd:8;
} t_color;

typedef struct s_cordinate
{
	int	x;
	int	y;
	int	z;
	t_color color;
} t_cordinate;

int	ft_atoi_base(char *str, char *base);
