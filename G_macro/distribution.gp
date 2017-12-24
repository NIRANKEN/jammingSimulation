clear
reset
set key off
set border 3

# Add a vertical dotted line at x=0 to show centre (mean) of distribution.
set yzeroaxis

# Each bar is half the (visual) width of its x-range.
#set boxwidth 0.05 absolute
#set style fill solid 1.0 noborder

set xr[0.62:0.67]
set yr[0:]
set grid

bin_width = 0.00075;

bin_number(x) = floor(x/bin_width)
rounded(x) = bin_width * ( bin_number(x) + 0.5 )
N64=20735
N128=4200
N256=1131
N512=320
N1024=64
N2048=64
#N4096=10

plot './N64/1:1/PHIJ_0524_3DBIN64.txt' using (rounded($2)):(1.0/N64) smooth frequency  w lp ps 0.5
replot './N128/1:1/PHIJ_0524_3DBIN128.txt' using (rounded($2)):(1.0/N128) smooth frequency w lp ps 0.5
replot './N256/1:1/PHIJ_0524_3DBIN256.txt' using (rounded($2)):(1.0/N256) smooth frequency w lp ps 0.5 
replot './N512/1:1/PHIJ_0524_3DBIN512.txt' using (rounded($2)):(1.0/N512) smooth frequency w lp ps 0.5 
replot '~/KenkyuData/data1203/SAMPLE0524_N1024/1by1/PHIJ_0524_3DBIN1024.txt' using (rounded($2)):(1.0/N1024) smooth frequency w lp ps 0.5 
replot '~/KenkyuData/data1203/SAMPLE0524_N2048/1by1/PHIJ_0524_3DBIN2048.txt' using (rounded($2)):(1.0/N2048) smooth frequency w lp ps 0.5 
#replot '~/KenkyuData/data1203/SAMPLE0524_N4096/1by1/PHIJ_0524_3DBIN4096.txt' using (rounded($2)):(1.0/N4096) smooth frequency w lp ps 0.5 
