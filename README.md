# uni-c-project
A university C programming project for semester 2.

The task was to write a container management system (yes...containers as in ship-containers. Actual, physical things. Not docker containers :P) to be picked up by ships that arrived at the port authority in a particular order.

The task was to create stacks of containers, represented by numbers, where no container with a higher number was on top of a container with a lower number. In the end the ships would arrive at the port and containers had to be handed out in order of the ships assigned to them (ship 1, ship 1, ship 1, ship 2, ship 3, etc...).

My solution is based around a stack in form of a double linked list (with structs) and a modified Red-Black binary search tree, making more and deeper comparisons and also using a simple heuristic looking at the bottom and top elements of a stack to compare their attractiveness for pacing a particular value on top of them to avoid having to create more stacks in the future.

This code is licensed under the MIT Public License and can be used for any purpose you so desire as long as my name and the LICENSE file remains in the head.
