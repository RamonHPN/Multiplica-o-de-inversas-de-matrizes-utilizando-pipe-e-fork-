#include <stdio.h>
#include <unistd.h>
#define BUFSIZE 80
#include<math.h>

float determinant(float [][25], float);
void cofactor(float [][25], float);
void transpose(float [][25], float [][25], float);
void matrizA(float k);
void matrizB(float k);

float x[25][25], teste, teste2;
float matrixA[25][25], matrixB[25][25], matrixR[25][25];


int main(void)
{
  int fd[2];
  pipe(fd);
  float a[25][25], k, d;
  float b[25][25], f;
 
  //float x[25][25];
  int i, j, g;
  printf("Enter the order of the Matrix '': ");
  scanf("%f", &k);

 
  if (fork() == 0) {

    matrizB(k);
    close(fd[0]);
   
   
    for (i = 0;i < k; i++)
      {
     for (j = 0;j < k; j++)
       {
         //printf("\n%f\n", x[i][j]);
         teste = x[i][j];
         //printf("\n%f\n", teste);
         write(fd[1], &teste, sizeof(teste));
        }
      }
   
   
  }
   
  else {
   
    wait(0);
    close(fd[1]);
    matrizA(k);

    //Obtendo os valores da matriz A
    for (i = 0;i < k; i++)
      {
     for (j = 0;j < k; j++)
       {
         
         matrixA[i][j] = x[i][j];
         
        }
      }
   
    for (i = 0;i < k; i++)
      {
     for (j = 0;j < k; j++)
       {
         read(fd[0], &teste2, sizeof(teste2));
     
         matrixB[i][j] = teste2;
         
        }
      }

    printf("\nA multiplicação das inversas é:\n");
    for (i = 0;i < k; i++)
      {
       for (j = 0;j < k; j++)
         {
           matrixR[i][j] = 0;
           
           for (g = 0;g < k; g++)
             {
               
               matrixR[i][j] = matrixR[i][j] + matrixA[i][g]*matrixB[g][j];
               
             }
           
            printf("\t%f",matrixR[i][j]);
           
          }
        printf("\n");
        }  
  }
 
}




void matrizA(float k){

  float a[25][25], d;
  float b[25][25], f;
  //float x[25][25];
  int i, j, g;

  printf("\nEnter the elements of %.0fX%.0f Matrix A: \n", k, k);
  for (i = 0;i < k; i++)
    {
     for (j = 0;j < k; j++)
       {
        scanf("%f", &a[i][j]);
        }
    }
 
  d = determinant(a, k);
  if (d == 0)
   printf("\nInverse of Entered Matrix is not possible\n");
  else
    cofactor(a, k);
}

void matrizB(float k){

  float a[25][25], d;
  float b[25][25], f;
  //float x[25][25];
  int i, j, g;
 
  printf("\nEnter the elements of %.0fX%.0f Matrix B: \n", k, k);
  for (i = 0;i < k; i++)
    {
     for (j = 0;j < k; j++)
       {
        scanf("%f", &b[i][j]);
        }
    }
 
  f = determinant(b, k);
  if (f == 0)
   printf("\nInverse of Entered Matrix is not possible\n");
  else
    cofactor(b, k);
 
}


/*For calculating Determinant of the Matrix */
float determinant(float a[25][25], float k)
{
  float s = 1, det = 0, b[25][25];
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }
 
    return (det);
}
 
void cofactor(float num[25][25], float f)
{
 float b[25][25], fac[25][25];
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  transpose(num, fac, f);
}

/*Finding transpose of matrix*/
void transpose(float num[25][25], float fac[25][25], float r)
{
  int i, j;
  float b[25][25], inverse[25][25], d;
 
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinant(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse[i][j] = b[i][j] / d;
        }
    }
   printf("\nThe inverse of matrix is : \n");
 
   for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         printf("\t%f", inverse[i][j]);
         x[i][j] = inverse[i][j];
         
        }
    printf("\n");
     }
}