#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

#ifndef N
#define N 2500
#endif

#ifndef M
#define M 2500
#endif

#ifndef P
#define P 2500
#endif

#define MAX_RANGE 100

float A[N][P], B[P][M], C[N][M];

void mat_mult()
{
    for (int i=0; i< N; i++){
        for (int j=0; j< M; j++){
            for (int k=0; k< P; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    for ( int i = 0; i < N; i++ )
    {
        for ( int j = 0; j < P; j++ )
        {
            A[i][j] = ((float)rand()/(float)RAND_MAX)*MAX_RANGE;
        }
    }

    for ( int i = 0; i < P; i++ )
    {
        for ( int j = 0; j < M; j++ )
        {
            B[i][j] = ((float)rand()/(float)RAND_MAX)*MAX_RANGE;
        }
    }

    mat_mult();

    fprintf(stdout, "%f", A[(int)(0.25 * (N - 1))][(int)(0.25 * (P - 1))]);
    fprintf(stdout, "%f", A[(int)(0.5 * (N - 1))][(int)(0.5 * (P - 1))]);
    fprintf(stdout, "%f", A[(int)(0.75 * (N - 1))][(int)(0.75 * (P - 1))]);
    
    fprintf(stdout, "%f", B[(int)(0.25 * (P - 1))][(int)(0.25 * (M - 1))]);
    fprintf(stdout, "%f", B[(int)(0.5 * (P - 1))][(int)(0.5 * (M - 1))]);
    fprintf(stdout, "%f", B[(int)(0.75 * (P - 1))][(int)(0.75 * (M - 1))]);
    
    fprintf(stdout, "%f", C[(int)(0.25 * (N - 1))][(int)(0.25 * (M - 1))]);
    fprintf(stdout, "%f", C[(int)(0.5 * (N - 1))][(int)(0.5 * (M - 1))]);
    fprintf(stdout, "%f", C[(int)(0.75 * (N - 1))][(int)(0.75 * (M - 1))]);

    return 0;
}
