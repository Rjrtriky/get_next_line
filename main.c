/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjuarez- <rjuarez-@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-29 15:44:15 by rjuarez-          #+#    #+#             */
/*   Updated: 2025-11-29 15:44:15 by rjuarez-         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

void	tratar_fichero(char *filename)
{
	int fd = open(filename, O_RDONLY);
	printf("Fichero: %s\n", filename);
	if (fd == -1)
	{
		perror("Error abriendo el fichero");
		return (0);
	}

	char *line;
	int i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linea %d: %s", i++, line);
		free(line);  // Muy importante: liberar cada línea
	}
	printf("\n");
	close(fd);
}

int main(void) {

	tratar_fichero("empty");
	tratar_fichero("nl");
	tratar_fichero("41_no_nl");
	tratar_fichero("41_with_nl");
	tratar_fichero("42_no_nl");
	tratar_fichero("42_with_nl");
	tratar_fichero("43_no_nl");
	tratar_fichero("43_with_nl");
	tratar_fichero("multiple_nlx5");
	tratar_fichero("multiple_line_no_nl");
	tratar_fichero("multiple_line_with_nl");
	tratar_fichero("alternate_line_nl_no_nl");
	tratar_fichero("alternate_line_nl_with_nl");
	tratar_fichero("big_line_no_nl");
	tratar_fichero("big_line_with_nl");
	tratar_fichero("read_error.txt");

    return 0;
}