# Code for coil printing device of vascular grafts, along with circuit diagram**
### Cosgriff-Hernandez Laboratory; UT-Austin Biomedical Engineering**

__Formulas for determining RPM__   
Assuming one step per pulse, delay is: wait = (μs/min) * (1/rpm) * (1/pulses per revolution) - overhead  
Overhead = extra time it takes to run digitalWrite twice and loop  
RPM = (steps per second)/(steps per revolution) * (60 seconds/minute)  
step angle = 1.8 degrees ; 200 steps per revolution ; .005 revolutions per step  
Solving for Steps Per Second: SPS = (RPM)/((REV_P_STEP)*(60 sec/min))  

According to John Craig:  
  C0 = 15 * M_PI ; Motor X Circumference  
  XSPR = 1 * (200 * 11) ; Motor X Steps per Rotation  
  dVx = dS * (XSPR/C0) ; Desired X-Axis time from mm/s to x-axis steps/sec (dS represents desired x-axis speed)  
  Assuming we use a button/knob, each increment/decrement would change the mm/s by 0.1  
  So, to get the necessary pulse delay, increment/decrement by:  
    dVx = 0.1 * (1 * (200 * 11))/(15*M_PI)  

  Example: If we have an initial target rpm of 10, that gives us a dS of 10  
  As such, dVx which is our speed in steps will be 10 * (1 * (200 * 11)) / (15 * M_PI)  
  All of these variables are set globally  
  wait = (microsecondsPminute) * (1/RPM) * (1/pulsesPrevolution) - overhead  
  rpm / 60 = rps  
  60 / rpm = spr  
  (60 / rpm)/360 = spd  
  ((60 / rpm)/360) * 1.8 = sps  

*** 
Assume from measured diameter with calipers that it is 12 mm (Check 11.85 as well)  
To get Spacings: V_extruder / RPM_rod   
V_extruder = M_PI * Diam_extruder * RPM_extruder (in (mm*rev)/min)   
RPM_rod = 13 rpm (set from original bought parts)  
V_extruder = M_PI * 12 mm * X   
Spacing = (M_PI * 12 * X) / 9.64507699 RPM   
Spacing = 3.90863773 * X  
For Spacings of 3 mm... 0.76753084 rev/min ~= 0.77 rev/min  
For Spacings of 5 mm... 1.27921807 rev/min ~= 1.28 rev/min  
For Spacings of 7 mm... 1.79090529 rev/min ~= 1.79 rev/min  
***
y = 1.0715x + 2.6653  
y = Voltage Setting  
x = RPM  
For Voltage Setting of 13, RPM = 9.64507699  

T_inc = incremental torque produced with each microstep  
T_hfs = holding torque (full-step operation)  
SDR = step division ratio (number of microsteps per full step)  

T_inc = T_hfs * sin(90/SDR)  
T_inc = 0.14 * sin(90/256)  
T_inc = 0.00085902385  
