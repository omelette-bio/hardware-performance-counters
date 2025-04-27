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


## utiliser les compteurs de perf
en gros pour compter un evenement
- remplir les informations de l'evenement que l'on souhaite mesurer grace aux event select msrs (IA32_PERFEVTSELx sur INTEL et jsplu sur AMD)
- ecrire "1" dans le bit EN avec l'instruction WRMSR, la mesure commence a la fin de l'execution de l'instructions
- si on veut arreter, ecrire "0" dans le bit EN avec l'instruction WRMSR.


## environnement d'experience
### intel 
nom : 11th Gen Intel(R) Core(TM) i5-1135G7 @ 2.40 GHz

adress size : 39 bits physical, 48 bits virtual

cores : 4 physical, 8 logical

### amd
nom : AMD Ryzen 5 3600X

adress size : 48 bits physical, 48 bits virtual

cores : 6 physical, 12 logical


## j'ai compris ???

en gros avec libpfm et meme les compteurs de perf en general

maniere "bas niveau" de demarrer un compteur de perf :
    - on met les infos necessaires dans le MSR event select
    - on met a 1 le bit EN (enable)
    - au cycle juste apres la fin de l'instruction WRMSR, on commence a compter

le kernel linux donne acces au linux perf api, qui donne une abstraction afin de pas s'embeter parce que c'est **CHIANT**
a travers l'appel systeme `perf_event_open()`, le systeme d'exploitation recupere les parametres de l'evenement comme son code, son umask et ensuite va attribuer un `fd` a ce compteur, ce fd est le "userspace" qui permet d'interagir avec le kernel

quand on appelle `perf_event_open()`, le kernel:
    - cree un objet "perf_event" en memoire
    - le lie a un compteur PMU
    - et renvoie un descripteur de fichier

grace a ioctl, on pourra:
    - reset le compteur avec l'appel `ioctl(fd, PERF_EVENT_IOC_RESET, 0);`
    - demarrer le compteur avec l'appel `ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);`
    - arreter le compteur avec l'appel `ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);`

apres lire avec `read(fd, &var, sizeof(uint64_t))`

probleme : encoder l'event et ses parametres 

## code et umask

Unit mask (UMASK) field (bits 8 through 15) — These bits qualify the condition that the selected event
logic unit detects. Valid UMASK values for each event logic unit are specific to the unit.

Event select field (bits 0 through 7) — Selects the event logic unit used to detect microarchitectural
conditions (see Table 21-3, for a list of architectural events and their 8-bit codes). The set of values for this field
is defined architecturally; each value corresponds to an event logic unit for use with an architectural
performance event

## plan ?

- environnement d'experience
- c'est quoi un compteur materiel de performances (dans l'intro ou l'abstract)


HPCs ON X86 CPUs
- key components
- encode events
- start the mesurements
  - low-level
  - linux perf api
  - libpfm
- HPC sur intel
- HPC sur AMD
  

TROUVER LES COMPTEURS COMPATIBLES
- commande cpuid
- comment lister les evenements materiels disponibles


BENCHMARKs
- benchmarks avec commande perf
    - linux perf api
    - resultats
- benchmarks plus precis : libpfm
    - presentation libpfm
    - resultats


