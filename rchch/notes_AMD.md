caches-misses caches-references pour AMD fait souvent reference au cache L3, puisqu'il compte les defauts de caches qui partent ensuite en memoire

cpuid
  - instruction assembleur pour avoir des informations sur le processeur
  - cmd pour voir quels C.P sont supportes

fonction 0x80000001 avoir infos sur proc extensives avec 4 registres et ECX c'est celui qu'on veut

bit 23 -> si 1 on a 6 core C.P
bit 24 -> si 1 on a 4 Northbridge C.P
bit 25 -> si 1 on a 4 C.P spe au cache L2
