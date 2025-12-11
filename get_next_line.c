/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 02:18:26 by rjuarez-          #+#    #+#             */
/*   Updated: 2025/12/03 02:34:23 by rjuarez-         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
 *
 * @dev
 * <desarrollo de la funcion>
 * 
 * */
/*unsigned char	*ft_get_line(unsigned char **ptr)
{
	unsigned char	*line;
	size_t			found;
	size_t			aux_len;
	int				i;

	if (!ptr || !*ptr)
		return (NULL);
	found = ft_nstrchr((char *)*ptr, '\n');
	line = ft_calloc(found + 2, sizeof(unsigned char));
	if (line == NULL)
		return (NULL);
	i = -1;
	while (++i <= (int) found)
		line[i] = (*ptr)[i];
	line[i] = '\0';
	aux_len = ft_strlen((char *)*ptr);
	i = -1;
	while ((int)(found + 1 + ++i) < (int) aux_len)
		(*ptr)[i] = (*ptr)[found + 1 + i];
	(*ptr)[i] = '\0';
	*ptr = ft_recalloc(*ptr, i + 1);
	if (*ptr == NULL)
		return (NULL);
	return (line);
}*/
unsigned char	*ft_get_line(unsigned char **des, unsigned char **line,
						ssize_t size, ssize_t byte_read)
{
	int				i;
	long long int	len_line;

	*line = ft_recalloc(*line, ft_strlen((char *)*line) + size + 1);
	if (*line == NULL)
	{
		free(des);
		free(line);
		return (NULL);
	}
	len_line = ft_strlen((char *)*line);
	i = -1;
	while (++i < (int)size)
		(*line)[len_line + i] = (*des)[i];
	(*line)[len_line + i] = '\0';
	if (size < byte_read)
	{
		i = -1;
		while ((++i + size) < byte_read)
			(*des)[i] = (*des)[size + i];
		(*des)[i] = '\0';
	}
	(*des) = ft_recalloc((*des), (byte_read - size + 1));
	return ((*line));
}

void	*ft_swaping(void **ptr1, void **ptr2)
{
	unsigned char	*aux;

	if ((ptr1 == NULL) && (ptr2 == NULL))
		return (0);
	else if (ptr1 == NULL)
	{
		*ptr1 = *ptr2;
		*ptr2 = NULL;
	}
	else if (ptr2 == NULL)
	{
		*ptr2 = *ptr1;
		*ptr1 = NULL;
	}
	else
	{
		aux = (unsigned char)(*ptr1);
		*ptr1 = *ptr2;
		*ptr2 = (void *) aux;
	}
	return (1);
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
 *
 * @dev
 * <desarrollo de la funcion>
 * */
/*int	ft_read_concat(unsigned char **des, int fd)
{
	unsigned char	*buffer;
	size_t			buffer_len;
	size_t			des_len;
	size_t			i;

	if (fd < 0)
		return (-1);
	if (*des == NULL)
		*des = (unsigned char *) ft_calloc(1, 1);
	buffer_len = (size_t) read(fd, buffer, BUFFER_SIZE);
	if (buffer_len <= 0)
		return (buffer_len);
	buffer[buffer_len] = '\0';
	des_len = ft_strlen((char *) *des);
	*des = ft_recalloc(*des, (des_len + (size_t)buffer_len + 2));
	if (*des == NULL)
		return (-1);
	i = -1;
	while (++i <= buffer_len)
		(*des)[des_len + i] = buffer[i];
	(*des)[des_len + buffer_len] = '\0';
	return ((int)des_len + (int)buffer_len + 1);
}*/

unsigned char	*ft_read_concat(unsigned char **des, unsigned char **line,
					int fd)
{
	unsigned long int	bytes_read;
	int					i;

	if (fd < 0)
		return (-1);
	if (*des == NULL)
		*des = (unsigned char *) ft_calloc(BUFFER_SIZE + 1,
				sizeof(unsigned char));
	ft_swaping ((void *)(*des), (void *)(*line));
	bytes_read = 1;
	while ((ft_nstrchr((char *)des, '\n') < 0) || (bytes_read <= 0))
	{
		bytes_read = (unsigned long int) read(fd, (*des), BUFFER_SIZE);
		(*des)[bytes_read] = '\0';
		if (bytes_read != 0)
			break ;
		*line = ft_get_line((*des), (*line), bytes_read, bytes_read);
	}
	if ((ft_nstrchr((char *)des, '\n') >= 0) && ((*line) != NULL))
		*line = ft_get_line((*des), (*line), ft_nstrchr((char *)des, '\n'),
				bytes_read);
	else if ((*line) != NULL)
		*line = ft_get_line((*des), (*line), bytes_read, bytes_read);
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
 *
 * @dev
 *      If the buffer still contains characters, it is returned as the last
 *      line. Otherwise, the memory is freed and NULL is returned. In both
 *      cases, the pointer *rest is set to NULL to avoid dangling references.
 * */
unsigned char	*ft_return_last(unsigned char **rest)
{
	unsigned char	*line;

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
 * 
 * @cond
 *		- the file must be open
 * @dev
 * <desarrollo de la funcion>
 * 
 * */
char	*get_next_line(int fd)
{
	static unsigned char	*rest;
	unsigned char			*line;
	ssize_t					rest_len;

	if ((fd < 0) || (BUFFER_SIZE < 0) || (read(fd, 0, 0) < 0))
	{
		if (rest != NULL)
		{
			free(rest);
			rest = NULL;
		}
		return (NULL);
	}
	if (rest == NULL)
		rest = ft_calloc((BUFFER_SIZE + 1), sizeof(unsigned char));
	rest_len = 1;
	while ((rest_len > 0) && (ft_nstrchr((char *)rest, '\n') < 0))
		rest_len = ft_read_concat(&rest, &line, fd);
	if (rest_len < 0)
		return (NULL);
	if (ft_nstrchr((char *)rest, '\n') >= 0)
		line = ft_get_line(&rest);
	else
		line = ft_return_last (&rest);
	return ((char *)line);
}
