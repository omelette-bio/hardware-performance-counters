# PROJET TUTORAT S2 M1 INFORMATIQUE

This project is about Hardware Performance Counters

## Goals

- Discover the different events available on a cpu (in my case, AMD ryzen 5 3600X and INTEL core i5-1135G7)
- Do some memory-bound and cpu-bound benchmarks using either the perf tool on linux or the libpfm c library
- Discover how HPC works (but maybe im pushing the project a bit too far)

## What has been done 

- Small program capable of analysing HPC capabilities on a cpu 
- Small program capable of analysing the PMUs of a cpu and the events attached to it 
- What is libpfm (only on the surface)
- Which registers are involved on AMD cpus 
- Which informations gives cpuid instruction on intel/amd 
- Benchmarks using perf command (only with memory-bound)

## Sources

- Manuels AMD 
    - Processor Programming Reference for AMD Family 17h Model A0h, Aout 2022
    - AMD64 Architecture Programmer's Manual Volume 2 : System Programming and Volume 3 : General-Purpose and System Instructions
- Manuel INTEL 
    - Intel 64 and IA-32 Architectures Software Developer's Manual


