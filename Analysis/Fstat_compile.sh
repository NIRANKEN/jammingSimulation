#!/bin/sh

g++ TestSampleTable.cpp -o F_sample
g++ TestExtractEIG2\(phi-phij\).cpp -o F_phiens
g++ TestOutputEIG_binfreq.cpp -o F_binstat
g++ TestOutputPHIJ\(cumdist\).cpp -o F_phijcum
g++ TestOutputCharacteristicFrequency.cpp -o F_cfreq
g++ TestOutputInvariantFrequency.cpp -o F_ifreq
g++ TestOutputCharacteristicFrequency3.cpp -o F_cfreq2
g++ TestOutputAdditionalEIG\(phi-phij\).cpp -o F_addBIN 
g++ TestOutputGaussianSmoothing.cpp -o F_smooth 
g++ TestOutputDeriveEffectiveCF.cpp -o F_ECF 
