clear
reset
#set key off
set border 3
set key font "Arial,16"
set tics font "Arial,16"
set key left top
# Add a vertical dotted line at x=0 to show centre (mean) of distribution.
set yzeroaxis

# Each bar is half the (visual) width of its x-range.
#set boxwidth 0.05 absolute
#set style fill solid 1.0 noborder

set xr[0.635:0.66]
set yr[0:1]
set grid
se xlabel '{/=24 jamming point}'
se xlabel offset 0,-1
se ylabel '{/=24 distribution}'
se ylabel offset -1.5,0
se lmargin 11
se bmargin 5

bin_width = 0.00075;
#bin_width = 0.0005;

bin_number(x) = floor(x/bin_width)
rounded(x) = bin_width * ( bin_number(x) + 0.5 )
#N64=20735
N128=4200
N256=1131
N512=320
N1024=64
N2048=64
N4096=30

#plot './N64/1:1/PHIJ_0524_3DBIN64.txt' using (rounded($2)):(1.0/N64) smooth frequency  w lp ps 0.7 lw 4 lc rgb '#320000'
plot './N128/1:1/PHIJ_0524_3DBIN128.txt' using (rounded($2)):(1.0/N128) smooth frequency w lp ps 0.7 lw 4 lc rgb '#003300' title '  N128'
replot './N256/1:1/PHIJ_0524_3DBIN256.txt' using (rounded($2)):(1.0/N256) smooth frequency w lp ps 0.7 lw 4 lc rgb '#2e3c12' title '  N256'
replot './N512/1:1/PHIJ_0524_3DBIN512.txt' using (rounded($2)):(1.0/N512) smooth frequency w lp ps 0.7 lw 4 lc rgb '#45401b' title '  N512'
replot '~/KenkyuData/data1203/SAMPLE0524_N1024/1by1/PHIJ_0524_3DBIN1024.txt' using (rounded($2)):(1.0/N1024) smooth frequency w lp ps 0.7 lw 4 lc rgb '#734a2e' title '  N1024
replot '~/KenkyuData/data1203/SAMPLE0524_N2048/1by1/PHIJ_0524_3DBIN2048.txt' using (rounded($2)):(1.0/N2048) smooth frequency w lp ps 0.7 lw 4 lc rgb '#a15340' title '  N2048'
replot '/home/y-kimura/KenkyuData/data1227/1by1/PHIJ_0524_3DBIN4096.txt' using (rounded($2)):(1.0/N4096) smooth frequency w lp ps 0.7 lw 4 lc rgb '#cf5c52' title '  N4096'
#replot './PHIJ_0524_3DBIN8192.txt' using (rounded($2)):(1.0/N4096) smooth frequency w lp ps 0.7 lw 4 lc rgb '#ff6666'
# plot './N64/1:1/PHIJ_0524_3DBIN64.txt' using (rounded($2)):(1.0/N64) smooth frequency w filledcurve lc rgb ''
# replot './N128/1:1/PHIJ_0524_3DBIN128.txt' using (rounded($2)):(1.0/N128) smooth frequency w filledcurve lc rgb '#491717'
# replot './N256/1:1/PHIJ_0524_3DBIN256.txt' using (rounded($2)):(1.0/N256) smooth frequency w filledcurve lc rgb '#5b2929'
# replot './N512/1:1/PHIJ_0524_3DBIN512.txt' using (rounded($2)):(1.0/N512) smooth frequency w filledcurve lc rgb '#6b3939'
# replot '~/KenkyuData/data1203/SAMPLE0524_N1024/1by1/PHIJ_0524_3DBIN1024.txt' using (rounded($2)):(1.0/N1024) smooth frequency w filledcurve lc rgb '#784646'
#replot '~/KenkyuData/data1203/SAMPLE0524_N2048/1by1/PHIJ_0524_3DBIN2048.txt' using (rounded($2)):(1.0/N2048) smooth frequency w filledcurve lc rgb '#8a5858'

# dark green to light red (pink)
#003300
#2e3c12
#45401b
#734a2e
#a15340
#cf5c52
#ff6666

# red to yellow gradient
#dc0000
#dc2e00
#dc4500
#dc7f00
#dcac00
#dcdc00

# brown gradient
#320000
#491717
#5b2929
#6b3939
#784646
#8a5858
#9b6969
#ad7b7b
#c89696

# red -> green
#
