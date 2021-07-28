NAME_1	=	cont_stl
NAME_2	=	cont_ft
RND		:=	$(shell echo $$RANDOM)
SRCS	=	my_main.cpp
CF_FT	=	-Wall -Wextra -Werror -std=c++98 -g
CF_STL	=	$(CF_FT) -D USE_STL
CC		=	clang++

all		:	ft

stl		:
	@$(CC) $(CF_STL) -o $(NAME_1) $(SRCS)
ft		:
	@$(CC) $(CF_FT) -o $(NAME_2) $(SRCS)

test	:
	./$(NAME_1) $(RND)


fclean	:
	rm -rf $(NAME_1) $(NAME_2)

re		: fclean all

.phony: stl ft all fclean re test
