caches-misses caches-references pour AMD fait souvent reference au cache L3, puisqu'il compte les defauts de caches qui partent ensuite en memoire

cpuid
  - instruction assembleur pour avoir des informations sur le processeur
  - cmd pour voir quels C.P sont supportes

fonction 0x80000001 avoir infos sur proc extensives avec 4 registres et ECX c'est celui qu'on veut

bit 23 -> si 1 on a 6 core C.P
bit 24 -> si 1 on a 4 Northbridge C.P
bit 25 -> si 1 on a 4 C.P spe au cache L2

pour citer manuel 
AMD64 architecture programmer's manual volume 2 : system programming may 2024
CPUID Fn8000_0001_ECX[PerfCtrExtCore] = 1 indicates support for the six architecturally defined extended core performance counters and their associated event-select registers. 
CPUID Fn8000_0001_ECX[PerfCtrExtNB] = 1 indicates support for the four architecturally defined Northbridge performance counter / event-select pairs
CPUID Fn8000_0001_ECX[PerfCtrExtL2I] = 1 indicates support for the four architecturally defined L2 cache performance counter / event-select pairs.


mon cpu :
supporte 6 core CP 
supporte 4 Northbridge CP 


Core performance counters are used to count processor core events, such as data-cache misses, or the
duration of events, such as the number of clocks it takes to return data from memory after a cache miss.
During event counting, hardware increments a counter each time it detects an occurrence of a specified
event. During duration measurement, hardware counts the number of processor clock cycles required
to complete a specific hardware function.

ok definitivement pas mesure de cache l3 
-> information erronee de la part de CPUID Fn8000_0001_ECX[PerfCtrExtL3], peut-etre parce que le manuel date de apres la sortie de mon cpu, ou le micro-logiciel de mon cpu est pas a jour.


