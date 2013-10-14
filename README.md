Welcome to custom_odroid_pws Repository
=================

(FOR ODROID U2)

==== DESCRIPTION ====

idle.c contains is little program to monitor the idle status of 
Odroid system. The idle status is monitored from the X server
trough the xscreensaver library. Also the average load of the
processors in the last minute is taken into account to detect the
idle status of the system.
When the system is detected in idle the default policy consists
into block all the 4 cores at frequency of 200 Mhz. Instead when 
the system is detected as not in idle the frequency is setted
between 1.4Ghz and 1.92Ghz using the ondemand governator. 


==== INSTALLATION ====

2.1 clone the git
> git clone https://github.com/jeky82/custom_odroid_pws.git

> cd custom_odroid_pws

2.2 install the necessary libraries
> sudo apt-get install libxss-dev libx11-dev cpufrequtils

2.3 compile and install
> make

> sudo make install

2.4 add it to rc.local to enable idle monitor to bed started when logged
> sudo gedit /etc/rc.local

2.5 add the line
> idle > /dev/null
