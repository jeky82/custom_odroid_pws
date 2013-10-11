#include <X11/extensions/scrnsaver.h>
#include <X11/Xlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void set_powersave(int pws_flag){
	
	if (pws_flag){
		// downclock to 300-800 Mhz
		system("cpufreq-set --min 200Mhz --max 200Mhz --governor ondemand");
		//system("cpufreq-set --min 200Mhz --governor powersave");
		
		// bump up or shutdown the cores that you want
		system("echo 1 > /sys/devices/system/cpu/cpu1/online");
		system("echo 1 > /sys/devices/system/cpu/cpu2/online");
		system("echo 1 > /sys/devices/system/cpu/cpu3/online");
		
	} else{
		// with these setting all the cores are automatically bumped up 
		//system("cpufreq-set --min 1.4Ghz --max 1.4Ghz --governor performance");
		system("cpufreq-set --min 1.4Ghz --max 2.0Ghz --governor ondemand"); //<-- overclock (uncomment to enalbe it, and comment previus line)
	}
	
}
 
unsigned long int get_idle(XScreenSaverInfo *info, Display *display) {
	// avg cpu load in the last 1,5,15 minutes	
	double load[3];

	// until xbmc have problem with xbmc this check is necessary
	//if (0 == system("pidof -x xbmc > /dev/null")){
	//	printf("xbmc");
	//	return 0;
	//}
	          
	if (getloadavg(load, 3) != -1) {     
	 if (load[0] >= 0.5){
		return 0;
	 }  
	}

	//display could be null if there is no X server running
	if (info == NULL || display == NULL) {
	    return -1;
	}

	//X11 is running, try to retrieve info
	if (XScreenSaverQueryInfo(display, DefaultRootWindow(display), info) == 0) {
		return -1;
	}

	return info->idle;  
}

int main(int argc, char *argv[]) {

XScreenSaverInfo *info = XScreenSaverAllocInfo();
Display *display = XOpenDisplay(NULL); //empty argument means to use $DISPLAY variable
unsigned long int time_idle;
int time_pws = 10*60*1000; // time to wait to go in power save (10 minutes)

	if(fork() == 0) {
		while(1) {
			
			time_idle = get_idle(info,display); // get idle time in milliseconds
			printf("%lu ms\n", time_idle);
			if (time_idle < time_pws ){
				sleep((time_pws - time_idle)/1000 + 5); // add 5 seconds of delay to prevent very little difference
			} else{
				// GO IN POWER SAVE MODE
				printf("GO IN POWER SAVE %lu ms\n", time_idle);
				set_powersave(1);

				setpriority(PRIO_PROCESS, 0, -15); // change priority to low
				while (time_idle >= time_pws ){ // check until we have to exit from the power saving mode
					sleep(5);
					time_idle = get_idle(info,display);
				}
				setpriority(PRIO_PROCESS, 0, 0); // change priority to normal
				
				// EXIT FROM POWER SAVE MODE
				printf("EXIT FROM POWER SAVE %lu ms\n", time_idle);
				set_powersave(0);

			}
		}
	}

	return 0;
}
