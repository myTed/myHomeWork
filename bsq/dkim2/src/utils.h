/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:04:46 by dkim2             #+#    #+#             */
/*   Updated: 2021/10/27 21:13:46 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_mark
{
	int		rows;
	int		cols;
	char	mark[3];
}	t_mark;

int		is_digit(char c);

int		is_printable(char c);

int		check_overlap(char c1, char c2, char c3);

int		is_mark(char c, t_mark M);

char	*ft_append(char *src, char c);

#endif
