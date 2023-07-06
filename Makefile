##
# Project Title sowut
#
# @file
# @version 0.1
CC=gcc
FLAGS=-Wall -ggdb

all: sharedobject sowhat

sowhat:
	$(CC) $(FLAGS) -lz -I ./inc/ ./src/* -o sowhat

# generate shared object for testing
sharedobject:
	$(CC) -Wall -ggdb -Werror -fpic -shared ./src/soex1.c -o /tmp/sowut_test.so

clean:
	rm ./sowhat && rm /tmp/sowut_test.so && rm /tmp/lol
# end
