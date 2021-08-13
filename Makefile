NAME_1	=	cont_stl
NAME_2	=	cont_ft
RND		:=	$(shell echo $$RANDOM)
SRCS	=	main.cpp
CF_FT	=	-Wall -Wextra -Werror -std=c++98 -g
CF_STL	=	$(CF_FT) -D USE_STL
CC		=	clang++

all		:	ft

stl		:
	@$(CC) $(CF_STL) -o $(NAME_1) $(SRCS)
ft		:
	@$(CC) $(CF_FT) -o $(NAME_2) $(SRCS)

fclean	:
	rm -rf $(NAME_1) $(NAME_2)

re		: fclean all

test	:
	./$(NAME_1) $(RND)

diff	:
	make re
	./$(NAME_2) > logs/ftLog;
	make re
	./$(NAME_2) > logs/stdLog;
	diff ./logs/ftLog ./logs/stdLog

.phony: stl ft all fclean re test
