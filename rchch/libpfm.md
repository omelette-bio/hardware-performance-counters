# libpfm

comment utiliser libpfm

- `pfm_initialize()` -> permet d'initialiser la librairie, checker si != PFM_SUCCESS, sinon c'est gud

- `perf_event_attr` -> struct qui permet de stocker les parametres des compteurs de perf 
- `pfm_perf_encode_arg_t` -> utilise pour permettre de traduire un nom d'event en perf event valide 


`pfm_get_os_event_encoding(event, PFM_PLM3, PFM_OS_PERF_EVENT, &arg)`
-> arg est de type `pfm_perf_encode_arg_t`, qui contient un `perf_event_attr`, qui va donc etre modifie pour avoir les parametres necessaires a la mesure de event.

`perf_event_open(perf_event_attr A, int B, int C, int D, int E)`
- `A`: event configuration
- `B`: which cpu to monitor (should be good to use taskset)
- `C`: which process to mesure performances (-1 to all)
- `D`: grouping (-1 for no group)
- `E`: flags

checker en profondeur ce que fait ioctl
