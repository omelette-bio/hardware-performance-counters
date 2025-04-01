## cpuid
instruction x86 qui permet d'avoir plein d'informations sur le processeur que l'on utilise, et demande un code, une `leaf` pour aller dans un repertoire specifique d'informationsqui nous donnera des informations dans quatres registres eax ebx ecx edx, sous la forme de nombres de 32 bits hexadecimaux.

chaque bit correspond a une fonctionnalite decrite dans le manuel AMD(AMD64 Architecture Programmer’s Manual Volume 3: General-Purpose and System Instructions)/INTEL

ce qui nous interesse dans ce projet c'est la `leaf` 0x80000001 du registre `ECX` sur `AMD` et la `leaf` 0x0000000A sur `INTEL`

### pour AMD 
elle nous donne des informations sur, par exemple, le support d'ensembles d'instructions comme le SSE4A (streaming/applications multimedia processeur SIMD)
ce qui est important ici, ce sont les bits 23, 24 et 28, qui nous donnent respectivement le support de compteurs de performances classiques, nb et L3, j'ai vu aussi cache l2 mais j'ai pas retrouve l'info.

### pour INTEL
je sais pas en sah

## trucs un peu random

`PFM_OS_PERF_EVENT` tells encoding function to use the Linux Perf API to encode

## bordel que je dois checker
linux perf API -> c'est bien que j'en entende parler que maintenant HAHAAHAHHA
privilege level mask -> ????
regarder les MSRs


## choses que je dois savoir en plus
- est-ce que c'est bien si je fais des parralleles avec mon proc dans le rapport

## linux perf API 
propose une API qui peut etre utilisee en ligne de commande avec perf ou en C avec libperf

Events come in two flavors: counting and sampled.  A counting event is one that
       is  used  for  counting the aggregate number of events that occur.  In general,
       counting event results are gathered with a read(2) call.  A sampling event  pe‐
       riodically  writes  measurements  to  a  buffer  that  can then be accessed via
       mmap(2).


## MSRs 
intel:
    nombre fini de registres de selection d'events (IA32_PERFEVTSELx)
    resultats dans les registres (IA32_PMCx)
    les adresses restent les memes pour chaque archi
