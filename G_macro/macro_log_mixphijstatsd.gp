#!/usr/bin/gnuplot -persist
#
#    
#    	G N U P L O T
#    	Version 5.0 patchlevel 5    last modified 2016-10-02
#    
#    	Copyright (C) 1986-1993, 1998, 2004, 2007-2016
#    	Thomas Williams, Colin Kelley and many others
#    
#    	gnuplot home:     http://www.gnuplot.info
#    	faq, bugs, etc:   type "help FAQ"
#    	immediate help:   type "help"  (plot window: hit 'h')
# set terminal qt 0 font "Sans,9"
# set output
unset clip points
set clip one
unset clip two
set bar 1.000000 front
set border 31 front lt black linewidth 1.000 dashtype solid
set zdata 
set ydata 
set xdata 
set y2data 
set x2data 
set boxwidth
set style fill  empty border
set style rectangle back fc  bgnd fillstyle   solid 1.00 border lt -1
set style circle radius graph 0.02, first 0.00000, 0.00000 
set style ellipse size graph 0.05, 0.03, first 0.00000 angle 0 units xy
set dummy N, y
set format x "10^{%L}" 
set format y "10^{%L}" 
set format x2 "% h" 
set format y2 "% h" 
set format z "% h" 
set format cb "% h" 
set format r "% h" 
set timefmt "%d/%m/%y,%H:%M"
set angles radians
set tics back
unset grid
set raxis
set style parallel front  lt black linewidth 2.000 dashtype solid
set key title "" center
set key inside right top vertical Right noreverse enhanced autotitle nobox
set key noinvert samplen 4 spacing 1 width 0 height 0 
set key maxcolumns 0 maxrows 0
set key noopaque
unset label
unset arrow
set style increment default
unset style line
unset style arrow
set style histogram clustered gap 2 title textcolor lt -1
unset object
set style textbox transparent margins  1.0,  1.0 border
unset logscale
set logscale x 10
set logscale y 10
set logscale x2 10
set logscale y2 10
set logscale z 10
set logscale cb 10
set offsets 0, 0, 0, 0
set pointsize 1
set pointintervalbox 1
set encoding default
unset polar
unset parametric
unset decimalsign
unset minussign
set view 60, 30, 1, 1
set samples 100, 100
set isosamples 10, 10
set surface 
unset contour
set cntrlabel  format '%8.3g' font '' start 5 interval 20
set mapping cartesian
set datafile separator whitespace
unset hidden3d
set cntrparam order 4
set cntrparam linear
set cntrparam levels auto 5
set cntrparam points 5
set size ratio 0 1,1
set origin 0,0
set style data points
set style function lines
unset xzeroaxis
unset yzeroaxis
unset zzeroaxis
unset x2zeroaxis
unset y2zeroaxis
set xyplane relative 0.5
set tics scale  1, 0.5, 1, 1, 1
set mxtics default
set mytics default
set mztics default
set mx2tics default
set my2tics default
set mcbtics default
set mrtics default
set xtics border in scale 1,0.5 mirror norotate  autojustify
set xtics  norangelimit autofreq 
set ytics border in scale 1,0.5 mirror norotate  autojustify
set ytics  norangelimit autofreq 
set ztics border in scale 1,0.5 nomirror norotate  autojustify
set ztics  norangelimit autofreq 
unset x2tics
unset y2tics
set cbtics border in scale 1,0.5 mirror norotate  autojustify
set cbtics  norangelimit autofreq 
set rtics axis in scale 1,0.5 nomirror norotate  autojustify
set rtics  norangelimit autofreq 
unset paxis 1 tics
unset paxis 2 tics
unset paxis 3 tics
unset paxis 4 tics
unset paxis 5 tics
unset paxis 6 tics
unset paxis 7 tics
set title "" 
set title  font "" norotate
set timestamp bottom 
set timestamp "" 
set timestamp  font "" norotate
set rrange [ * : * ] noreverse nowriteback
set trange [ * : * ] noreverse nowriteback
set urange [ * : * ] noreverse nowriteback
set vrange [ * : * ] noreverse nowriteback
set xlabel "" 
set xlabel  font "" textcolor lt -1 norotate
set x2label "" 
set x2label  font "" textcolor lt -1 norotate
set xrange [ 100.000 : 10000.0 ] noreverse nowriteback
set x2range [ * : * ] noreverse nowriteback
set ylabel "" 
set ylabel  font "" textcolor lt -1 rotate by -270
set y2label "" 
set y2label  font "" textcolor lt -1 rotate by -270
set yrange [ 0.000100000 : 0.100000 ] noreverse nowriteback
set y2range [ * : * ] noreverse nowriteback
set zlabel "" 
set zlabel  font "" textcolor lt -1 norotate
set zrange [ * : * ] noreverse nowriteback
set cblabel "" 
set cblabel  font "" textcolor lt -1 rotate by -270
set cbrange [ 0.0100000 : 1.00000 ] noreverse nowriteback
set paxis 1 range [ * : * ] noreverse nowriteback
set paxis 2 range [ * : * ] noreverse nowriteback
set paxis 3 range [ * : * ] noreverse nowriteback
set paxis 4 range [ * : * ] noreverse nowriteback
set paxis 5 range [ * : * ] noreverse nowriteback
set paxis 6 range [ * : * ] noreverse nowriteback
set paxis 7 range [ * : * ] noreverse nowriteback
set zero 1e-08
set lmargin  8
set bmargin  -1
set rmargin  -1
set tmargin  -1
set locale "ja_JP.UTF-8"
set pm3d explicit at s
set pm3d scansautomatic
set pm3d interpolate 1,1 flush begin noftriangles noborder corners2color mean
set palette positive nops_allcF maxcolors 0 gamma 1.5 color model RGB 
set palette rgbformulae 7, 5, 15
set colorbox default
set colorbox vertical origin screen 0.9, 0.2, 0 size screen 0.05, 0.6, 0 front  noinvert bdefault
set style boxplot candles range  1.50 outliers pt 7 separation 1 labels auto unsorted
set loadpath 
set fontpath 
set psdir
set fit brief errorvariables nocovariancevariables errorscaling prescale nowrap v5
set grid
set key font "Arial,16"
set tics font "Arial,16"

