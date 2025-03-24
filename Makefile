EXECUTABLE	=	retardio
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iinclude

#
#	COLORS
#
RESET = \033[0m
GREEN = \033[32;49m
RED = \033[31;49m
BLUE = \033[34;49m

#
# 	SRCS
#
SRC_DIR		=	src
SRCS	=	$(wildcard $(SRC_DIR)/*.c)
OBJS	=	$(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


all: comp

comp: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)
	@printf "$(GREEN)[$(EXECUTABLE)]\tExecutable compiled✨$(RESET)\n"

debug: $(OBJS)
	@$(CC) $(CFLAGS) -g3 $(OBJS) -o $(EXECUTABLE)
	@printf "$(BLUE)[$(EXECUTABLE)]\tDebug Executable compiled✨$(RESET)\n"

clean:
	@files_deleted=0; \
	for obj in $(OBJS); do \
		if [ -f "$$obj" ]; then \
			rm -f "$$obj"; \
			files_deleted=1; \
		fi; \
	done; \
	if [ $$files_deleted -eq 1 ]; then \
		printf "$(RED)[$(EXECUTABLE)]\tBinary files deleted🗑️$(RESET)\n"; \
	fi

fclean:	clean
	@files_deleted=0; \
	if [ -f "$(EXECUTABLE)" ]; then \
		rm -f $(EXECUTABLE); \
		files_deleted=1; \
	fi; \
	if [ $$files_deleted -eq 1 ]; then \
		printf "$(RED)[$(EXECUTABLE)]\tExecutable cleaned🗑️$(RESET)\n"; \
	fi
	@printf "\n"

re:		fclean all

.PHONY: all clean fclean re