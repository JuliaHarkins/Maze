# Maze
Second year project, done in C++. It's a maze.

A console based application in which the user's goal is to exit the maze.
Upon opening the application a menu appears which allows the user to chose
which maze they would like to navigate: basic, random or file.

the basic maze is always the same. However the file maze is a maze created
by the user and the random maze is generated by the program.

The File map is loaded in from a file named ‘maze.txt’. In which the User enters
the name of the room, the direction (North, East, South, West, Ladder, Floor) it
connects in followed by the connection room. This connection only needs to be
done once and letter case matters. 

Example:
A West B 
B West C 
C West D
