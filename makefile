SOURCES = $(wildcard $(C_REP)*.c)
OBJETS = $(SOURCES:.c=.o)
OBJETSC = $(patsubst $(C_REP)%.c, $(O_REP)%.o, $(SOURCES))
CC = gcc


O_REP = obj/
E_REP = bin/
C_REP = src/
H_REP = include/
D_REP = dist/
IFLAGS = -I include -W -Wall

MODE = CAIRO

VPATH = $(H_REP)
vpath %.o $(E_REP)
vpath %.c $(C_REP)
vpath %.h $(H_REP)
vpath main $(O_REP)




main : $(OBJETS)
	$(CC) -g -o $@ $(OBJETSC) -Llib/ -Iinclude -I/usr/include/cairo -lcairo -lm -lX11
	mkdir -p $(E_REP)
	mv $@ $(E_REP)
	@echo "\n ########  La compilation fut un franc succés   ##########\n"


%.o : %.c graphic.h
	mkdir -p $(O_REP)
	$(CC) -D$(MODE) -c $(IFLAGS) -o $@ $< -I/opt/x11/include
	mv $@ $(O_REP)


.PHONY : clean mrproper

	
clean:
	rm $(O_REP)* $(E_REP)*
	rmdir $(O_REP)
	rmdir $(E_REP)
	@echo "\n######## Les repertoires obj/ et bin/ ont ete vides puis supprimes ########\n"
	

docs:
	doxygen Doxyfile
	

dist: 
	@mkdir -p dist
	tar -l -cvf dist/SchmatzlerAki-GoL-3.0.tar.xz src makefile Doxyfile
	@echo "\n ######## Archive créée ########\n"
	

rmdist: 
		rm $(D_REP)*
		rmdir $(D_REP)
		@echo "\n########## Archive effacée ###########\n"

