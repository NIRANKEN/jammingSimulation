#!/bin/sh 

./expxy.sh macro_BI3DN512_DOS.gp 512 64
./expxy.sh macro_BI3DN512_IPR.gp 512 64
./expxy.sh macro_BI3DN512_IPRsmall.gp 512 64
./expxy.sh macro_BI3DN512_checkedsmoothedDOS.gp 512 64
./expxy.sh macro_BI3DN512_scaledDOS.gp 512 64
./expxy.sh macro_BI3DN512_smoothedDOS.gp 512 64
./expx.sh macro_BI3DN512_PR.gp 512 64
./expx.sh macro_BI3DN512_PRsmall.gp 512 64
./expx.sh macro_BI3DN512_PRlarge.gp 512 64
./expx.sh macro_BI3DN512_SmallParticleRatio.gp 512 64
mv new newN64
