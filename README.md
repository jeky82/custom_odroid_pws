Welcome to custom_odroid_pws Repository
=================
FOR ODROID U2

1. DESCRIPTION
idle.c contains a little program to monitor the idle status of 
Odroid system. The idle status is monitored from the X server
trough the xscreensaver library. Also the average load of the
processor is taken into account.
When the system is detected ad in idle the all the 4 cores are
blocked at frequency of 200 Mhz. Instead when the system is detected
as not in idle the frequency is scaled between 1.4Ghz and 1.92Ghz
using the ondemand governator. 

2. INSTALLATION

2.1 clone the git

git clone https://github.com/jeky82/custom_odroid_pws.git

cd custom_odroid_pws

2.2 install necessary libray

sudo apt-get install libxss-dev libx11-dev cpufrequtils

2.3 compile

gcc -o idle idle.c -lX11 -lXss

2.4 copy in a bin directory

sudo cp ./idle /bin/

2.5 add it in rc.local

sudo gedit /etc/rc.local

2.6 add the line

idle > /dev/null