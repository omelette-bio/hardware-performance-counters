#!/bin/bash

cpu_vendor=$(grep "vendor_id" /proc/cpuinfo | head -1 | awk '{print $3}')

if [[ "$cpu_vendor" == "GenuineIntel" ]]; then
	echo "Compiling for INTEL cpu"
	gcc HPC_analysis.c -D INTEL -o HPC_analysis
elif [[ "$cpu_vendor" == "AuthenticAMD" ]]; then
	gcc HPC_analysis.c -D AMD -o HPC_analysis
	echo "Compiling for AMD cpu"
else
	echo "Unknown cpu vendor :("
fi
