#include <stdio.h>
#ifndef N
#define N 100000
#endif

// modifiez la valeur de N selon vos besoins
int main(void)
{
  float x,y,z,t;
  int i;

  x = 1.2f;
  y = 1.3f;
  z = 1.4f;
  t = 1.5f;

  for (i=0; i< N; i++){
    x=x+y;
    y=x+t;
    z=x+z;
    x=t+y;
    t=y+x;
  }

  printf("%f, %f, %f, %f\n", x,y,z,t);
  return 0;
}
