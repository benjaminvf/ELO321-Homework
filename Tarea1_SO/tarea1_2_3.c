/*
* @file : "tarea1_2_3.c"
* @author : Patricio Carrasco
*           Benjamin Villegas
* @date : 01/11/2020
* @brief : Codigo para tarea 01 Parte B 3 en ELO 321, semestre 2020-2 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h> 

/* array de numeros entre 1 y 100. */
int  numArray [50] ; 

void* return_Avg(void*) ;
void* return_Min(void*); 
void* return_Max(void*); 


int main () {

  /* variables locales a calcular. */
  float avg_value ; 
  int min_value ; 
  int max_value ; 

  /* inicializacion del array numArray. */ 	
  int i ;
  for (i =0 ; i<50  ; i++){
    numArray[i] = (rand() % 100 )+ 1    ;
  }

  /* se inicializan los threads y llama a cada funcion. */
  pthread_t threadID[3];
  pthread_attr_t attr[3];
    
  pthread_attr_init(&attr[0]);
  pthread_create(&threadID[0], &attr[0], return_Avg , &avg_value );  /*aca se llama a la variable local que se quiere usar como argumento*/ 
    
  pthread_attr_init(&attr[1]);
  pthread_create(&threadID[1], &attr[1], return_Min , &min_value);
    
  pthread_attr_init(&attr[2]);
  pthread_create(&threadID[2], &attr[2], return_Max , &max_value);

  /* main espera a que terminen los threads. */
  for (i=0; i<3; i++) {
    pthread_join(threadID[i], NULL);
  }
  return 0 ;  
}

void* return_Avg(void *param){ /* esta funcion entrega el promedio. */
  float  suma = 0 ;
  int i ;
  for (i=0 ; i <50 ; i++){
    suma = suma + numArray[i] ;
  }
  /* se define el pointer a un float y se guarda el valor obtenido. */
  float* dir_avg = (float*)param ;
  *dir_avg = suma /50 ; 
     
  printf("Thread ID : %d calculo promedio \n" , pthread_self() ) ;
  printf("Resultado : %f \n" , suma/50 ) ;	  
  pthread_exit(0) ;
}

void* return_Min(void *param){ /* esta funcion entrega el minimo. */
  int min = 101 ;
  int i ;
  for ( i=0 ; i <50 ; i++){
    if (numArray[i] <min) 
      min=numArray[i] ; 
  }
  /* se define el pointer a un int y se guarda el valor obtenido. */
  int* dir_min = (int*)param ;
  *dir_min = min ; 
  
  printf("Thread ID : %d calculo el minimo \n" , pthread_self() ) ;
  printf("Resultado : %d \n" , min ) ;
  pthread_exit(0) ;
}

void* return_Max(void *param){  /* esta funcion entrega el minimo. */
  int max = 0 ;
  int i ;
  for ( i=0 ; i <50 ; i++){
    if (numArray[i] >max) 
      max=numArray[i] ; 
  }
  /* se define el pointer a un int y se guarda el valor obtenido. */
  int* dir_max = (int*)param ;
  *dir_max = max ;
  
  printf("Thread ID : %d calculo el maximo \n" , pthread_self() ) ;
  printf("Resultado : %d \n" , max ) ;
  pthread_exit(0) ;
}