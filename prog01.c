/**
 * DSA_HA01
 * Program 01
 **/

#include<stdio.h>
#include<stdlib.h>

int main(){
  int m, n, p, r, s, q, x, y;             //Declaring the required variables
/**
 * Asking user to input the order of the matrix
 * and the value of 'r' and 's'
 **/

  scanf("%d %d %d %d", &m, &n, &r, &s);

  if (m <= 10 || n <= 10 || r <= 10 || s <= 10){
/**
 * Input array elements
 **/
    int matrix_A[m][n];                              //Input matrix_A
    for (size_t i = 0; i < m; i++){
      for (size_t j = 0; j < n; j++){
        scanf("%d", &matrix_A[i][j]);
      }
    }

/**
 * Calculating the order of the required matrix
 * using the given formula
 **/

    p = m*r;
    q = n*s;

/**
 * Calculating the values of the required matrix
 * here i and j acts as the array index of the output matrix
 * and values of x and y will be calculated to give the required output
 **/

    int matrix_B[p][q];                            //Required matrix_B
    for (size_t i = 0; i < p; i++){
      for (size_t j = 0; j < q; j++){
        if((i+1)%m == 0){
          x = m-1;
        }
        else{
          x = (i+1)%m-1;
        }
        if((j+1)%n == 0){
          y = n-1;
        }
        else{
          y = (j+1)%n-1;
        }
      matrix_B[i][j] = ((i/m)+1)*((j/n)+1)*matrix_A[x][y];
      }
    }

/**
 * printing the required matrix
 **/

    for (size_t i = 0; i < p; i++){
      for (size_t j = 0; j < q; j++){
        printf("%d ", matrix_B[i][j]);
      }
      printf("\n");
    }
  }
  else{
    exit(0);
  }
  return 0;
}
