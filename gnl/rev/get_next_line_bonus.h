/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyolee <kyolee@student.42.seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:14:46 by kyolee            #+#    #+#             */
/*   Updated: 2022/01/09 20:56:59 by kyolee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# include <sys/types.h>
# define FD_BUF_MAX	32

typedef struct s_fd
{
	int		fd;
	char	*prev;
}	t_fd_arr;

typedef struct s_read
{
	t_fd_arr	*parr;
	size_t		arr_cur_len;
	size_t		arr_max;
}	t_read;

char	*ft_strjoin(
			char const *s1,
			char const *s2,
			size_t s1_len,
			size_t s2_len
			);
int		expand_buff(
			char **buff,
			size_t read_cnt,
			size_t cur_len,
			size_t plus_len
			);
ssize_t	repeat_read(
			int fd,
			char **buff,
			size_t buff_len,
			size_t *total_read
			);
char	*ft_read_line(
			int fd,
			char **buff,
			t_read *pread,
			size_t buff_max_len
			);
char	*ft_strdup(const char *s, size_t size);
int		is_found_enter(char *s, size_t size);
int		init_read_info_arr(t_read *pread_info);
char	*make_line(char **cur);
int		save_read_info_arr(t_read *pinfo, int fd, char **prev, char *line);
char	*get_next_line(int fd);
#endif
