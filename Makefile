##
# Project Title sowut
#
# @file
# @version 0.1
CC=gcc
FLAGS=-Wall -ggdb

all: dir sharedobject sowhat

dir:
	mkdir ./bin/

sowhat:
	$(CC) $(FLAGS) -I ./inc/ ./src/* -o ./bin/sowhat -lz -ldl

# generate shared object for testing
sharedobject:
	$(CC) -Wall -ggdb -Werror -fpic -shared ./src/soex1.c -o /tmp/sowut_test.so

clean:
	rm -rf ./bin/ && rm /tmp/sowut_test.so && rm /tmp/lol
# end
