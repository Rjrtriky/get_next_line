/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonnus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-14 12:58:57 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-12-14 12:58:57 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*FT_GET_LINE
 * @def	It obtains a line ending in '\n' and leaves the rest in the string
 *		received as a parameter.
 *
 * @param
 *		{pointer to unsigned char} **ptr - Pointer to string with line and rest
 *
 * @returns
 *		OK - Returns the line up to '\n' and the rest in the parameter. 
 *		KO - NULL
 * */
unsigned char	*ft_get_line(unsigned char **rest)
{
	unsigned char	*line;
	size_t			found;
	size_t			aux_len;
	int				i;

	if ((rest == NULL) || (*rest == NULL))
		return (NULL);
	found = ft_nstrchr((char *)*rest, '\n');
	line = ft_calloc(found + 2, sizeof(unsigned char));
	if (line == NULL)
		return (NULL);
	i = -1;
	while (++i <= (int) found)
		line[i] = (*rest)[i];
	line[i] = '\0';
	aux_len = ft_strlen((char *)*rest);
	i = -1;
	while ((int)(found + 1 + ++i) < (int) aux_len)
		(*rest)[i] = (*rest)[found + 1 + i];
	(*rest)[i] = '\0';
	*rest = ft_recalloc(*rest, i + 1);
	if (*rest == NULL)
		return (NULL);
	return (line);
}

/*FT_RETURN_LAST
 * @def Handles the final return of the remaining buffer when no newline
 *      character is found in the string.
 *
 * @param
 *      {pointer to unsigned char} **rest - double pointer to the buffer
 *      that stores the remaining content.
 *
 * @returns
 *      OK - Returns the last line stored in *rest if it is not empty.
 *      KO - Returns NULL if *rest is empty, freeing the memory.
 * */
unsigned char	*ft_return_last(unsigned char **rest)
{
	unsigned char	*line;

	if (rest == NULL || *rest == NULL)
		return (NULL);
	if (**rest != '\0')
		line = (*rest);
	else
	{
		free(*rest);
		line = NULL;
	}
	*rest = NULL;
	return (line);
}

/*FT_READ_CONCAT
 * @def	Read from the file and concatenate what you read to an unsigned char
 *		pointer.
 *
 * @param
 *		{pointer to unsigned char} *des - 
 *		{integer number} fd - identifier descriptor of file to read.
 *
 * @returns
 *		OK - Returns the total number of characters and in the received
 *			parameter, the received value and the buffer read from the file.
 *		KO - -1
 * */
int	ft_read_concat(unsigned char **rest, int fd)
{
	int	buffer_len;
	int	rest_len;

	if (fd < 0)
		return (-1);
	if (*rest == NULL)
		*rest = (unsigned char *) ft_calloc(1, 1);
	rest_len = ft_strlen((char *) *rest);
	*rest = ft_recalloc(*rest, rest_len + BUFFER_SIZE + 1);
	if (*rest == NULL)
		return (-1);
	buffer_len = (int) read(fd, (*rest) + rest_len, BUFFER_SIZE);
	if (buffer_len == 0)
		return (buffer_len);
	else if (buffer_len < 0)
	{
		free(*rest);
		*rest = NULL;
		return (-1);
	}
	(*rest)[rest_len + buffer_len] = '\0';
	return ((int)rest_len + (int)buffer_len + 1);
}

/*GET_NEXT_LINE
 * @def  Calling your `get_next_line` function repeatedly (for example, using a
 *	loop) will allow you to read the contents of the file pointed to by the
 *	file descriptor, line by line, to the end.
 *	- Your function should return the line that was just read.
 *	- If there is nothing more to read or if an error has occurred, it should
 *	return NULL.
 *	- Make sure your function behaves correctly when reading from a file and when
 *	reading from stdin.
 *	- Note that the returned line must end with `\n`, unless the end of the file
 *	has been reached and it does not end with `\n`.
 *
 * @param
 *		{integer number} fd - identifier descriptor of file to read.
 * 
 * @returns {string}
 *		OK - the line read up to '\n'
 *		KO - In case of failure or if the reading ends: NULL
 * */
char	*get_next_line_bonus(int fd)
{
	static unsigned char	*rest[1024];
	unsigned char			*line;
	ssize_t					rest_len;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
	{
		if (rest[fd] != NULL)
		{
			free(rest[fd]);
			rest[fd] = NULL;
		}
		return (NULL);
	}
	if (rest[fd] == NULL)
		rest[fd] = ft_calloc(1, 1);
	rest_len = 1;
	while ((rest_len > 0) && (ft_nstrchr((char *)rest[fd], '\n') < 0))
		rest_len = ft_read_concat(&rest[fd], fd);
	if (rest_len < 0 || rest[fd] == NULL)
		return (NULL);
	if (ft_nstrchr((char *)rest[fd], '\n') >= 0)
		line = ft_get_line(&rest[fd]);
	else
		line = ft_return_last (&rest[fd]);
	return ((char *)line);
}
