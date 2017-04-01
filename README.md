# The VR-Wifi Simulator.

This is my first kernel module.
I was sitting in an intercity train the other day trying to download the _linux-source_ package and had lots of packet loss and a shitty speed using the train wifi. Incidentally I was reading about kernel programming at the same time so I got this idea: What if I wrote my hello_world module and make it be about having a shitty internet -- fantastic!

**Currently this does:**
 - Drops every 13th packet

**Ideas:**
 - Determine rules for both outbound and inbound traffic
 - Block certain IPs/ports to increase productivity (looking at you social media)
 - Try out some make flags
 - Come up with _funnier_ ways to determine whether packet is dropped

**Building:**
Makefile is ready and usable. Requires the linux-source package for your current kernel.

