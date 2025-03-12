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
	// int fd_cycles, fd_instructions;
	float x,y,z,t;
	int i, ret;
	uint64_t instructions_counter, cycles_counter;
	pfm_perf_encode_arg_t arg;

	int fds[2];
	char *event_list[2] = {"cycles", "instructions"};

	// initialize the library
	ret = pfm_initialize();
	if (ret != PFM_SUCCESS)
		fprintf(stderr, "cannot initialize library: %s\n", pfm_strerror(ret));

	// makes sure the data is set to 0
	memset(&pe, 0, sizeof(struct perf_event_attr));
	memset(&arg, 0, sizeof(pfm_perf_encode_arg_t));

	// attribute of argument is pe (perf event attribute)
	arg.attr = &pe;

	for (i=0; i<2; i++)
	{
		if (pfm_get_os_event_encoding(event_list[i], PFM_PLM3, PFM_OS_PERF_EVENT, &arg) != PFM_SUCCESS) {
			fprintf(stderr, "Error encoding event\n");
			return -1;
		}

		fds[i] = perf_event_open(&pe, 0, -1, -1, 0);
		if (fds[i] == -1) {
			perror("perf_event_open");
			return -1;
		}
	}
	
	x = 1.2f;
	y = 1.3f;
	z = 1.4f;
	t = 1.5f;

	for (int i=0; i<2; i++)
	{
		ioctl(fds[i], PERF_EVENT_IOC_RESET, 0);
		ioctl(fds[i], PERF_EVENT_IOC_ENABLE, 0);
	}

	clock_gettime(CLOCK_REALTIME, &t1);
	for (i=0; i< N; i++){
		x=x+y;
		y=x+t;
		z=x+z;
		x=t+y;
		t=y+x;
	}
	clock_gettime(CLOCK_REALTIME, &t2);

	ioctl(fds[0], PERF_EVENT_IOC_DISABLE, 0);
	ioctl(fds[1], PERF_EVENT_IOC_DISABLE, 0);

	read(fds[0], &cycles_counter, sizeof(uint64_t));
	read(fds[1], &instructions_counter, sizeof(uint64_t));

	fprintf(stderr, "%-20s: %10d\n", "FLOPS", N * FLOP_IN_LOOP);
	fprintf(stderr, "%-20s: %10lu\n", "CPU_CYCLES", cycles_counter);
	fprintf(stderr, "%-20s: %10lu\n", "INSTRUCTIONS", instructions_counter);
	fprintf(stderr, "%-20s: %10lu\n", "TIME_TAKEN(ns)", t2.tv_nsec-t1.tv_nsec);

	printf("%f, %f, %f, %f\n", x,y,z,t);
	close(fds[0]);
	close(fds[1]);
	pfm_terminate();
	return 0;
}
