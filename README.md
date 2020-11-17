# PROJET JEU DE LA VIE
 
## Version 4.0

**Bienvenue sur mon implémentation du projet jeu de la vie, effectué dans le cadre du cours "Techniques de développement "de L2S3 Informatique, Université de Strasbourg, année 2020/2021**

*Les fichiers .c sont dans src, les .h dans include et les grillesx.txt dans grilles*

### Versionnement:  
chaque x.0 correspond à un niveau du projet complété, ainsi la version 1.0
			correspond au niveau 1 complété, la 2.0 au niveau 2 etc...


### Makefile:   
`make`: compile en mettant les .o dans /bin et le main dans /obj   
`make docs`: génère la documentation html  
`make clean`: vide /bin et/obj et supprime les répertoires  
`make dist`: crée une archive et la place dans /dist   
`make rmdist`: supprime l'archive et le répertoire /dist  

### Execution:   
pour exécuter (après compilation), faire `./bin/main grilles/grille<num_grille>.txt` (les autres grilles sont ensuite accessibles avec la touche n. Pour quitter l'exécution: q

##Affichage shell  
(compilation avec `make MODE=TEXTE`)  

#### Calcul cyclique/non cyclique:  
Pour activer/désactiver le calcul cyclique, appuyer sur la touche *c*.  
**Affichage:**    
*Voisinage: 0* correspond au Calcul cyclique  
*Voisinage: 1* correspond au Calcul non cyclique  

#### Vieillissement:  
Pour activer/désactiver le vieillissement des cellules, appuyer sur la touche *v*  
**Affichage:**    
*Vieillissement: 0* : Les cellules ne vieilissent pas    
*Vieillissement: 1*: Les cellules vieillissent (de age 1 à age 9, elles meurent après)  

#### Cases non accessibles: 
Les cases non accessibles (qui ne peuvent pas être vivantes) sont marqués par un X rouge. 
Elles ont été spécifiées aléatoirement par mes soins dans les fichiers *.txt*.  


## Affichage graphique (cairo) 
(compilation avec `make`)  

#### Calcul cyclique/non cyclique:  
Pour activer/désactiver le calcul cyclique, appuyer sur la touche *c*.  
**Affichage:**    
*cyclic grid : [activated]* correspond au Calcul cyclique  
*cyclic grid: [desactivated]* correspond au Calcul non cyclique  

#### Vieillissement:  
Pour activer/désactiver le vieillissement des cellules, appuyer sur la touche *v*  
**Affichage:**    
*aging of cells: [desactivated]* : Les cellules ne vieilissent pas    
*aging of cells: [activated]*: Les cellules vieillissent (de age 1 à age 9, elles meurent après)  

#### Cases non accessibles: 
Les cases non accessibles (qui ne peuvent pas être vivantes) sont marqués par un carré bleu remplissant la case. 
Elles ont été spécifiées aléatoirement par mes soins dans les fichiers *.txt*.  


