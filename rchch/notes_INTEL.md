alors du coup faut que je check parce qu'il ya 3 types

core, uncore et offcore

site pour intel : https://perfmon-events.intel.com/ et regarder dans tigerlake

pour trouver des events un peu generiques avec leur code
/sys/devices/cpu/events

sinon on peut utiliser perf list pour trouver la liste de tous les compteurs

ensuite la partie Architecture Performance Monitoring Features de la commande cpuid donne la version du systeme de compteur de perfs du processeur, et plein d'autres infos comme le nombre de "fixed counters" qui sont les compteurs qui calculent une performance fixe certains evenements standard et si ils sont supportes, et il reste aussi le nombre de compteurs programmables

INTEL:
- version 5
- compteurs programmables : 8
- compteurs fixes : 4 (1 inutile) (retired instructions, cpu cycles, unhalted cpu cycles)
- top-down metrics (?) manquants, limite les analyses de "stall"

SNOOPING
cache coherence mechanism used in multi-core processors with shared variable
makes sure variables are always updated without checking the memory
how does it works ?
- core request value 
- other check value 
- if one core has the latest value
  - send updated data
- if no core has the latest value 
  - fetch memory

0x80000008 -> gives informations about address size 
for exemple on my intel cpu i have in eax register 0x3027
  0x27 = 0d39 so physical address size of 39 bits (512Go of physical memory)
  0x30 = 0d48 so logical address size of 48 bits (256To of virtual memory)

0x0A -> Architectural Performance Monitoring
in eax
    [7:0] -> version number
    [15:8] -> number of MSR per logical core 
    [23:16] -> bit width of an IA32_PMCx MSR 
    [31:24] -> number of architecural events 

in edx 
    [7:0] -> number of fixed PMC

non-zero bits in ebx indicates that an architectural event is not supported, the bit index corresponds to a specific event:
    0: UnHalted Core Cycles (umask=00H,event=3CH)
    1: Instruction Retired (umask=00H,event=C0H)
    2: UnHalted Reference Cycles (umask=01H,event=3CH)
    3: LLC Reference (umask=4FH,event=2EH)
    4: LLC Misses (umask=41H,event=2EH)
    5: Branch Instruction Retired (umask=00H,event=C4H)
    6: Branch Misses Retired (umask=00H,event=C5H)
    7: Topdown Slots (umask=01H,event=A4H)
    8: Topdown Backend Bound (umask=02H,event=A4H)
    9: Topdown Bad Speculation (umask=00H,event=73H)
    10: Topdown Frontend Bound (umask=01H,event=9CH)
    11: Topdown Retiring (umask=02H,event=C2H)
    12: LBR Inserts (umask=01H,event=E4H)

pmc introduits avec les processeurs pentium

