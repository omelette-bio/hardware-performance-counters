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
#define N 100000
#endif

#define FLOP_IN_LOOP 5

struct timespec t1, t2;
float temps_execution;

// modifiez la valeur de N selon vos besoins
int main(void)
{
  struct perf_event_attr pe;
  int fd_cycles, fd_instructions;
  float x,y,z,t;
  int i, ret;
  uint64_t instructions_counter, cycles_counter;
  pfm_perf_encode_arg_t arg;
  char *event1 = "cycles";
  char *event2 = "instructions";

  ret = pfm_initialize();
  if (ret != PFM_SUCCESS)
	  fprintf(stderr, "cannot initialize library: %s\n", pfm_strerror(ret));

  memset(&pe, 0, sizeof(struct perf_event_attr));
  memset(&arg, 0, sizeof(pfm_perf_encode_arg_t));

  arg.attr = &pe;
  if (pfm_get_os_event_encoding(event1, PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
    fprintf(stderr, "Error encoding event\n");
    return -1;
  }

  fd_cycles = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_cycles == -1) {
    perror("perf_event_open");
    return -1;
  }

  if (pfm_get_os_event_encoding(event2, PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) 
  {
    fprintf(stderr, "Error encoding event 2\n");
    return -1;
  }

  fd_instructions = perf_event_open(&pe, 0, -1, -1, 0);
  if (fd_cycles == -1)
  {
    perror("perf_event_open");
    return -1;
  }

  x = 1.2f;
  y = 1.3f;
  z = 1.4f;
  t = 1.5f;

  ioctl(fd_cycles, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_cycles, PERF_EVENT_IOC_ENABLE, 0);
  
  ioctl(fd_instructions, PERF_EVENT_IOC_RESET, 0);
  ioctl(fd_instructions, PERF_EVENT_IOC_ENABLE, 0);

  clock_gettime(CLOCK_REALTIME, &t1);
  for (i=0; i< N; i++){
    x=x+y;
    y=x+t;
    z=x+z;
    x=t+y;
    t=y+x;
  }
  clock_gettime(CLOCK_REALTIME, &t2);

  ioctl(fd_cycles, PERF_EVENT_IOC_DISABLE, 0);
  ioctl(fd_instructions, PERF_EVENT_IOC_DISABLE, 0);

  read(fd_cycles, &cycles_counter, sizeof(uint64_t));
  read(fd_instructions, &instructions_counter, sizeof(uint64_t));

  fprintf(stderr, "FLOP: %d\n", N * FLOP_IN_LOOP);
  fprintf(stderr, "CPU_CYCLES: %lu\n", cycles_counter);
  fprintf(stderr, "INSTRUCTIONS: %lu\n", instructions_counter);
  fprintf(stderr, "TIME_TAKEN(ns): %lu\n", t2.tv_nsec-t1.tv_nsec);

  printf("%f, %f, %f, %f\n", x,y,z,t);
  close(fd_cycles);
  close(fd_instructions);
  pfm_terminate();
  return 0;
}
