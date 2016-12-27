# Robot Navigation

This project is about making the robot to clean the floor tiles. First of all, the floor tile has dust quantity 0 (no dust) to 5 (full of dust) but note that 0 is also can be an obstacle that robot can't move over. Robot can clean dusts by its brush which has value 0 to 5 and the floor tile will cleaned by absolute of brush value minus dust value. Note that the robot can know whether the floor tile has dust or not (can't know the quantity of the dust) only when camera is opened. The robot has 3 states, off, stand by and robot can only move (8 directions) and clean the dust only when in state on. Every time the robot has to change direction, it need to be in stay still state.

## Robot Description

State of ROBOT = { P , C , B , D }
    
P = Power (0 = Off, 1 = Stand By, 2 = On)
C = Camera (0 = Off, 1 = On)
B = Brush (Power to Clean 0 - 5)
D = Direction 
   
0 = North
1 = North East
2 = East
3 = South East
4 = South
5 = South West
6 = West
7 = North West
8 = Stay Still

## Developer

By Supakrit Paoliwat 5730593821                               

## About

Project for "ALGORITHM DESIGN" 2016/1

Computer Engineering (CP 41), Faculty of Engineering, Chulalongkorn University


                
                
