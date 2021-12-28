/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:14:46 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/25 00:20:50 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <sys/types.h>

typedef struct s_endline
{
	char	*str;
	size_t	str_size;
} t_endline;

typedef struct s_linearry
{
	t_endline	*p_endline;
	size_t		endline_size;
} t_endline_arry;
/*
typedef struct s_list
{
	void			**content;
	ssize_t			cur_str_idx;
	size_t			need_to_concat_idx;
	size_t			str_cnt;
	struct s_list	*next;
}	t_list;

typedef struct s_line_info
{
	size_t	total_cur_len;
	size_t	after_new_len;
	char	*after_new_str;
}	t_line_info;
*/
/*
t_list	*ft_lstnew(void **content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);

void	*ft_memcpy(void *dest, const void *src, size_t n);

int		get_pos_newline_in_buffer(
			char *buff,
			size_t size,
			int *is_found_newline
			);
*/
char	*get_next_line(int fd);
void	ft_memcpy(void *dest, const void *src, size_t n);
#endif
