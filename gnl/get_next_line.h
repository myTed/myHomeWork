/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:14:46 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/15 23:24:32 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	size_t			len;
	struct s_list	*next;
}	t_list;

typedef struct s_line_info
{
	size_t	total_cur_len;
	size_t	after_new_len;
	char	*after_new_str;
}	t_line_info;

t_list	*ft_lstnew(void *content, size_t len);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		get_pos_newline_in_buffer(
			char *buff,
			size_t size,
			int *is_found_newline
			);
#endif
