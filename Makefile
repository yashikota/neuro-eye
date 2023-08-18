CC = g++
CFLAGS = -Wall -Wextra
SRCDIR = src
SRCS = $(SRCDIR)/main.cpp $(SRCDIR)/window.cpp $(SRCDIR)/camera.cpp
PROG = main

OPENCV = `pkg-config opencv4 --cflags --libs`
LIBS = $(OPENCV)

all: $(PROG)

$(PROG): $(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(PROG)
