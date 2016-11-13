reset

pi = 5
eps = 1
f = 4

set logscale y
plot[][0.0001:]\
"pSwitchingTime.dat" u ($1):($2/0.1) w lp
