##
# Project Title sowut
#
# @file
# @version 0.1
CC=gcc
FLAGS=-Wall -ggdb

all: dir sharedobject sowhat

release: dir stripped

dir:
	mkdir ./bin/

sowhat:
	$(CC) $(FLAGS) -I ./inc/ ./src/base64.c ./src/loadnexec.c ./src/main.c ./src/srv.c -o ./bin/sowhat -lz -ldl

stripped: 
	$(CC) -I ./inc/ ./src/base64.c ./src/loadnexec.c ./src/main.c ./src/srv.c -o ./bin/sowhat -lz -ldl -s

# generate shared object for testing
sharedobject:
	$(CC) -Wall -ggdb -Werror -fpic -shared ./src/soex1.c -o /tmp/sowut_test.so

clean:
	rm -rf ./bin/ && rm /tmp/sowut_test.so && rm /tmp/lol
# end