# f(N)=B-o*log10(N)
# g(N)=A*N**(-o)
# GNUTERM = "qt"
# GPFUN_f = "f(N)=B-o*log10(N)"
# GPFUN_g = "g(N)=A*N**(-o)"
# B = 1.0
# o = 1.0
# fit f(N) './1vs0/PHIJstatinfo.txt' using 1:(log10($4)) via B,o
# A=10**B
# ## Last datafile plotted: "phij_statinfoN1024.txt"
# plot './1vs0/PHIJstatinfo_all.txt' using 1:4 pt 1 ps 3 lw 2 lc 1 notitle,g(N) w l lw 1.5 lc 1 title '1:0'

f31(N)=B31-o31*log10(N)
g31(N)=A31*N**(-o31)
GNUTERM = "qt"
GPFUN_f31 = "f31(N)=B31-o31*log10(N)"
GPFUN_g31 = "g31(N)=A31*N**(-o31)"
B31 = 1.0
o31 = 1.0
fit f31(N) './3vs1/PHIJstatinfo.txt' using 1:(log10($4)) via B31,o31
A31=10**B31
#replot './3vs1/PHIJstatinfo.txt' using 1:4 pt 2 ps 3 lw 2 lc 2 notitle,g31(N) w l lw 1.5 lc 2 title '3:1'
plot './3vs1/PHIJstatinfo.txt' using 1:4 w p ps 3 pt 1 lw 2 lc rgb '#00994d' notitle,g31(N) w l lw 1.5 lc rgb '#00994d' title '3:1'

f11(N)=B11-o11*log10(N)
g11(N)=A11*N**(-o11)
GNUTERM = "qt"
GPFUN_f11 = "f11(N)=B11-o11*log10(N)"
GPFUN_g11 = "g11(N)=A11*N**(-o11)"
B11 = 1.0
o11 = 1.0
fit f11(N) './1vs1/PHIJstatinfo.txt' using 1:(log10($4)) via B11,o11
A11=10**B11
replot './1vs1/PHIJstatinfo.txt' using 1:4 w p pt 2 ps 3 lw 2 lc rgb '#ff7f00' notitle,g11(N) w l lw 1.5 lc rgb '#ff7f00' title '1:1'

f13(N)=B13-o13*log10(N)
g13(N)=A13*N**(-o13)
GNUTERM = "qt"
GPFUN_f13 = "f13(N)=B13-o13*log10(N)"
GPFUN_g13 = "g13(N)=A13*N**(-o13)"
B13 = 1.0
o13 = 1.0
fit f13(N) './1vs3/PHIJstatinfo.txt' using 1:(log10($4)) via B13,o13
A13=10**B13
replot './1vs3/PHIJstatinfo.txt' using 1:4 w p pt 4 ps 3 lw 2 lc rgb '#b366ff' notitle,g13(N) w l lw 1.5 lc rgb '#b366ff' title '1:3'


#replot (N<10**3?NaN:(N>5*10**3?NaN:(10**(-2))*(0.5*N*10**(-3))**(-0.55))) w l lw 1.5 lc rgb 'black' notitle
replot (2*10**(-3))*(0.5*N*10**(-3))**(-0.55) w l lw 1.5 lc rgb '#3f3f3f' dt 2 notitle

#    EOF
