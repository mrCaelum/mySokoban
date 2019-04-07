# Colors
BLACK	=	\e[30m
RED	=	\e[31m
GREEN	=	\e[32m
YELLOW	=	\e[33m
BLUE	=	\e[34m
MAGENTA	=	\e[35m
CYAN	=	\e[36m
WHITE	=	\e[37m
DEFAULT	=	\e[0m
BOLD	=	\e[1m

# Output function
ECHO	=	echo
LIB_INDENT =	sed -E "s/^/`printf "\\e[1;35m"`>`printf "\\e[0m"`  /"

# Compile Strings
RE_COMPILE		=	$$'$(BOLD)$(GREEN)[ Recompiled the project ! ]\t$(DEFAULT)'
PROD_COMPILE		=	$$'$(BOLD)$(GREEN)[ Recompiled with PROD flags ! ]\t$(DEFAULT)'
DEBUG_COMPILE		=	$$'$(BOLD)$(GREEN)[ Recompiled with DEBUG flags ! ]\t$(DEFAULT)'
OK			=	$$'$(BOLD)$(GREEN)[ OK ]\t$(DEFAULT)'
WARNING			=	$$'$(BOLD)$(YELLOW)[ WARNING ]\t$(DEFAULT)'
ERROR			=	$$'$(BOLD)$(RED)[ ERROR ]\t$(DEFAULT)'
CLEAN			=	$$'$(BOLD)$(RED)Removing object file in [$(OBJ_DIR)]...\t$(DEFAULT)'
FCLEAN			=	$$'$(BOLD)$(RED)Removing binary in [$(BIN_DIR)]...\t$(DEFAULT)'
SETUP			=	$$'$(BOLD)$(GREEN)Project setup OK$(DEFAULT)'

# Directories
INC_DIR	=	./include/
SRC_DIR	=	./src/
OBJ_DIR	=	./obj/
BIN_DIR	=	./bin/
LIB_DIR =	./lib/

# Object Compile Status
define compile_check
	@$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
		$(ECHO) $(ERROR) $$'$(@F)'; \
		cat $@.log | sed -E "s/^/`printf "\\e[1;31m"`>`printf "\\e[0m"`  /";	\
	elif [ -s $@.log ]; then \
		$(ECHO) $(WARNING) $$'$(@F)'; \
		cat $@.log | sed -E "s/^/`printf "\\e[1;33m"`>`printf "\\e[0m"`  /";	\
	else \
		$(ECHO) $(OK) $$'$(@F)'; \
		cat $@.log | sed -E "s/^/`printf "\\e[1;32m"`>`printf "\\e[0m"`  /";	\
	fi
	@$(RM) $@.log;
	@exit $$RESULT
endef

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(call compile_check,$(CC) $(CFLAGS) $(LFLAGS) -c -o $@ $<)


NAME		=	my_sokoban

CC		=	gcc

RM		=	rm -f

SRCS	=	$(SRC_DIR)main.c \
	$(SRC_DIR)map.c \
	$(SRC_DIR)game.c \
	$(SRC_DIR)player_move.c

OBJS	=	$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CFLAGS	+=	-I$(INC_DIR) -Wall -Wextra -std=c99 -pedantic -g

LDFLAGS	+=	-L$(LIB_DIR)

LIB	=	-lncurses

all:		$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIB) -o $(NAME)
	@$(call compile_check)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ_DIR)$(NAME)
	@$(ECHO) $(CLEAN)

silent_clean:
	@$(RM) $(OBJS)
	@$(RM) $(BIN_DIR)$(NAME)

fclean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ_DIR)$(NAME)
	@$(ECHO) $(CLEAN)
	@$(RM) $(NAME)
	@$(RM) $(BIN_DIR)$(NAME)
	@$(RM) $(LIB_DIR)*.a
	@$(ECHO) $(FCLEAN)

silent_fclean:	silent_clean
	@$(RM) $(NAME)
	@$(RM) $(BIN_DIR)$(NAME)
	@$(RM) $(LIB_DIR)*.a

re:	silent_fclean all
	@$(ECHO) $(RE_COMPILE)

.PHONY:		all clean silent_clean fclean silent_fclean re
