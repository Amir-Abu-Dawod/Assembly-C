all: play

play: compile.o operations.o macroDeployment.o dataInstructions.o addressMethods.o memory.o labels.o auxiliary.o pass1.o pass2.o export.o 
	gcc compile.o operations.o macroDeployment.o dataInstructions.o addressMethods.o memory.o labels.o auxiliary.o pass1.o pass2.o export.o -o play

compile.o: compile.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c compile.c

operations.o: operations.c dataHeaders.h
	gcc -ansi -Wall -pedantic -c operations.c

macroDeployment.o: macroDeployment.c dataHeaders.h
	gcc -ansi -Wall -pedantic -c macroDeployment.c

dataInstructions.o: dataInstructions.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c dataInstructions.c

addressMethods.o: addressMethods.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c addressMethods.c

memory.o: memory.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c memory.c

labels.o: labels.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c labels.c

auxiliary.o: auxiliary.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c auxiliary.c

pass1.o: pass1.c dataHeaders.h 
	gcc -ansi -Wall -pedantic -c pass1.c

pass2.o: pass2.c dataHeaders.h
	gcc -ansi -Wall -pedantic -c pass2.c

export.o: export.c dataHeaders.h
	gcc -ansi -Wall -pedantic -c export.c

clean :
	rm *.o *.ob *.am *.ent *.ext play
