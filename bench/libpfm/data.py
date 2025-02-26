#! /bin/python3

avg_cycles = 0
c_cycles = 0
avg_time = 0
c_time = 0
avg_instructions = 0
c_instructions = 0

f = open('cpu_bound.data','r')
for i in f.readlines():
    words = i.split()
    if len(words) > 0 and words[0][:-1] == "CPU_CYCLES":
        avg_cycles += int(words[1])
        c_cycles += 1
    if len(words) > 0 and words[0][:-1] == "INSTRUCTIONS":
        avg_instructions += int(words[1])
        c_instructions += 1
    if len(words) > 0 and words[0][:-1] == "TIME_TAKEN(ns)":
        avg_time += int(words[1])
        c_time += 1

print(avg_cycles/c_cycles)
print(avg_instructions/c_instructions)
print(avg_time/c_time)
