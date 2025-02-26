#! /bin/python3

events = ["CPU_CYCLES", "INSTRUCTIONS", "TIME_TAKEN(ns)", "L1_CACHE_LOADS", "L1_CACHE_LOAD_MISSES", "L1_CACHE_STORES", "L1_CACHE_STORE_MISSES"]
data = dict()

f = open('memory_bound.data','r')
for i in f.readlines():
    words = i.split()
    if len(words) > 0 and words[0][:-1] in events:
        # print(words[1])
        try:
            (val1, val2) = data[words[0][:-1]]
            val1 += int(words[1])
            val2 += 1
        except:
            val1 = int(words[1])
            val2 = 1
        data[words[0][:-1]] = (val1, val2)

# print(data)


for key in data:
    print(key, data[key][0]/data[key][1])