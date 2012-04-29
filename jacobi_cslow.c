#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;
const int dim = 6;
const int C = 3;
const int cols = dim;
void max_print_matrix(double *m, int rows, int cols, char *hint_msg);
void max_print_array(double (*m)[cols], int rows, int cols, char *hint_msg);


void max_print_vector(void *m, int rows, int cols, char *title);
void max_print_matrixV1(void **m, int rows, int cols, char *title);
int main(int argc, const char** argv) 
{
	
	int MAX_ITER = 1000; 	
	int RUN = C;	
	double A[dim * dim];
	//srand(time(NULL));

	for(int i = 0; i < dim; ++i) {
		double sum = 0;
		for(int j = 0; j < dim; ++j) {
			if(i != j) {
				A[i*dim+j] = 2.0*rand()/(double)RAND_MAX - 1;  // random number between -1 and 1
				//sum += fabs(A[i*dim+j]);
				A[i * dim + j] = 1; 				
				sum += fabs(A[i * dim + j]);

			}
		}
		A[i * dim + i] = 1 + sum;
	}

	/**
	* Start solving. This will go into HW.
	*
	* 	JACOBI(dim, A, b_base, x_base);
	**/
	double sigma[C][dim];
	memset(sigma, 0, C * dim *sizeof(double));
	double x[C][dim];
	memset(x, 0, sizeof(double) * C * dim);
	double z[C][dim];
	memset(z, 0, sizeof(double) * C * dim);
	double b[C][dim];
	memset(b, 0, sizeof(double) * C * dim);
	for(int i = 0; i < C; i ++)
	{
		for(int j = 0; j < dim; j ++)
		{			
			b[i][j] = 2.0*rand()/(double)RAND_MAX - 1;
			b[i][j] = 20;
		}
	}

	max_print_matrix(A, dim, dim, "A");
	max_print_array(b, C, dim, "B");
	int blks = 1;
	int cols = dim;
	//分成几块
	for(int yy = 0; yy < blks; yy++)
   	{
		//对每一块迭代多少次
		for(int e = 0; e < MAX_ITER; e ++)
		{	// update x
			memset(sigma, 0, sizeof(double)* C * dim);
			//当该循环结束，就产生了C个方程的解。
			for(int j = 0; j < cols; j ++)
			{
				//当该循环结束，就产生了C个方程的部分解，每个解得长度为j。
				for(int k = 0; k < C; k ++) 
				{
					//当该循环结束，就产生了第K个方程的部分解，每个解得长度为j
					for(int i = 0; i < dim; i ++)
					{						
						sigma[k][i] += (i != j) ? (A[i * cols + j]*x[k][j]):0;
						z[k][i] = (b[k][i] - sigma[k][i])/A[k * dim + k];
					}
					for(int i = 0; i < dim; i ++)
					{
							
							//z[k][i] =(b[k][i] - sigma[k][i])/A[k * dim + k];
					}
					
				}
			
			}
			//when runs to here, all z values is updated, so now we need to swap z and x
			double tmp[C][dim];
			memcpy(tmp, x, sizeof(double) * C * dim);
			memcpy(x, z, sizeof(double) * C * dim);
			memcpy(z, tmp, sizeof(double) * C * dim);

		}//loop e

		max_print_array(x, C, dim, "Values in X");
		max_print_array(z, C, dim, "Values in Z");
	
	}

	
//	max_print_array(x, C, dim, "Values in X");
//	max_print_array(z, C, dim, "Values in Z");
//	max_print_matrix(sigma, 1, dim, "sigma");

}


void max_print_matrix(double *m, int rows, int cols, char *hint_msg)
{
	fprintf(stderr, "====>%s\n", hint_msg);
	for(int i = 0; i < rows; i ++)
	{
		for(int j = 0; j < cols; j ++)
		{
			fprintf(stderr, "%g ", m[i * cols + j]);
		}
		fprintf(stderr, "\n");
	}
}


void max_print_array(double (*m)[cols], int rows, int cols, char *hint_msg)
{
	fprintf(stderr, "====>%s\n", hint_msg);
	for(int i = 0; i < rows; i ++)
	{
		for(int j = 0; j < cols; j ++)
		{
			fprintf(stderr, "%g ", m[i][j]);
		}
		fprintf(stderr, "\n");
	}
}




void max_print_vector(void *m, int rows, int cols, char *title)
{
	double *m1 = (double *)m;
	printf("======>%s\n", title);
	for(int i = 0; i < rows; i ++)
	{
		for(int j = 0; j < cols; j ++)
		{
			printf("%g ", m1[i * cols + j]);
		}
		printf("\n");
	}
}


void max_print_matrixV1(void **m, int rows, int cols, char *title)
{
	double **m1 = (double **)m;
	printf("======>%s\n", title);
	for(int i = 0; i < rows; i ++)
	{
		for(int j = 0; j < cols; j ++)
		{
			printf("%g ", m1[i][j]);
		}
		printf("\n");
	}
}