/*
* @file : "tarea1_2.c"
* @author : Patricio Carrasco
*           Benjamin Villegas
* @date : 01/11/2020
* @brief : Codigo para tarea 01 Parte B 1 y 2 en ELO 321, semestre 2020-2 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 

/* variables globales a calcular. */
float avg_value ; 
int min_value ; 
int max_value ; 

/* array de numeros entre 1 y 100. */
int  numArray [50] ; 

void* return_Avg() ;
void* return_Min(); 
void* return_Max(); 


int main () {
	
  /* inicializacion del array numArray. */ 	
  int  i ;
  for ( i =0 ; i<50  ; i++){
    numArray[i] = (rand() % 100) + 1    ;
  }

  /* se inicializan los threads y llama a cada funcion. */
  pthread_t thread_ID[3];
  pthread_attr_t attr[3];
    
  pthread_attr_init(&attr[0]);
  pthread_create(&thread_ID[0], &attr[0], &return_Avg , NULL); 
    
  pthread_attr_init(&attr[1]);
  pthread_create(&thread_ID[1], &attr[1], &return_Min , NULL);
    
  pthread_attr_init(&attr[2]);
  pthread_create(&thread_ID[2], &attr[2], &return_Max , NULL);

  /* main espera a que terminen los threads. */
  for (i=0; i<3; i++) {
      pthread_join(thread_ID[i], NULL);
      }
  return 0 ;  
}

void* return_Avg(){ /* esta funcion entrega el promedio. */
  float  suma = 0 ;
  int  i ; 
  for ( i=0 ; i <50 ; i++){
    suma = suma + numArray[i] ;
  }
  avg_value = suma /50 ; 
   
  printf("Thread ID : %d calculo promedio \n" , pthread_self() ) ;
  printf("Resultado : %f \n" , avg_value ) ;	 
  pthread_exit(0) ;
}

void* return_Min(){ /* esta funcion entrega el minimo. */
  int min = 101 ;
  int  i ;
  for ( i=0 ; i <50 ; i++){
    if (numArray[i] <min) 
      min=numArray[i] ; 
  }
  min_value = min ; 
  
  printf("Thread ID : %d calculo el minimo \n" , pthread_self() ) ;
  printf("Resultado : %d \n" , min_value ) ;
  pthread_exit(0) ;
}

void* return_Max(){ /* esta funcion entrega el maximo. */
  int max = 0 ;
  int  i ; 
  for ( i=0 ; i <50 ; i++){
    if (numArray[i] >max) 
      max=numArray[i] ; 
  }
  max_value = max ; 
  
  printf("Thread ID : %d calculo el maximo \n" , pthread_self() ) ;
  printf("Resultado : %d \n" , max_value ) ;
  pthread_exit(0) ;
}






