# FlashFloodProject

In Engineering 101 at Duke University, students work in a team to learn and apply the engineering design process to solve an open-ended, client-based problem drawn from a community partner.  

My Engineering 101 group was tasked by our client, Professor Andrew Jones, with developing a sensor device that automatically deploys during flash floods to collect surface flow data on speed and position, facilitating the creation of higher-accuracy predictive flash flood models. 

Data collection is done through an electronic circuit involving a feather board with a LoRa Radio Module, 9-DOF Inertial Measurement Unit, Micro SD Card Breakout Board, and GPS module. Arduino scripts that interface between these electronics are included in this repository. 

Other Arduino scripts included in this repository involve communicating using the feather board's long-range radio functionality, detecting voltage from the DC motor connected with the water wheel to turn the stepper motor as part of the rack-and-pinion release mechanism, and measuring the voltage of the 3.7 V lithium polymer battery powering the electronics.

