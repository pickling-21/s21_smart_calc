TARGET ?= SmartCalc_v1

CC=gcc 
CFLAGS=-std=c11 -Wall -Werror -Wextra

GCOV=--coverage
SRC_DIRS ?=./Project

TEST_DIR = ./Tests
TEST_SRC := $(shell find $(TEST_DIR) -name '*.c' )
TEST := $(addsuffix .o,$(basename $(TEST_SRC)))

SCR_ALL ?= ./

C_SRCS := $(shell find $(SRC_DIRS) -name '*.c' )
C_SRCSH := $(shell find $(SRC_DIRS) -name '*.h' )

SRCSCPP := $(shell find $(SCR_ALL) -name '*.cpp' )
SRCSC := $(shell find $(SCR_ALL) -name '*.c' )
SRCSH := $(shell find $(SCR_ALL) -name '*.h' )

OBJS := $(addsuffix .o,$(basename $(C_SRCS)))

README = README.html


all: $(TARGET).a

$(TARGET).a: $(OBJS)
	@ar rc $@ $(OBJS)

tests : clean $(TARGET).a $(OBJS) $(TEST)
	$(CC) $(CFLAGS) $(OBJS) $(TEST) -l check -L. $(TARGET).a -o test
	./test


install:
	qmake -o Executables/Makefile $(TARGET)/$(TARGET).pro
	cd Executables && make
	
start: install
	cd Executables/$(TARGET).app/Contents/MacOS && ./$(TARGET)

dist: install 
	cd .. && tar -czf $(TARGET).tgz src


uninstall: clean
	rm -rf Executables

dvi: 
	open $(README)

gcov_report: install_lcov g$(TARGET).a
	$(CC) -o gcov g$(TARGET).a -lcheck $(TEST_SRC) $(C_SRCS) $(GCOV)
	chmod +x gcov
	./gcov
	lcov -t "gcovReport" -o gcov.info -c -d .
	genhtml -o report gcov.info
	open report/index.html


g$(TARGET).a: $(OBJS)
	$(CFLAGS)+=$(GCOV)
	@ar rc  $@ $(OBJS)


leaks:
	chmod 777 Executables/$(TARGET).app/Contents/MacOS/$(TARGET)
	cd Executables/$(TARGET).app/Contents/MacOS && CK_FORK=no leaks --atExit -- ./$(TARGET)

install_lcov:
	brew install lcov

clean_import:
	rm -rf Import
	mkdir Import

clean:
	$(RM) a.out $(TARGET).a $(OBJS) $(TARGET).o test $(TEST)
	$(RM) gcov  *.info *.gcda *.gcno Tests/*.gcda Tests/*.gcno g$(TARGET).a 
	cd $(TARGET) && $(RM)  *.pro.user
	rm -rf report


push: 
	git add .
	git commit -m'$m'
	git push '$o'

# m - commit 
# o - origin

# brew:
# eval "$(/opt/goinfre/pickling/homebrew/bin/brew shellenv)"
# chmod -R go-w "$(brew --prefix)/share/zsh"

style: 
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -n $(SRCSC)
	clang-format -n $(SRCSCPP)
	clang-format -n $(SRCSH)
	rm -rf .clang-format

style_done: 
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -i $(SRCSC)
	clang-format -i $(SRCSCPP)
	clang-format -i $(SRCSH)
	rm -rf .clang-format


# docker:
# 	rm -rf ~/Library/Containers/com.docker.docker
# 	mkdir -p ~/goinfre/Docker/Data
# 	ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker

# val: docker
# 	cd Valgrind && sh run.sh

# valgrind: start
# 	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT.txt ./$(TARGET)
# 	cat RESULT.txt