# discrete-event-simulation
C++ working flow of a cargo company simulation


![alt tag]( discrete-event-simulation/layout_pics/layout1.png )
# Input
* First line is the number of first-level units (N).
* Next N lines contain process time information of the first-level units.
* Next line contains the number of second-level units (M).
* Next M lines contain process time information of the second-level units.
* Next line contains the number of cargo packets (L)
* Remaining lines contain arrival times of packets.


# Output
* Average turnaround time, which is equal to the time that the package is sent to the truck - the arrival time of the package
* Maximum length of first-level queue
* Maximum length of second-level queue
* Average wait time of all packages
* Longest wait time of all packages
* The last line is the total running time of the cargo office, which is equal to the time when the last order is packed - the arrival time of the first package
