CC = g++
FLAGS = -g -Wall -O
INC = -I. -I/home/tcomer/miniconda3/include

PLATFORM=$(shell uname)
ifeq ($(PLATFORM),Darwin)
LIBS=-framework OpenGL -framework GLUT
else
LIBS=-lGL -lglut -lGLU -L/home/tcomer/miniconda3/lib -LD_LIBRARY_PATH/home/tcomer/miniconda/lib3
endif

##################################################
# EXECUTABLES
##################################################
chess: etMouse.o etTransform.o etMath.o etVector.o Mystack.o Vertices.o etSimpleObjParser.o Shapemove.o Movement.o texture.o chess.cpp defs.h
	$(CC) $(FLAGS) $(INC) etMouse.o etTransform.o etMath.o etVector.o Mystack.o Vertices.o etSimpleObjParser.o Shapemove.o Movement.o texture.o chess.cpp -o chess $(LIBS)

test: etMath.o etVector.o vectorTest.cpp
	$(CC) $(FLAGS) etMath.o etVector.o vectorTest.cpp -o test

sqrt: etMath.o etVector.o sqrtTest.cpp
	$(CC) $(FLAGS) etMath.o etVector.o sqrtTest.cpp -o sqrt

fastsqrt: etMath.o etVector.o fastSqrtTest.cpp
	$(CC) $(FLAGS) etMath.o etVector.o fastSqrtTest.cpp -o fastsqrt

##################################################
# ET IMPROVEMENTS
##################################################
etMath.o: etMath.cpp etMath.h
	$(CC) $(FLAGS) $(INC) etMath.cpp -c

etMouse.o: etMouse.cpp etMouse.h
	$(CC) $(FLAGS) $(INC) etMouse.cpp -c

etTransform.o: etTransform.cpp etTransform.h
	$(CC) $(FLAGS) $(INC) etTransform.cpp -c

etVector.o: etVector.cpp etVector.h
	$(CC) $(FLAGS) $(INC) etVector.cpp -c

##################################################
# OLD CODE
##################################################
Mystack.o: Mystack.cpp Mystack.h defs.h
	$(CC) $(FLAGS) $(INC) Mystack.cpp -c

Vertices.o: Vertices.cpp Vertices.h defs.h
	$(CC) $(FLAGS) $(INC) Vertices.cpp -c

etSimpleObjParser.o: etSimpleObjParser.cpp etSimpleObjParser.h defs.h
	$(CC) $(FLAGS) $(INC) etSimpleObjParser.cpp -c

Shapemove.o: Shapemove.cpp Shapemove.h defs.h
	$(CC) $(FLAGS) $(INC) Shapemove.cpp -c

Movement.o: Movement.cpp Movement.h defs.h
	$(CC) $(FLAGS) $(INC) Movement.cpp -c

texture.o: texture.cpp texture.h defs.h
	$(CC) $(FLAGS) $(INC) texture.cpp -c

##################################################
# GENERICS
##################################################
all:
	${MAKE} chess

clean:
	rm -f *~
	rm -f *.o
	rm -f hw3
