#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef AMD 
#define LEAF 0x80000001
#endif

#ifdef INTEL
#define LEAF 0xA
#endif

// AMD 0x80000001
// SSE INSTRUCTIONS SUBSETS
// ECX[6] -> support for SSE4A (EXTRQ, INSERTQ, MOVNTSS and MOVNTSD instructions)
// ECX[11] -> support for AMD XOP ???
// ECX[16] -> support for AMD FMA4 ???
// 
// long mode instructions -> ECX[29]
// prefetch -> ECX[31]
// CMOVEcc -> ECX[15]
// CMPXCHG8B -> ECX[8]
// RDMSR and WRMSR -> ECX[5]


uint32_t eax, ebx, ecx, edx;
char *features_name[32] = {
	"LAHF and SAHF instructions", 
	"Core multi-processing legacy mode", 
	"Secure Virtual Machine feature", 
	"extended APIC register space",
	"LOCK MOV CR0 (means MOV CR8)", 
	"Advanced bit manipulation",
	"SSE4A instruction set", 
	"Misaligned SSE mode", 
	"PREFETCH and PREFETCHW instructions", 
	"OS visible workaround", 
	"Instruction based sampling", 
	"Extended operation support", 
	"SKINIT and STGI support", 
	"Watchdog timer support", 
	"Reserved", 
	"Lightweight profiling", 
	"Four-operand FMA instruction support", 
	"Translation Cache Extension support", 
	"Reserved", 
	"Reserved", 
	"Reserved", 
	"Trailing bit manipulation support", 
	"Topology extension support", 
	"Processor performance counter extension support", 
	"NB performance counter extensions support",
	"Reserved",
	"Data access breakpoint extension",
	"Performance time-stamp counter",
	"L3 performance counter extension support",
	"MWAITX and MONITORX instructions support",
	"Breakpoint Addressing masking extended to bit 31",
	"Reserved"
};


char *pre_defined_architectural_perf_events[13] =
    {
      "UnHalted Core Cycles (umask=00H,event=3CH)",
      "Instruction Retired (umask=00H,event=C0H)",
      "UnHalted Reference Cycles (umask=01H,event=3CH)",
      "LLC Reference (umask=4FH,event=2EH)",
      "LLC Misses (umask=41H,event=2EH)",
      "Branch Instruction Retired (umask=00H,event=C4H)",
      "Branch Misses Retired (umask=00H,event=C5H)",
      "Topdown Slots (umask=01H,event=A4H)",
      "Topdown Backend Bound (umask=02H,event=A4H)",
      "Topdown Bad Speculation (umask=00H,event=73H)",
      "Topdown Frontend Bound (umask=01H,event=9CH)",
      "Topdown Retiring (umask=02H,event=C2H)",
      "LBR Inserts (umask=01H,event=E4H)"
    };
// pour intel 
// fixed counter enumeration
// FxCtr[i]_is_supported := ECX[i] || (EDX[4:0] > i);

void cpuid(uint32_t leaf, uint32_t subleaf) {
    eax = ebx = ecx = edx = 0xDEADBEEF;
    __asm__ volatile ("cpuid"
                      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                      : "a"(leaf), "c"(subleaf));
    printf("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x\n", eax, ebx, ecx, edx);
}

int main(int argc, char** argv) {
	// if (argc > 1) leaf = (int)strtol(argv[1], NULL, 16);
  int features_eax[32];
  int features_ecx[32];
  int features_edx[32];
  
  printf("checking through CPUID.0x%XH\n\n", LEAF);
  cpuid(LEAF, 0); // Example: Get extended feature flags

  #ifdef AMD
	for (int i=0; i<32; i++)
	{
		features[i] = (ecx >> i) & 1; 
	}
	for (int i=31; i>=0; i--) printf("%d ", features[i]);
	printf("\n");
	for (int j=0; j<32; j++)
	{
		printf("%2d : ", j);
		if (features[j]) printf("%-50s supported\n", features_name[j]);
		else printf("%-50s not supported\n", features_name[j]); 
	}
	#endif
	#ifdef INTEL
 	
  for (int i=0; i<32; i++)
		features_ecx[i] = (ecx >> i) & 1;

  for (int i=0; i<32; i++) if (features_ecx[i]) printf("Fixed counter %d supported\n", i);
	
  printf("\n");
  printf("%-40s %d\n", "Performance monitoring version", eax & 0xff);
  printf("%-40s %d\n", "Bit width of an IA32_PMCx MSR", (eax >> 16) & 0xff);
  printf("%-40s %d\n", "Number of general purpose PMC", (eax >> 8) & 0xff);
  printf("%-40s %d\n", "Number of fixed PMC", edx & 0xff);
  int arch_ev = (eax >> 24) & 0xff;
  printf("%-40s %d\n","Number of architectural events", arch_ev);
  

  uint32_t eax_b, ebx_b, ecx_b, edx_b;
  eax_b = eax;
  ebx_b = ebx;
  ecx_b = ecx;
  edx_b = edx;


  printf("\nPREDEFINED ARCHITECTURAL EVENTS : \n");
  for (int i=0; i<arch_ev; i++)
  {
    if ((ebx >> i) & 1) printf("%-50s not supported\n", pre_defined_architectural_perf_events[i]);
    else printf("%-50s supported\n", pre_defined_architectural_perf_events[i]);
  }
	#endif
  return 0;
}
