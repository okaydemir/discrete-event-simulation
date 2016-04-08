# Discrete Event Simulation

Assume that we want to simulate the working flow of a cargo company. This company has two types
of units in their work flow: first-level units that collect and process the package information and
second-level units that put the given packet into the correct truck. Whenever a new package comes,
first-level units will get the package, process the related information and pass the package onto the
second-level units. These units are connected to each other within different layouts.
#Layout 1
![layout 1](/layout_pics/layout1.png)
#Layout 2
![layout 2](/layout_pics/layout2.png)

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

#Resources
http://www.win.tue.nl/~resing/2S540/week2.pdf <br />
https://en.wikipedia.org/wiki/Discrete_event_simulation
