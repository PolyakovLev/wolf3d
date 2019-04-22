# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/04 19:55:47 by ramory-l          #+#    #+#              #
#    Updated: 2019/02/13 17:11:35 by ramory-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET = wolf3d

SRCS = $(wildcard srcs/*.c) main.c
OBJ = $(SRCS:.c=.o)

HEADERS = -I includes -I libft/includes

SDL2 = -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	   -I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers \
	   -I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	   -I ~/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers \

FRAMES = -F ~/Library/Frameworks/ -framework SDL2 \
		-F ~/Library/Frameworks/ -framework SDL2_image \
		-F ~/Library/Frameworks/ -framework SDL2_ttf \
		-F ~/Library/Frameworks/ -framework SDL2_mixer

LDFLAGS = -Llibft -lft

SFLAGS = -Wall -Wextra -Werror

all: $(TARGET)

$(TARGET): $(OBJ) libft
	gcc -o $@ $(OBJ) $(LDFLAGS) $(FRAMES)

%.o: %.c
	gcc -c $< -o $@ $(HEADERS) $(SFLAGS) $(SDL2) -F ~/Library/Frameworks

.PHONY: libft
libft:
	make -C libft

.PHONY: clean
clean:
	rm -Rf *.o srcs/*.o
	make clean -C libft

.PHONY: fclean
fclean: clean
	rm -Rf wolf3d
	make fclean -C libft

re: fclean all