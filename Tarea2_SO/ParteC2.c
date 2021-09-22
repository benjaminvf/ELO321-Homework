/*
* @file : "ParteC2.c"
* @author : Patricio Carrasco
*           Benjamin Villegas
* @date : 23/12/2020
* @brief : Codigo para tarea 02 Parte C punto 1 en ELO 321, semestre 2020-2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

int sudoku_array[9][9] ={{6,5,8,1,9,7,3,4,2},{2,1,3,4,5,6,7,9,8},{4,9,7,3,8,2,1,6,5},{5,7,6,8,2,3,9,1,4},{3,2,1,6,4,9,5,8,7},{9,8,4,5,7,1,6,2,3},{1,6,2,7,3,4,8,5,9},{8,3,9,2,6,5,4,7,1},{7,4,5,9,1,8,2,3,6}} ;
int rows_checked[9] ; 
int cols_checked[9] ;
int sub_grids_checked[9]; 

struct areas 
{
 int init_row; // fila inicial
 int fin_row; // fila final
 int init_col; // columna inicial
 int fin_col; // columna final
}  ;



int  validity_check( struct areas  ) ; 
void*  thread_rows(void*) ; /* se crean  3 funciones para chequear rows ,cols, grids en 3 threads por separado*/
void*  thread_cols(void*) ;
void*  thread_grids(void*) ; 

struct areas row[9]={{0,0,0,8} , {1,1,0,8} , {2,2,0,8} , {3,3,0,8} , {4,4,0,8} , {5,5,0,8} , {6,6,0,8} , {7,7,0,8} , {8,8,0,8} } ;
struct areas col[9]= {{0,8,0,0}, {0,8,1,1} , {0,8,2,2} , {0,8,3,3}  ,{0,8,4,4} , {0,8,5,5} , {0,8,6,6} , {0,8,7,7} , {0,8,8,8} } ;
struct areas grid[9]={{0,2,0,2} , {3,5,0,2} , {6,8,0,2} , {0,2,3,5} , {3,5,3,5} , {6,8,3,5} , {0,2,6,8} , {3,5,6,8} , {6,8,6,8} }; 

double times[100];

int main() {

int num, num2;
for(num = 0 ; num < 100 ; num ++){  /* para hacer un promedio de tiempo luego de repetir 100 veces el mismo proceso */

  struct timeval tv1, tv2;
  gettimeofday(&tv1, NULL); 

  int m , k , i;
  pthread_t threadID[3];
  pthread_attr_t attr[3];
  for(i=0;i<=2;i++)
      pthread_attr_init(&attr[i]);

  pthread_create(&threadID[0], &attr[0],  &thread_rows , NULL ); /* se chequea rows en este thread */
  pthread_create(&threadID[1], &attr[1],  &thread_cols , NULL ); /* se chequea cols en este thread */
  pthread_create(&threadID[2], &attr[2],  &thread_grids , NULL ); /* se chequea grid en este thread */

  for (m=0; m<3; m++) {
      pthread_join(threadID[m], NULL);
  }
  int check = 1;
  for(k = 0 ; k <= 8 ; k++ ){
	    if((sub_grids_checked[k] == 0) || (rows_checked[k] == 0) || (cols_checked[k] == 0)){   /* en esta parte del codigo se ve si la solucion es valida o no */
		       printf("La solucion no es valida.");
           check = 0;

	   }
  }
  if (check == 1){
     printf("La solucion es valida.\n");
  }
  gettimeofday(&tv2, NULL);  /* se calcula timepo  de la repetcion y se guarda en un array */
  times[num] = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 +
  (double) (tv2.tv_sec - tv1.tv_sec);
  printf ("Time = %f sec\n", times[num]); 

}
double prom;
for(num = 0 ; num < 100 ; num++){
 prom += times[num]/100;
}
printf("el tiempo promedio es %f \n", prom);

return 0;
}  


int  validity_check( struct areas area ){

int val_num = ((area.fin_row-area.init_row+1)*(area.fin_col-area.init_col+1));	
int valores[val_num];


int i, j, k = 0 ; 
for (i= area.init_row ; i <= area.fin_row  ; i++ ){
    for (j = area.init_col ; j <=area.fin_col ; j++ ){
	   valores[k]=sudoku_array[i][j];
	   k++;
    }
}

for (k=0 ; k < val_num-1 ; k++ ){
	for (i=k+1 ; i< val_num ; i++){
		if(valores[k] == valores[i])
			return 0;
	}
}
return 1;

}

void*  thread_rows(void* param ){
int i ;
for (i=0 ; i <= 8 ; i++){
	rows_checked[i]=validity_check(row[i]);
}
}
void*  thread_cols(void* param){
int i ;
for (i=0 ; i <= 8 ; i++){
	cols_checked[i]=validity_check(col[i]);
}
}

void*  thread_grids(void* param){
int i ;
for (i=0 ; i <= 8 ; i++){
	sub_grids_checked[i]=validity_check(grid[i]);
}
}
