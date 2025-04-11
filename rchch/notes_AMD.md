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

2 types de MSR :
- Core::X86::Msr::PERF_CTL : definissent l'event qui doit etre mesure, est lie avec un registre Core::X86::Msr::PERF_CTR et sont notes MSRC001_02X[A,8,6,4,2,0]
- Core::X86::Msr::PERF_CTR : sont les registres qui comptent les events, donc litteralement les compteurs materiels de performance, ils sont notes MSRC001_02X[B,9,7,5,3,1]

X correspond au groupe d'evenements, par exemple 0 est le groupe des evenements classiques, nombre de cycles, instructions, branchements, ....
les groupes sont definis comme dans la partie avec CPUID.

et pour chaque groupe, les PERF_CTL MSRs ne contiennent pas la meme information, (et la dans le rapport montrer les tables faites pour chaque (?) PERF_CTL MSR).

compteur demarre quand le bit EN est mit a 1 avec l'instruction WRMSR, le comptage demarre quand l'instruction a fini.
les infos doivent etre mise a jour avant ou pendant l'ecriture du bit.
fin du comptage quand bit remis a 0.

## Comment ca fonctionne ?



## IBS

methode de mesure exclusive a amd
compatibilite avec IBS marquee dans le bit 10 de CPUID[800000001].ECX
arrive pas a marcher avec perf stat mais amd uprof oui

- technique de profilage qui permet d'avoir beaucoup d'informations
- identifie les instructions qui n'utilisent pas le pipeline et la hierarchie memoire au max des capacites
- deux sampling : op sampling et fetch sampling

### fetch

- addresse de fetch
- est-ce que le fetch a fini ou non
- est-ce que le fetch a fait defaut dans le cache instruction
- est-ce que le fetch a fait defaut dans le niveau 1 ou 2 du ITLB