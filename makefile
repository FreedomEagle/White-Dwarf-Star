GRAPH = gnuplot

CC = clang
CFLAGS = -Wall -O0 -g 
LFLAGS = -O0 -g
LIBS = -lgsl -lm

white-dwarf: white-dwarf.o Starvar.o
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

res1: white-dwarf
	./white-dwarf > res1

white-dwarf.png: white-dwarf.gpl res1
	$(GRAPH) white-dwarf.gpl
	
white-dwarf2: white-dwarf2.o Starvar.o
	${CC} $(LFLAGS) -o $@ $^ $(LIBS)

res2: white-dwarf2
	./white-dwarf2 > res2

white-dwarf2.png: white-dwarf2.gpl res2
	$(GRAPH) white-dwarf2.gpl

clean : 
	rm -f *~
	rm -f *.o
	rm -f white-dwarf2
	rm -f white-dwarf

veryclean : clean
	rm -f res1 white-dwarf.png
	rm -f res1 white-dwarf2.png
