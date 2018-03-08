OBJS = draw.o output.o matrix.o parser.o main.o
OUTPUT = picture.ppm
EXEC = exec
MATH_LIB = -lm
SCRIPT=script

all: $(OBJS)
	gcc -o $(EXEC) $(OBJS) $(MATH_LIB)
	./$(EXEC) $(SCRIPT)

main.o: main.c include/draw.h include/output.h include/matrix.h
	gcc $(DBG) -Wall -c main.c include/draw.h include/output.h include/matrix.h

draw.o: draw.c include/draw.h include/output.h include/dimen.h
	gcc $(DBG) -Wall -c draw.c include/draw.h include/output.h include/dimen.h

output.o: output.c include/output.h include/draw.h
	gcc $(DBG) -Wall -c output.c include/output.h include/draw.h

matrix.o: matrix.c include/matrix.h
	gcc $(DBG) -Wall -c matrix.c include/matrix.h

parser.o: parser.c include/parser.h include/draw.h include/output.h include/matrix.h
	gcc $(DBG) -Wall -c parser.c include/parser.h include/draw.h include/output.h include/matrix.h

clean:
	rm -rf *.o $(OUTPUT)

