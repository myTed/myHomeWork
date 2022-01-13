/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:14:46 by kyolee            #+#    #+#             */
/*   Updated: 2021/12/30 13:07:05 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <sys/types.h>
# define MEM_ALLOC_ERROR	-1
# define READ_ERROR			-2
# define NON_ERROR			0

typedef struct s_list
{
	void			*content;
	size_t			len;
	size_t			is_newline;
	size_t			ready_to_free;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content, size_t len, int is_newline);
int		ft_lstadd_back(t_list **lst, t_list *new);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		is_found_newline(char *buff, ssize_t size);
void	delete_list(t_list **pplist, int error);
int		concat_line(t_list **pplist, char **pnew_line, size_t new_len);
int		make_newline(t_list **pplist, char **pnew_line, size_t new_len);
int		make_list(int fd, t_list **plist, char *buff);
int		add_list(t_list	**pplist, char *buff, ssize_t size);
char	*get_next_line(int fd);
#endif
