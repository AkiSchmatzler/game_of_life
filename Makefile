SOURCES = $(wildcard $(C_REP)*.c)
OBJETS = $(SOURCES:.c=.o)
OBJETSC = $(patsubst $(C_REP)%.c, $(O_REP)ù.o, $(SOUCRES))
IFLAGS = -I include -W -Wall
DOCGEN = doxygen
CC = gcc
O_REP = obj/
E_REP = bin/
C_REP = src/
H_REP = include/
D_REP = dist/

vpath %.o $(O_REP)
vpath %.c $(C_REP)
vpath %.h $(H_REP)
vpath main bin

main : $(OBJETS)
	$(CC) -g -o $@ $(OBJETSC)
	mv $@ $(O_REP)

%.o : %.c io.h
	$(CC) -c $(IFLAGS) -o $@ $<
	mv $@ $(E_REP)

.PHONY : clean 

clean : 
	rm $(O_REP)* $(E_REP)*
	@echo "\n###### Les repertoires obj/ et bin/ sont vidés #######\n"

docs : 
	$(DOCGEN)

rmdist :
	rm $(D_REP)*
	rmdir $(D_REP)*
	@echo "\n###### Archive effacée ######\n"

dist :
	@mkdir -p dist
	Doxygen -g
	tar -l -cvf dist/Jeu_de_la_vie.tar.xz grilles include Makefile Doxyfile
	@echo "\n ######## Archive créée ######### \n"






