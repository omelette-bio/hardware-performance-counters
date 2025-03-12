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

void cpuid(uint32_t leaf, uint32_t subleaf) {
    __asm__ volatile ("cpuid"
                      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                      : "a"(leaf), "c"(subleaf));
    printf("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x\n", eax, ebx, ecx, edx);
}

int main(int argc, char** argv) {
	// if (argc > 1) leaf = (int)strtol(argv[1], NULL, 16);
    int features[32];
	cpuid(LEAF, 0); // Example: Get extended feature flags
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
    return 0;
}
