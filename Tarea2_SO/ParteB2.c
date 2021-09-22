/*
* @file : "ParteB2.c"
* @author : Patricio Carrasco
*           Benjamin Villegas
* @date : 23/12/2020
* @brief : Codigo para tarea 02 Parte B punto 2 en ELO 321, semestre 2020-2 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <sys/time.h>

int sudoku_array[9][9] = {{6,5,8,1,9,7,3,4,2},{2,1,3,4,5,6,7,9,8},{4,9,7,3,8,2,1,6,5},{5,7,6,8,2,3,9,1,4},{3,2,1,6,4,9,5,8,7},{9,8,4,5,7,1,6,2,3},{1,6,2,7,3,4,8,5,9},{8,3,9,2,6,5,4,7,1},{7,4,5,9,1,8,2,3,6}} ;

int rows_checked[9];
int cols_checked[9];
int sub_grids_checked[9] ;

struct areas 
{
 int init_row; // fila inicial
 int fin_row; // fila final
 int init_col; // columna inicial
 int fin_col; // columna final
}  ;

double time[100];

int  validity_check( struct areas ) ; 

int main() {
	
int num, num2;
for(num = 0 ; num < 100 ; num ++){

  struct timeval tv1, tv2;
  gettimeofday(&tv1, NULL); 	
 
  int i, j, k, m;
  #pragma opm parallel for
  {
    for (i=0 ; i <= 8 ; i++){
       struct areas row_i={i,i,0,8};
       rows_checked[i]=validity_check(row_i);
    }
  }
  #pragma opm parallel for
  {
     for (j=0 ; j <= 8 ; j++){
        struct areas col_j={0,8,j,j};
        cols_checked[j]=validity_check(col_j);
     }
  }
 
  struct areas grid[9]={{0,2,0,2} , {3,5,0,2} , {6,8,0,2} , {0,2,3,5} , {3,5,3,5} , {6,8,3,5} , {0,2,6,8} , {3,5,6,8} , {6,8,6,8} }; 
  #pragma opm parallel for
  {
     for (k = 0 ; k <= 8 ; k++){
        sub_grids_checked[k] = validity_check(grid[k]);
     }
  }

  #pragma omp barrier
  int check = 1;
  for(m = 0 ; m <= 8 ; m++ ){
     if((sub_grids_checked[m] == 0) || (rows_checked[m] == 0) || (cols_checked[m] == 0)){
        printf("La solucion no es valida.\n");
        check = 0;
     }
  }
  if (check == 1){
     printf("La solución es valida.\n");
  }
  gettimeofday(&tv2, NULL);
  time[num] = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000.0 +
  (double) (tv2.tv_sec - tv1.tv_sec);
  printf ("Time = %f sec\n", time[num]); 


}

double prom;
for(num = 0 ; num < 100 ; num++){
   prom += time[num]/100;
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