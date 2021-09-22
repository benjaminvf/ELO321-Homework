/*
* @file : "tarea1.c"
* @author : Patricio Carrasco
*           Benjamin Villegas
* @date : 01/11/2020
* @brief : Codigo para tarea 01 Parte A en ELO 321, semestre 2020-2 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
//#include <errno.h>
#include <time.h>

int sucesion_Collatz (unsigned int );

int main() {
	
  /* creacion de variables para la memoria compartida. */	
  const char *name = "/shm";
  const int SIZE = 4096; 
  int shm_fd ; 
  
  /* se solicita al usuario el numero inicial. */
  int numero ;  
  printf("introduzca numero positivo:\n") ; 
  scanf ( "%d" , &numero ) ;
  /* para realizar el punto 6 comentar esta printf y scanf y darle un valor positivo a la variable numero. */
  if (numero <= 0 ){
        fprintf(stderr , "non-positive number") ;
        return 1 ;
  }
 
  pid_t pid1 , pid2 ; 

  /* creacion de fork para mostrar hora y fecha. */
  pid1 = fork() ; 
  if (pid1 < 0 ){  /* encontrar error. */
      fprintf(stderr , "fork failed") ;
      return 1 ;
  }
  else if (pid1 == 0) {   /*comienzo de  proceso hijo. */
      time_t t;
      struct tm *tm;   /* https://poesiabinaria.net/2012/06/obtener-la-fecha-y-hora-formateada-en-c/ */
      char fechayhora[100];
      t=time(NULL);
      tm=localtime(&t);
      printf ("Hoy es: %02d/%02d/%d  Hora: %02d:%02d:%d \n", tm->tm_mday, tm->tm_mon, 1900+tm->tm_year, tm->tm_hour, tm->tm_min, tm->tm_sec);
      exit(0) ;
  }
  else {     /* proceso padre. */ 
      wait () ;
  }

  /* creacion de fork para sucesion de Collatz. */  
  pid2 = fork() ; 
  if (pid2 < 0 ){  /* encontrar error. */
        fprintf(stderr , "fork failed") ;
        return 1 ;
  }
  else if (pid2 == 0) {   /*comienzo de  proceso hijo */
        char caracter[10] ; 
        void *ptr;
	
      	/* aca se crea el espacio de memoria. */
        shm_fd = shm_open( name , O_CREAT | O_RDWR, 0666);  
        ftruncate(shm_fd,SIZE);
        ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) { /* encontrar error. */
          printf("Map failed\n");
          return 1;
    }
	
	/* se hace la sucesion y se guarda dentro de la memoria compartida. */
    snprintf(caracter , 10 , "%d\n" , numero  ); 
    sprintf(ptr,"%s", caracter);
    ptr += strlen(caracter);
	
    while (numero != 1){
        numero = sucesion_Collatz (numero) ;
        snprintf(caracter , 10,  "%d\n" , numero  ) ; 
        sprintf(ptr,"%s", caracter);
        ptr += strlen(caracter);
    }
    exit(0) ;
  }
  else {     /* proceso padre */ 
         //sleep(15) ; /* descomentar para parte 6 */
          wait () ;
	
	      /* se abre memoria compartida y se imprime */
        void *ptr;
        shm_fd = shm_open( name ,  O_RDONLY, 0666);
        ptr = mmap(0,SIZE, PROT_READ , MAP_SHARED, shm_fd, 0);
      	printf("La sucesion de Collatz es:\n") ; 
        printf("%s",(char *)ptr);
        shm_unlink(name) ;
  }

  return 0 ; 
}

int sucesion_Collatz (unsigned int n) {
  if (n%2 ==0) {
      return n/2 ; 
  } else {
      return (3*n + 1) ;
  }
} 