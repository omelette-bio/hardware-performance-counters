#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

#ifndef N
#define N 2000
#endif

#ifndef M
#define M 2000
#endif

#ifndef P
#define P 2000
#endif

#define MAX_RANGE 100

float A[N][P], B[P][M], C[N][M];

struct timeval t1, t2;
float temps_execution;

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

    gettimeofday(&t1, NULL);
    mat_mult();
    gettimeofday(&t2, NULL);

    temps_execution = (float)((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec)) / 1000000;

    fprintf(stderr, "%f", A[(int)(0.25 * (N - 1))][(int)(0.25 * (P - 1))]);
    fprintf(stderr, "%f", A[(int)(0.5 * (N - 1))][(int)(0.5 * (P - 1))]);
    fprintf(stderr, "%f", A[(int)(0.75 * (N - 1))][(int)(0.75 * (P - 1))]);
    
    fprintf(stderr, "%f", B[(int)(0.25 * (P - 1))][(int)(0.25 * (M - 1))]);
    fprintf(stderr, "%f", B[(int)(0.5 * (P - 1))][(int)(0.5 * (M - 1))]);
    fprintf(stderr, "%f", B[(int)(0.75 * (P - 1))][(int)(0.75 * (M - 1))]);
    
    fprintf(stderr, "%f", C[(int)(0.25 * (N - 1))][(int)(0.25 * (M - 1))]);
    fprintf(stderr, "%f", C[(int)(0.5 * (N - 1))][(int)(0.5 * (M - 1))]);
    fprintf(stderr, "%f", C[(int)(0.75 * (N - 1))][(int)(0.75 * (M - 1))]);

    printf("%f\n", temps_execution);
    return 0;
}
