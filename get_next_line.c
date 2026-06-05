/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstuhrin <jstuhrin@student.codam.nl>          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/18 15:09:04 by jstuhrin       #+#    #+#                */
/*   Updated: 2024/11/18 15:09:06 by jstuhrin       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static void	set_data_struct_zero(t_buffer_data *data, int fd)
{
	size_t	i;

	data->fd = fd;
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
	static t_buffer_data	data = {0};
	char					*line;
	char					*result;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	data.fd = fd;
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	result = loop(&data, line, BUFFER_SIZE, 0);
	if (result == NULL)
		return (set_data_struct_zero(&data, fd), NULL);
	return (resize_line(result));
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <limits.h>
// #include <string.h>

// // int	main(void)
// // {
// // 	int		fd;
// // 	char	*line;

// // 	fd = open("../../example.txt", O_RDONLY);
// // 	if (fd < 0)
// // 	{
// // 		perror("open");
// // 		return (1);
// // 	}
// // 	printf("printing lines:\n");
// // 	line = get_next_line(fd);
// // 	while (line != NULL)
// // 	{
// // 		printf("%s\n", line);
// // 		free(line);
// // 		line = get_next_line(fd);
// // 	}
// // 	close(fd);
// // 	return (0);
// // }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	printf("printing lines from invalid fd:\n");
// 	line = get_next_line(1026);
// 	printf("%s", line);
// 	free(line);
// 	fd = open("../../one_char.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from one_char.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("../../example1.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from example1.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("../../empty_file.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from empty_file.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("../../empty_lines.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from empty_lines.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("../../example1.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from example1.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("../../one_empty_line.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	printf("printing lines from one_empty_line.txt:\n");
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
