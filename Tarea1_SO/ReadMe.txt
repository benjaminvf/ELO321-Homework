Benjamin Villegas  201721007-9 benjamin.villegas@sansano.usm.cl 
Patricio Carrasco  201721064-8 patricio.carrascoo@sansano.usm.cl 

Parte A
En archivo tarea1.c se encuentra toda la parte A de la tarea 

la forma de compilar el programa es:
gcc tarea1.c -o tarea1 -lrt 

para ejecutarlo:
./tarea1 

para el punto 6 de esta misma parte se encuentra una imagen en el archivo que
muestra el proceso Zombie presente.

Para el punto 6 de esta parte hay que comentar las lineas 32 y 33 e incializar 
la variable numero con un numero positivo, por ejemplo int numero=6 ;  
y descomentar el sleep(15) de la linea 94 

se compila de igual manera que en el caso anterior 

para ejecutar esta parte:
./tarea1 & 

y luego ejecutar este comando :

ps -el | grep 'Z' 

el pantallazo de esta parte se encuentra en una imagen del archivo llamado ParteA_Punto6

lo que se puede ver en esta imagen es que hay un proceso zombie antes de terminar sleep(15)
este comando nos muestran PID del proceso zombie PPiD que corresponde el PID del proceso padre.
el Wichan (do exit) es que el proceso ha terminado pero el proceso padre todavia no llama wait()
despues que se ejecutara el programa el estado Wichan cambia a done.
   
 


Parte B 

En archivo tarea1_2.c se encuentra la parte B de la tarea desde el punto  0 hasta 2:

la forma de compilar el programa es:
gcc tarea1_2.c -o tarea1_2 -lrt -lpthread

para ejecutarlo:
./tarea1_2  

En archivo tarea1_2_3.c se encuentra la parte B de la tarea el punto 3:

la forma de compilar el programa es:
gcc tarea1_2_3.c -o tarea1_2_3 -lrt -lpthread

para ejecutarlo:
./tarea1_2_3   
