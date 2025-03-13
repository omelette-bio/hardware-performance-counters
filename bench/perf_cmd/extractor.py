events = ('L1-dcache-loads:u', 'L1-dcache-load-misses:u', 'l2_cache_req_stat.ls_rd_blk_l_hit_x:u', 'l2_cache_req_stat.ls_rd_blk_c:u', 'cache-misses:u', 'cache-references:u')

data=dict()
count=dict()

f = open('memory_bound_AMD.data','r')
for i in f.readlines():
    words = i.split()
    if (len(words) < 2): continue

    if (words[1] in events):
        print(f"{words[1]} : {words[0]}")
