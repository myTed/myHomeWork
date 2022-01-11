#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_list
{
	int				fd;
	char			*left;
	size_t			left_len;
	struct s_list	*next;
} t_list;


t_list  *ft_lstnew(int fd, void *str, size_t str_len)
{
	t_list  *new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->left = str;
	new->left_len = str_len;
	new->next = NULL;
	return (new);
}

void    ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list  *end;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		end = *lst;
		while (end->next != NULL)
			end = end->next;
		end->next = new;
	}
}


void    *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t  idx;

	idx = 0;
	while (idx < n)
	{
		if ((dest == 0) && (src == 0))
		return (0);
		*((unsigned char *)dest + idx) = *((const unsigned char *)src + idx);
		idx++;
	}
	return (dest);
}


size_t	ft_strlen(void *src)
{
	size_t	idx;
	idx = 0;
	if (src == 0)
		return (0);
	while (((char*)src)[idx] != 0)
		idx++;
	return (idx);
}

char    *ft_strjoin(char const *s1, char const *s2, size_t s1_len, size_t s2_len)
{
	char    *str;

	if ((s1 == 0 && s2 == 0))
			return (NULL);
	if (s1_len == 0 && s2_len == 0)
			return (NULL);
	str = NULL;
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str != NULL)
	{
		if (s1)
			ft_memcpy(str, s1, s1_len);
		if (s2)
			ft_memcpy(str + s1_len, s2, s2_len);
		str[s1_len + s2_len] = 0;
	}
	return (str);
}


int	is_found_chr(const char *s, int c, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (s[idx] == (char)c)
			return (1);
		idx++;
	}
	return (0);
}



int	read_line(int fd, char *buff, char **pstr)
{
	ssize_t	read_cnt;
	ssize_t	tmp_cnt;
	char	*tmp;
	
	tmp_cnt = 0;
	while (1)
	{
		read_cnt = read(fd, buff, BUFFER_SIZE);
		if (read_cnt == 0)
			break;
		if (read_cnt < 0)
			return (-1);
		tmp = ft_strjoin(*pstr, buff, tmp_cnt, read_cnt);
		if (tmp == 0)
			return (-1);
		free(*pstr);
		*pstr = tmp;
		if (is_found_chr(*pstr, '\n', tmp_cnt + read_cnt))
			break;
		tmp_cnt += read_cnt;
	}
	return (0);
}

void	ft_lstdel(t_list **lst, int	fd)
{
	t_list	*cur;
	t_list	*prev;

	cur = *lst;
	prev = cur;
	if (lst == 0)
		return ;
	while (cur != 0)
	{
		if (cur->fd == fd)
		{	
			if (prev == cur)
				*lst = cur->next;
			else
				prev->next = cur->next;
			free(cur->left);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	add_prev_line(int fd, char **pline, t_list **pplist)
{
	char	*tmp;
	size_t	line_len;
	t_list	*plist;

	if (*pline != 0)
		line_len = ft_strlen(*pline);
	else
		line_len = 0;
	plist = *pplist;
	while (plist != NULL)
	{
		if (plist->fd == fd)
		{
			tmp = ft_strjoin(plist->left, *pline, plist->left_len, line_len);
			if (tmp == 0)
				return (-1);
			ft_lstdel(pplist, fd);
			free(*pline);
			*pline = tmp;
			break;
		}
		plist = plist->next;
	}
	return (0);
}

int	save_line(int fd, char **pline, t_list **pplist)
{
	size_t	idx;
	size_t	line_len;
	size_t	enter_pos;
	char	*tmp;
	t_list	*new_lst;

	if (*pline == 0)
		return (0);
	line_len = ft_strlen(*pline);
	if (is_found_chr(*pline, '\n', line_len -1) == 0)
		return (0);
	idx = 0;
	while ((*pline)[idx] != 0)
	{
		if ((*pline)[idx] == '\n')
			break;
		idx++;
	}
	enter_pos = idx;
	tmp = ft_strjoin(&(*pline)[enter_pos + 1], 0, line_len - enter_pos - 1, 0);
	if (tmp == 0)
		return (-1);
	new_lst = ft_lstnew(fd, tmp, line_len - enter_pos - 1);
	if (new_lst == 0)
		return (-1);
	ft_lstadd_back(pplist, new_lst);
	(*pline)[enter_pos + 1] = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	static t_list	*plist;

	if (fd < 0)
		return (0);
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (buff == 0)
		return (0);
	line = 0;
	if (read_line(fd, buff, &line) < 0)
	{
		free(buff);
		return (0);
	}
	if (add_prev_line(fd, &line, &plist) < 0)
	{
		free(buff);
		free(line);
		return (0);
	}
	if (save_line(fd, &line, &plist) < 0)
	{
		free(buff);
		free(line);
	}
	free(buff);
	return (line);
	//2. 기존에 읽은 것과 합치기 (searching + 합치기)
	//3. 합친 것 나누기
	//4. 나눌것이 있으면 저장. 아니면 삭제
}
/*
int	main(void)
{
	int		fd;
	char	*str;
	int		idx;
	
	fd = open("aaa.txt", O_RDONLY);
	
	fd = 0;
	while ((str = get_next_line(fd)) != 0)
	{
		printf("%s", str);
		fflush(stdout);
		free(str);
		idx++;
	}
	
	if (fd)
		close(fd);
	
	return (0);
}
*/
/*
int	main(void)
{
	int		fd[3];
	char	*str;
	int		idx;

	fd[0] = open("aaa.txt", O_RDONLY);
	if (fd[0] < 0)
		return (-1);
	fd[1] = open("bbb.txt", O_RDONLY);
	if (fd[1] < 0)
		return (-1);
	fd[2] = open("ccc.txt", O_RDONLY);
	if (fd[2] < 0)
		return (-1);
	idx = 0;
	while (1)
	{
		str = get_next_line(fd[idx % 3]);
		printf("%s", str);
		fflush(stdout);
		free(str);
		idx++;
	}
	
	if (fd)
		close(fd);
	
	return (0);
}
*/
