if [ "$1" = "AMD" ]; then
	gcc -O2 memory_bound.c -o memory_bound_bench
	for i in {1..10}
	do
		# perf stat -e L1-dcache-loads,L1-icache-loads,L1-dcache-load-misses,L1-icache-load-misses,l2_cache_req_stat.ic_dc_miss_in_l2,l2_cache_req_stat.ic_dc_hit_in_l2 ./memory_bound_bench > /dev/null 2>> m_b_amd.data
		perf stat -e cycles,instructions ./cpu_bound_bench > /dev/null 2>> c_b_amd.data
	done
fi
if [ "$1" = "INTEL" ]; then
  gcc -O2 memory_bound.c -o memory_bound_bench
  echo "" > m_b_intel.data
  for i in {1..10}
  do
    perf stat -e mem_load_retired.l1_hit,mem_load_retired.l1_miss, \
    mem_load_retired.l2_hit,mem_load_retired.l2_miss, \
    mem_load_retired.l3_hit,mem_load_retired.l3_miss \
    ./memory_bound_bench > /dev/null 2>> m_b_intel.data
  done
fi

