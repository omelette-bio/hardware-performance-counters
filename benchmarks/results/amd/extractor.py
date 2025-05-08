events = {"L1-dcache-loads:u","L1-icache-loads:u","L1-dcache-load-misses:u","L1-icache-load-misses:u",
          "l2_cache_req_stat.ic_dc_miss_in_l2:u","l2_cache_req_stat.ic_dc_hit_in_l2:u"}

data = dict()

f = open('m_b_amd.data','r')
print("event, data")
for i in f.readlines():
    words = i.split()
    if (len(words)<2): continue

    if (words[1] in events):
        try:
            data[words[1][:-2]].append("".join(words[0].split(",")))
        except:
            data[words[1][:-2]] = ["".join(words[0].split(","))]

for j in range(10):
    try:
        data["l1-cache-hits"].append(int(data["L1-dcache-loads"][j])+int(data["L1-icache-loads"][j]))
    except:
        #print(f"{data["L1-dcache-loads"][j]} + {data["L1-icache-loads"][j]} = {[int(data["L1-dcache-loads"][j])+int(data["L1-icache-loads"][j])]}")
        data["l1-cache-hits"] = [int(data["L1-dcache-loads"][j])+int(data["L1-icache-loads"][j])]

    try:
        data["l1-cache-misses"].append(int(data["L1-dcache-load-misses"][j])+int(data["L1-icache-load-misses"][j]))
    except:
        # print(f"{data["L1-dcache-load-misses"][j]} + {data["L1-icache-load-misses"][j]} = {[int(data["L1-dcache-load-misses"][j])+int(data["L1-icache-loads"][j])]}")
        data["l1-cache-misses"] = [int(data["L1-dcache-load-misses"][j])+int(data["L1-icache-load-misses"][j])]

for i in data["l1-cache-hits"]:
    print(f"l1-cache-hits : {i}")

for i in data["l1-cache-misses"]:
    print(f"l1-cache-misses : {i}")

for i in data["l2_cache_req_stat.ic_dc_miss_in_l2"]:
    print(f"l2-cache-misses : {i}")

for i in data["l2_cache_req_stat.ic_dc_hit_in_l2"]:
    print(f"l2-cache-hits : {i}")


