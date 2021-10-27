#ifndef MAP_H
# define MAP_H

int check_first_line(int fd, Mark *M);

int check_each_line(char *str, Mark M);

int check_whole_line(int fd, Mark M);

int check_map_file(int fd, Mark *M);

char **get_map(char *filename, Mark M);

#endif