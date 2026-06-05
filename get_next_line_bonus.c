/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_bonus.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/18 20:42:55 by jstuhrin       #+#    #+#                */
/*   Updated: 2024/11/18 20:42:57 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*return_line_or_null(	t_buffer_data *data,
									size_t line_index,
									char *line)
{
	if (data->buffer_len == 0 && line_index > 0)
	{
		line[line_index] = '\0';
		return (line);
	}
	free(line);
	return (NULL);
}

static char	*return_line(t_buffer_data *data, size_t line_index, char *line)
{
	line[line_index] = '\0';
	data->buffer_index++;
	return (line);
}

static char	*loop(	t_buffer_data *data,
					char *line,
					size_t line_len,
					size_t line_index)
{
	while (1)
	{
		if (data->buffer_index >= data->buffer_len)
		{
			data->buffer_len = read(data->fd, data->buffer, BUFFER_SIZE);
			if (data->buffer_len <= 0)
				return (return_line_or_null(data, line_index, line));
			data->buffer_index = 0;
		}
		while (data->buffer_index < data->buffer_len)
		{
			if (data->buffer[data->buffer_index] == '\n')
			{
				line[line_index++] = '\n';
				return (return_line(data, line_index, line));
			}
			line[line_index++] = data->buffer[(data->buffer_index)++];
			if (line_index >= line_len)
			{
				line = realloc_line(line, &line_len);
				if (!line)
					return (NULL);
			}
		}
	}
}

static void	set_data_struct_zero(t_buffer_data *data)
{
	ssize_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		data->buffer[i++] = '\0';
	}
	data->buffer_len = 0;
	data->buffer_index = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer_data	data[1024];
	char					*line;
	char					*result;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	data[fd].fd = fd;
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	result = loop(&data[fd], line, BUFFER_SIZE, 0);
	if (result == NULL)
		return (set_data_struct_zero(&data[fd]), NULL);
	return (resize_line(result));
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// // int	main(void)
// // {
// // 	int		fd;
// // 	char	*line;

// // 	fd = open("../../empty_file.txt", O_RDONLY);
// // 	if (fd < 0)
// // 	{
// // 		perror("open");
// // 		return (1);
// // 	}
// // 	line = get_next_line(fd);
// // 	while (line != NULL)
// // 	{
// // 		printf("%s", line);
// // 		free(line);
// // 		line = get_next_line(fd);
// // 	}
// // 	close(fd);
// // 	return (0);
// // }

// int main(void)
// {
// 	int		fd_one_char;
// 	int		fd_no_new_line_char;
// 	int		fd_empty_file;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		fd10;
// 	int		fd100;
// 	//int		fd100000;
// 	int		fd_empty_lines;
// 	char	*line;
// 	fd_one_char = open("../../one_char.txt", O_RDONLY);
//     if (fd_one_char < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd_no_new_line_char = open("../../no_new_line_char.txt", O_RDONLY);
//     if (fd_no_new_line_char < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd_empty_file = open("../../empty_file.txt", O_RDONLY);
//     if (fd_empty_file < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd1 = open("../../example1.txt", O_RDONLY);
//     if (fd1 < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd2 = open("../../example2.txt", O_RDONLY);
//     if (fd2 < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd3 = open("../../example3.txt", O_RDONLY);
//     if (fd3 < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd10 = open("../../example10.txt", O_RDONLY);
//     if (fd10 < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	fd100 = open("../../example100.txt", O_RDONLY);
//     if (fd100 < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	// fd100000 = open("../../example100000.txt", O_RDONLY);
//     // if (fd100000 < 0)
// 	// {
//     //     perror("open");
//     //     return (1);
//     // }
// 	fd_empty_lines = open("../../empty_lines.txt", O_RDONLY);
//     if (fd_empty_lines < 0)
// 	{
//         perror("open");
//         return (1);
//     }
// 	line = get_next_line(fd_one_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_no_new_line_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(1023);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(1026);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_empty_file);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd1);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd2);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd3);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd10);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd100);
//     printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd100000);
//     // printf("%s\n", line);
// 	// free(line);
// 	line = get_next_line(fd_empty_lines);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_one_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_no_new_line_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(1022);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_empty_file);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd1);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd2);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd3);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd10);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd100);
//     printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd100000);
//     // printf("%s\n", line);
// 	// free(line);
// 	line = get_next_line(fd_empty_lines);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_one_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_no_new_line_char);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(1021);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd_empty_file);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd1);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd2);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd3);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd10);
//     printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd100);
//     printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd100000);
//     // printf("%s\n", line);
// 	// free(line);
// 	line = get_next_line(fd_empty_lines);
//     printf("%s", line);
// 	free(line);
// 	close(fd_no_new_line_char);
// 	close(fd_empty_file);
//     close(fd1);
// 	close(fd2);
// 	close(fd3);
//     close(fd10);
// 	close(fd100);
// 	close(fd_empty_lines);
// 	//close(fd100000);
//     return (0);
// }