#include <stdio.h>
#include <stdint.h>

void cpuid(uint32_t leaf, uint32_t subleaf) {
    uint32_t eax, ebx, ecx, edx;
    __asm__ volatile ("cpuid"
                      : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                      : "a"(leaf), "c"(subleaf));
    printf("EAX: 0x%x, EBX: 0x%x, ECX: 0x%x, EDX: 0x%x\n", eax, ebx, ecx, edx);
}

int main() {
    cpuid(0x0000000A, 0); // Example: Get extended feature flags
    return 0;
}
