# Switching-Matrix

This PCB switching board was designed to eliminate unwanted electrical cross-talk when addressing devices in memristive systems, a well-known drawback of the commonly used crossbar array. The board contains a 16x16 grid of electrical contacts. At each contact, there lie 3 switches, each controlled through an Arduino nano via 16 bus expander units using I2C communication. Memristive systems, as well as up to 16 pairs of input and output devices, can be connected to the 16x16 grid. To produce optimal switch pathways connecting I/O devices with memristive devices, the switching matrix was represented with NetworkX and the Dijkstra algorithm was implemented. As a result, a serial communication protocol between python and arduino needed to be established. Funded by NSF grants no. 1748459 and 16088.
