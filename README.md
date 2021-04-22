# PROJECT GAME OF LIFE 
 

**Welcome to my implementation of the game of life, made as a class project for one on my classes at the University of Strasbourg**  
**This project uses Cairo graphics library for the graphic part, but is also available in Shell display**  


*The grids are created with the help of .txt files, that are in the grilles/ repository* 
*The project uses Cairo library for graphics* 

### Makefile:   
`make`: compiles (in graphical mode) and creates a library `libjeu.a` in /lib . The main wille be in /obj   
`make MODE=TEXTE`: compiles in non-graphic mode and creates a library `libjeu.a` in /lib . The main will be in /obj  
`make docs`: generates the html documentation  
`make clean`: empties /lib and /obj and deletes those repositories 
`make dist`: creates an archive and puts it in /dist   
`make rmdist`: deletes the archive and the /dist repository  

### Execution:   
After compilation, to execute, type `./bin/main grilles/grille<num_grille>.txt` other grids are the available using the n key. To exit execution, press q.  


## Shell display     
(compile with `make MODE=TEXTE`)  

#### Calcul cyclique/non cyclique:  
To activate or deactivate the cyclic grid, press *c*.  
**Display:**    
*Voisinage: 0* cyclic grid  
*Voisinage: 1* non-cyclic grid  

#### Aging of cells:  
To show the agee of the cells, press the key *v*  
**Display:**    
*Vieillissement: 0* : Cells don't age    
*Vieillissement: 1*: Cells age (from age 1 to 9, they'll die after that)  


#### Oscillation:  
You can check if a grid has an oscillatory behaviour using the *o* Key.  
 

## Graphic display (using Cairo)  
(compile with `make`)  

#### Calcul cyclique/non cyclique:  
To activate or deactivate the cyclic grid, press *c*.  
**Affichage:**    
*cyclic grid : [activated]*   
*cyclic grid: [desactivated]*   

#### Vieillissement:  
To show the agee of the cells, press the key *v*  
**Display:**    
*aging of cells: [desactivated]* : Cells aren't aging     
*aging of cells: [activated]*: Cells are aging (they can't live older than 9 generations)    

 
#### Oscillation: 
You can check if a grid has an oscillatory behaviour using the *o* Key.

