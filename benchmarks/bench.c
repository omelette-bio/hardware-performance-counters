#include <stdio.h>

#define N 2100
#define M 2100
#define P 2100

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
    for ( int i = 0; i < N; i++ )
    {
        for ( int j = 0; j < P; j++ )
        {
            A[i][j] = 1.5f;
        }
    }

    for ( int i = 0; i < P; i++ )
    {
        for ( int j = 0; j < M; j++ )
        {
            B[i][j] = 2.5f;
        }
    }

    mat_mult();
    
    fprintf(stdout, "%f ", C[(int)(0.25 * (N - 1))][(int)(0.25 * (M - 1))]);
    fprintf(stdout, "%f ", C[(int)(0.5 * (N - 1))][(int)(0.5 * (M - 1))]);
    fprintf(stdout, "%f\n", C[(int)(0.75 * (N - 1))][(int)(0.75 * (M - 1))]);

    return 0;
}
