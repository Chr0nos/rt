#!/bin/sh
clang perlin_test.c -I ~/.brew/include -I libdraw/headers -I libft -L libdraw -ldraw -L libft -lft -L ~/.brew/lib/ -fsanitize=address -o perlin
