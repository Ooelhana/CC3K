XX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = cc3k
OBJECTS = testmain.o GameObject.o Character.o Player.o cell.o floor.o Enemy.o gold.o potion.o Chamber.o
DEPENDS = ${OBJECTS:.o=.d}

$EXEC: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean: 
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
