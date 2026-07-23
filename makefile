main: main.o funcPreAssembler.o  openMcro.o mcroNamesAndLine.o preAssembler.o shareFunc.o  firstPass.o funcFirstPass.o   seconedPass.o  funcSeconedPass.o  binaryWords.o   allBinary.o errors.o funcErrors.o 
	gcc -g -ansi -Wall main.o funcPreAssembler.o  openMcro.o mcroNamesAndLine.o preAssembler.o shareFunc.o  firstPass.o funcFirstPass.o    seconedPass.o  funcSeconedPass.o  binaryWords.o  allBinary.o errors.o funcErrors.o    -o main

main.o: main.c
	gcc -g -ansi -Wall -c main.c -o main.o
funcPreAssembler.o: funcPreAssembler.c
	gcc -g -ansi -Wall -c funcPreAssembler.c -o funcPreAssembler.o
openMcro.o: openMcro.c
	gcc -g -ansi -Wall -c openMcro.c -o openMcro.o
mcroNamesAndLine.o: mcroNamesAndLine.c
	gcc -g -ansi -Wall -c mcroNamesAndLine.c -o mcroNamesAndLine.o
preAssembler.o: preAssembler.c
	gcc -g -ansi -Wall -c preAssembler.c -o preAssembler.o
shareFunc.o: shareFunc.c
	gcc -g -ansi -Wall -c shareFunc.c -o shareFunc.o
firstPass.o: firstPass.c
	gcc -g -ansi -Wall -c firstPass.c -o firstPass.o
funcFirstPass.o: funcFirstPass.c
	gcc -g -ansi -Wall -c funcFirstPass.c -o funcFirstPass.o
seconedPass.o: seconedPass.c
	gcc -g -ansi -Wall -c seconedPass.c -o seconedPass.o
funcSeconedPass.o: funcSeconedPass.c
	gcc -g -ansi -Wall -c funcSeconedPass.c -o funcSeconedPass.o
binaryWords.o: binaryWords.c
	gcc -g -ansi -Wall -c binaryWords.c -o binaryWords.o
allBinary.o: allBinary.c
	gcc -g -ansi -Wall -c allBinary.c -o allBinary.o	
errors.o: errors.c
	gcc -g -ansi -Wall -c errors.c -o errors.o
funcErrors.o: funcErrors.c
	gcc -g -ansi -Wall -c funcErrors.c -o funcErrors.o				
