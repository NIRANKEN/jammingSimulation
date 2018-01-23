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
set terminal qt 0 font "Sans,9" size 600,800
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
set dummy x, y
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
set grid nopolar
set grid xtics nomxtics ytics nomytics noztics nomztics \
 nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
set grid layerdefault   lt 0 linewidth 0.500 dashtype solid,  lt 0 linewidth 0.500 dashtype solid
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
set xlabel  font "" textcolor lt -1 norotate
set x2label "" 
set x2label  font "" textcolor lt -1 norotate
set xrange [ 1.00000e-06 : 1.00000 ] noreverse nowriteback
set x2range [ 1.00000e-06 : 1.00000 ] noreverse nowriteback
set ylabel "{/=30 {/Arial-Italic D({/Symbol w})}}" 
set ylabel  offset character -3, 0, 0 font "" textcolor lt -1 rotate by -270
set y2label "" 
set y2label  font "" textcolor lt -1 rotate by -270
set yrange [ 0.0100000 : 100.000 ] noreverse nowriteback
set y2range [ 0.0100000 : 100.000 ] noreverse nowriteback
set zlabel "" 
set zlabel  font "" textcolor lt -1 norotate
set zrange [ * : * ] noreverse nowriteback
set cblabel "" 
set cblabel  font "" textcolor lt -1 rotate by -270
set cbrange [ * : * ] noreverse nowriteback
set paxis 1 range [ * : * ] noreverse nowriteback
set paxis 2 range [ * : * ] noreverse nowriteback
set paxis 3 range [ * : * ] noreverse nowriteback
set paxis 4 range [ * : * ] noreverse nowriteback
set paxis 5 range [ * : * ] noreverse nowriteback
set paxis 6 range [ * : * ] noreverse nowriteback
set paxis 7 range [ * : * ] noreverse nowriteback
set zero 1e-08
set lmargin  13
set bmargin  5
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
GNUTERM = "qt"
x = 0.0

se multi layout 3,1
#set size ratio 2
set bmargin 1
unset format x ""
unset xlabel
## Last datafile plotted: "./6.5_6.0/CharacteristicFrequency2_SM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt"
plot 11.772*((1.0/0.0103451)*x)**2 w l lw 2 lt 0 notitle, 11.772*((1.0/5.64387e-05)*x)**2 w l lw 2 lt 0 notitle,'./1.5_1.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00e150' notitle, './2.0_1.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00d65b' notitle, './2.5_2.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00cb66' notitle, './3.0_2.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00c170' notitle, './3.5_3.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00b67b' notitle, './4.0_3.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#009b86' notitle, './4.5_4.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#009f92' notitle, './5.0_4.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#00939e' notitle, './5.5_5.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#0089a8' notitle, './6.0_5.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#007cb5' notitle, './6.5_6.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:11 w lp pt 7 ps 0.5 lc rgb '#0050e1' notitle, './1.5_1.0/CharacteristicFrequency2_SM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 2:3 w lp pt 11 ps 3 lc rgb '#00e150' notitle, './6.5_6.0/CharacteristicFrequency2_SM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 2:3 w lp pt 11 ps 3 lc rgb '#0050e1' notitle

# 要cfreq値設定!!!!
set yrange [ 0.00010000 : 1.00000 ] noreverse nowriteback
#set y2range [ 0.000100000 : 1.00000 ] noreverse nowriteback
set ylabel "{/=30 {/Arial-Italic Y({/Symbol w})}}"
#set tmargin -3 
plot './1.5_1.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00e150' notitle, './2.0_1.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00d65b' notitle, './2.5_2.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00cb66' notitle, './3.0_2.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00c170' notitle, './3.5_3.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00b67b' notitle, './4.0_3.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#009b86' notitle, './4.5_4.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#009f92' notitle, './5.0_4.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#00939e' notitle, './5.5_5.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#0089a8' notitle, './6.0_5.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#007cb5' notitle, './6.5_6.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:2 w lp pt 7 ps 0.5 lc rgb '#0050e1' notitle, 1.0/2048 w l lt 0 lw 5 lc rgb 'gray' notitle

set format x "10^{%L}"
unset format y "% h"
set xlabel "{/=30 {/Arial-Italic {/Symbol w}}}"
set ylabel "{/=30 {/Arial-Italic SPR({/Symbol w})}}"
set bmargin  5
unset log y
set yrange [ 0.00000 : 1.00000 ] noreverse nowriteback
set y2range [ * : * ] noreverse nowriteback
plot './1.5_1.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00e150' notitle, './2.0_1.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00d65b' notitle, './2.5_2.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00cb66' notitle, './3.0_2.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00c170' notitle, './3.5_3.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00b67b' notitle, './4.0_3.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#009b86' notitle, './4.5_4.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#009f92' notitle, './5.0_4.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#00939e' notitle, './5.5_5.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#0089a8' notitle, './6.0_5.5/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#007cb5' notitle, './6.5_6.0/AdditionalSM_EIGEnsAve_BR0.05_0524_3DBIN2048.txt' using 1:9 w lp pt 7 ps 0.5 lc rgb '#0050e1' notitle

unse multi

#    EOF