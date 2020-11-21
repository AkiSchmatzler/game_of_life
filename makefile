SOURCES = $(wildcard $(C_REP)*.c)
OBJETS = $(SOURCES:.c=.o)
OBJETSC = $(patsubst $(C_REP)%.c, $(O_REP)%.o, $(SOURCES))
CC = gcc
LIB = libjeu.a

O_REP = obj/
E_REP = bin/
C_REP = src/
H_REP = include/
D_REP = dist/
L_REP = lib/
IFLAGS = -I include -W -Wall
MODE = CAIRO

vpath %.o $(O_REP)
vpath %.c $(C_REP)
vpath %.h $(H_REP)
vpath main $(O_REP)


main : $(OBJETS)
	mkdir -p $(E_REP)
	mkdir -p $(L_REP)
	ar -crv $(LIB) $(O_REP)*
	mv $(LIB) $(L_REP)
	rm $(O_REP)*
	rmdir $(O_REP)
	$(CC) -o $@ -ljeu -Llib/ -Iinclude -I/usr/include/cairo -lcairo -lm -lX11
	mv $@ $(E_REP)
	@echo "\n ########  La compilation fut un franc succès :)  ##########\n"

%.o : %.c graphic.h
	@mkdir -p $(O_REP)
	$(CC) -D$(MODE) -c $(IFLAGS) -o $@ $< -I/opt/x11/include
	mv $@ $(O_REP)


.PHONY : clean mrproper

	
clean:
	rm $(L_REP)* $(E_REP)*
	rmdir $(L_REP)
	rmdir $(E_REP)
	@echo "\n######## Les repertoires lib/ et bin/ ont été vidés puis supprimés ########\n"
	

docs:
	doxygen Doxyfile
	

dist: 
	@mkdir -p dist
	tar -l -cvf dist/SchmatzlerAki-GoL-5.0.tar.xz src makefile Doxyfile
	@echo "\n ######## Archive créée :) ########\n"
	

rmdist: 
		rm $(D_REP)*
		rmdir $(D_REP)
		@echo "\n########## Archive effacée ###########\n"

