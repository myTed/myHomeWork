/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:14:46 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/12 00:42:18 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <sys/types.h>

typedef struct s_list
{
	int				fd;
	char			*left;
	size_t			left_len;
	struct s_list	*next;
}	t_list;

int		is_found_chr(const char *s, int c, size_t len);
int		read_line(int fd, char *buff, char **pstr);
int		add_prev_line(int fd, char **pline, t_list **pplist);
int		save_line(int fd, char **pline, t_list **pplist);
t_list	*ft_lstnew(int fd, void *str, size_t str_len);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdel(t_list **lst, int fd);
size_t	ft_strlen(void *src);
char	*ft_strjoin(
			char const *s1,
			char const *s2,
			size_t s1_len,
			size_t s2_len
			);
char	*get_next_line(int fd);
#endif
