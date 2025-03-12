#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <bits/time.h>
#include <perfmon/perf_event.h>
#include <stdint.h>
#include <stdio.h>
#include <perfmon/pfmlib.h>
#include <perfmon/pfmlib_perf_event.h>
#include <string.h>
#include <unistd.h>
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

struct timeval t1, t2;
float temps_execution;

/*
L1-dcache-loads OR cpu/L1-dcache-loads/
  L1-dcache-load-misses OR cpu/L1-dcache-load-misses/
  L1-dcache-stores OR cpu/L1-dcache-stores/
  L1-icache-load-misses OR cpu/L1-icache-load-misses/
  LLC-loads OR cpu/LLC-loads/
  LLC-load-misses OR cpu/LLC-load-misses/
  LLC-stores OR cpu/LLC-stores/
  LLC-store-misses
*/

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
  struct perf_event_attr pe;
  int fd_l1_loadm, fd_l1_load, fd_l1_store, fd_l1_storem;
  int fd_llc_loadm, fd_llc_load, fd_llc_store, fd_llc_storem;
  float x,y,z,t;
  int i, ret;
  uint64_t l1_loadm_counter, l1_load_counter, l1_store_counter, l1_storem_counter;
  uint64_t llc_loadm_counter, llc_load_counter, llc_store_counter, llc_storem_counter;
  pfm_perf_encode_arg_t arg;
  
  ret = pfm_initialize();
  if (ret != PFM_SUCCESS)
	  fprintf(stderr, "cannot initialize library: %s\n", pfm_strerror(ret));

  memset(&pe, 0, sizeof(struct perf_event_attr));
  memset(&arg, 0, sizeof(pfm_perf_encode_arg_t));

  arg.attr = &pe;
  if (pfm_get_os_event_encoding("l1-dcache-loads", PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
    fprintf(stderr, "Error encoding event\n");
    return -1;
  }

  fd_l1_load = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_l1_load == -1) {
    perror("perf_event_open");
    return -1;
  }

  if (pfm_get_os_event_encoding("L1-dcache-load-misses", PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
    fprintf(stderr, "Error encoding event\n");
    return -1;
  }

  fd_l1_loadm = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_l1_loadm == -1) {
    perror("perf_event_open");
    return -1;
  }

  if (pfm_get_os_event_encoding("L1-dcache-stores", PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
    fprintf(stderr, "Error encoding event\n");
    return -1;
  }

  fd_l1_store = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_l1_loadm == -1) {
    perror("perf_event_open");
    return -1;
  }

  if (pfm_get_os_event_encoding("L1-dcache-store-misses", PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
    fprintf(stderr, "Error encoding event\n");
    return -1;
  }

  fd_l1_storem = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_l1_loadm == -1) {
    perror("perf_event_open");
    return -1;
  }

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
  
  ioctl(fd_l1_load, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_l1_load, PERF_EVENT_IOC_ENABLE, 0);
  
  ioctl(fd_l1_loadm, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_l1_loadm, PERF_EVENT_IOC_ENABLE, 0);
  
  ioctl(fd_l1_store, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_l1_store, PERF_EVENT_IOC_ENABLE, 0);
  
  ioctl(fd_l1_storem, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_l1_storem, PERF_EVENT_IOC_ENABLE, 0);

  gettimeofday(&t1, NULL);
  mat_mult();
  gettimeofday(&t2, NULL);
  
  ioctl(fd_l1_load, PERF_EVENT_IOC_DISABLE, 0);
  ioctl(fd_l1_loadm, PERF_EVENT_IOC_DISABLE, 0);
  ioctl(fd_l1_store, PERF_EVENT_IOC_DISABLE, 0);
  ioctl(fd_l1_storem, PERF_EVENT_IOC_DISABLE, 0);

  read(fd_l1_load, &l1_load_counter, sizeof(uint64_t));
  read(fd_l1_loadm, &l1_loadm_counter, sizeof(uint64_t));
  read(fd_l1_store, &l1_store_counter, sizeof(uint64_t));
  read(fd_l1_storem, &l1_storem_counter, sizeof(uint64_t));



  fprintf(stderr, "L1_CACHE_LOADS: %lu\n", l1_load_counter);
  fprintf(stderr, "L1_CACHE_LOAD_MISSES: %lu\n", l1_loadm_counter);
  fprintf(stderr, "L1_CACHE_STORES: %lu\n", l1_store_counter);
  fprintf(stderr, "L1_CACHE_STORE_MISSES: %lu\n", l1_storem_counter);
  


  close(fd_l1_load);
  close(fd_l1_loadm);
  close(fd_l1_store);
  close(fd_l1_storem);
  pfm_terminate();

  temps_execution = (float)((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec)) / 1000000;

  fprintf(stdout, "%f", A[(int)(0.25 * (N - 1))][(int)(0.25 * (P - 1))]);
  fprintf(stdout, "%f", A[(int)(0.5 * (N - 1))][(int)(0.5 * (P - 1))]);
  fprintf(stdout, "%f", A[(int)(0.75 * (N - 1))][(int)(0.75 * (P - 1))]);
    
  fprintf(stdout, "%f", B[(int)(0.25 * (P - 1))][(int)(0.25 * (M - 1))]);
  fprintf(stdout, "%f", B[(int)(0.5 * (P - 1))][(int)(0.5 * (M - 1))]);
  fprintf(stdout, "%f", B[(int)(0.75 * (P - 1))][(int)(0.75 * (M - 1))]);
    
  fprintf(stdout, "%f", C[(int)(0.25 * (N - 1))][(int)(0.25 * (M - 1))]);
  fprintf(stdout, "%f", C[(int)(0.5 * (N - 1))][(int)(0.5 * (M - 1))]);
  fprintf(stdout, "%f", C[(int)(0.75 * (N - 1))][(int)(0.75 * (M - 1))]);

  printf("%f\n", temps_execution);
  return 0;
}
