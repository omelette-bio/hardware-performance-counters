
## cpuid
instruction x86 qui permet d'avoir plein d'informations sur le processeur que l'on utilise, et demande un code, une `leaf` pour aller dans un repertoire specifique d'informationsqui nous donnera des informations dans quatres registres, sous la forme de nombres de 32 bits hexadecimaux.

chaque bit correspond a une fonctionnalite decrite dans le manuel AMD(AMD64 Architecture Programmer’s Manual Volume 3: General-Purpose and System Instructions)/INTEL

ce qui nous interesse dans ce projet c'est la `leaf` 0x80000001 du registre `ECX` sur `AMD` et la `leaf` 0x0000000A sur `INTEL`

### pour AMD 
elle nous donne des informations sur, par exemple, le support d'ensembles d'instructions comme le SSE4A (streaming/applications multimedia processeur SIMD)
ce qui est important ici, ce sont les bits 23, 24 et 28, qui nous donnent respectivement le support de compteurs de performances classiques, nb et L3, j'ai vu aussi cache l2 mais j'ai pas retrouve l'info.

### pour INTEL
je sais pas en sah
