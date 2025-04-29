events = ('cycles:u', 'instructions:u', 'L1-dcache-loads:u', 'L1-dcache-load-misses:u', 'l2_cache_req_stat.ls_rd_blk_l_hit_x:u', 'l2_cache_req_stat.ls_rd_blk_c:u', 'cache-misses:u', 'cache-references:u', 'l2_rqsts.miss:u','LLC-store-misses:u', 'LLC-load-misses:u','L1-dcache-stores:u','l2_rqsts.all_rfo:u','l2_rqsts.rfo_miss:u','l2_rqsts.all_demand_data_rd:u','l2_rqsts.demand_data_rd_miss:u','mem_load_retired.l1_hit:u','mem_load_retired.l1_miss:u','mem_load_retired.l2_hit:u','mem_load_retired.l2_miss:u','mem_load_retired.l3_hit:u','mem_load_retired.l3_miss:u')

data=dict()
count=dict()

f = open('m_b_intel.data','r')
print("event, quantity")
for i in f.readlines():
    words = i.split()
    if (len(words) < 2): continue

    if (words[1] in events):
        print(f"{words[1][:-2]}, {"".join(words[0].split(","))}")
