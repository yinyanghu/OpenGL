CC = g++
CFLAGS = -Wall
LIB = -lGL -lGLU -lglut

all: bresenham_line bresenham_circle filling weiler_atherton z-buffer Bezier BezierCurve

BezierCurve: BezierCurve.cc
	$(CC) $(CFLAGS) $(LIB) BezierCurve.cc -o BezierCurve

Bezier: Bezier.cc
	$(CC) $(CFLAGS) $(LIB) Bezier.cc -o Bezier

z-buffer: z-buffer.cc
	$(CC) $(CFLAGS) $(LIB) z-buffer.cc -o z-buffer

weiler_atherton: weiler_atherton.cc
	$(CC) $(CFLAGS) $(LIB) weiler_atherton.cc -o weiler_atherton

filling: filling.cc
	$(CC) $(CFLAGS) $(LIB) filling.cc -o filling

bresenham_line: bresenham_line.cc
	$(CC) $(CFLAGS) $(LIB) bresenham_line.cc -o bresenham_line

bresenham_circle: bresenham_circle.cc
	$(CC) $(CFLAGS) $(LIB) bresenham_circle.cc -o bresenham_circle

clean:
	rm -f bresenham_line bresenham_circle filling weiler_atherton z-buffer Bezier
