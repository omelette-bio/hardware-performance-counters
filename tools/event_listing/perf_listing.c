
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <perfmon/pfmlib.h>

int main() {
    pfm_initialize();

    pfm_pmu_info_t pinfo;
    pfm_event_info_t einfo;
    int pmu;
    int event, ret;
	int i;

	//list_pmu_events(445);
	memset(&einfo, 0, sizeof(einfo));
	memset(&pinfo, 0, sizeof(pinfo));

	einfo.size = sizeof(einfo);
	pinfo.size = sizeof(pinfo);
	
    for (pmu = 0; pmu < PFM_PMU_MAX; pmu++) {
        ret = pfm_get_pmu_info(pmu, &pinfo);
        if (ret != PFM_SUCCESS || !pinfo.is_present)
            continue;

		printf("EVENT LIST FOR %s (%d) :\n", pinfo.name, pmu);
		for (i = pinfo.first_event; i != -1; i = pfm_get_event_next(i)) 
		{
			ret = pfm_get_event_info(i, PFM_OS_PERF_EVENT, &einfo);
			if (ret != PFM_SUCCESS)
				errx(1, "cannot get event info");

			if (pfm_find_event(einfo.name) && pinfo.is_present)
				printf("  %s\n	  (%s)\n",einfo.name,einfo.desc);
		}
		printf("\n");
	}

    return 0;
}


