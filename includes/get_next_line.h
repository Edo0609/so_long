/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:49:31 by epenaloz          #+#    #+#             */
/*   Updated: 2023/11/08 16:14:12 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2000
# endif

char	*get_next_line(int fd);
char	*find_line(int fd, char *storage);
char	*line_get(char *storage);
char	*update_storage(char *storage);

size_t	ft_strlen_gnl(char *s);
char	*ft_strdup_gnl(char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr_gnl(char	*s, char c);
char	*ft_free(char *ptr);
#endif
