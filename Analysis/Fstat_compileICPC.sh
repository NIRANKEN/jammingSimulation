#!/bin/sh

icpc -fast TestSampleTable.cpp -o F_sample
icpc -fast TestExtractEIG2\(phi-phij\).cpp -o F_phiens
icpc -fast TestOutputEIG_binfreq.cpp -o F_binstat
icpc -fast TestOutputPHIJ\(cumdist\).cpp -o F_phijcum
icpc -fast TestOutputCharacteristicFrequency.cpp -o F_cfreq
icpc -fast TestOutputInvariantFrequency.cpp -o F_ifreq
icpc -fast TestOutputCharacteristicFrequency3.cpp -o F_cfreq2
icpc -fast TestOutputAdditionalEIG\(phi-phij\).cpp -o F_addBIN
icpc -fast TestOutputGaussianSmoothing.cpp -o F_smooth 
icpc -fast TestOutputDeriveEffectiveCF.cpp -o F_ECF 
