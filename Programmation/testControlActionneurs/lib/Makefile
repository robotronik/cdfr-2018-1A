CC=gcc
CFLAGS=-W -Wall -ansi -std=c99
LD=ld
LDFLAGS=
EXEC=a.out
SRC= $(wildcard *.c)
HDR = $(wildcard *.h)
OBJ= $(SRC:.c=.o)

#colors
NC=\033[0m
BLACK=\033[0;30m
DGRAY=\033[1;30m
LGRAY=\033[0;37m
WHITE=\033[1;37m
RED=\033[0;31m
LRED=\033[1;31m
GREEN=\033[;32m
LGREEN=\033[1;32m
ORANGE=\033[0;33m
YELLOW=\033[1;33m
BLUE=\033[0;34m
LBLUE=\033[1;34m
PURPLE=\033[0;35m
LPURPLE=\033[1;35m
CYAN=\033[0;36m
LCYAN=\033[1;36m

all: $(EXEC)

$(EXEC): $(OBJ)
	@echo -e "\t${YELLOW}Building exec. ${LGREEN}$@${YELLOW}${NC}"
	@echo -e -n "${YELLOW}[${GREEN}OK${YELLOW}]${NC}\r"
	@$(CC) -o $@ $^ $(LDFLAGS)
	@echo -e -n "\n"

%.o: %.c $(HDR)
	@echo -e "\t${YELLOW}Building obj. ${LGREEN}$@${YELLOW}${NC}"
	@echo -e -n "${YELLOW}[${GREEN}OK${YELLOW}]${NC}\r"
	-@$(CC) -o $@ -c $< $(CFLAGS)
	@echo -e -n "\n"

run: $(EXEC)
	@echo -e "\t${YELLOW}Running exec. ${LGREEN}$@${YELLOW}${NC}"
	@./$(EXEC)
	@echo -e "${YELLOW}[${GREEN}OK${YELLOW}]${NC}"

clean:
	@echo -e "\t${YELLOW}Removing ${LGREEN}*.o${NC}"
	@rm -rf *.o $(EXEC)
	@echo -e "${YELLOW}[${GREEN}OK${YELLOW}]${NC}"

