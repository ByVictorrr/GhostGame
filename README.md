# GhostGame ( A CLI game)



## Images:

![screenshot1](https://github.com/ByVictorrr/GhostGame/blob/master/images/screenshot2.png)
![screenshot2](https://github.com/ByVictorrr/GhostGame/blob/master/images/screenshot1.png)
![screenshot3](https://github.com/ByVictorrr/GhostGame/blob/master/images/screenshot3.png)


### A description of your program and its features.

The class Ghost game consist of many functions and when it starts the process. The menu has 5 options: start game, instructions how to play, example how to play, score card as well as exit. When you press the start game it prompts you to enter in the amount of players 2-4, then entering your name it stores it into a data structure for name and score. Which when you loose the round it minus 5 points same as if the typed word doesn't start with string.

### A description of your program's command-line syntax.
I wrote this using object oriented programing including useful variable and function names for the game such as inserting word list and insert as in the data structure of trie tree. 

### A description of the main data structures your program uses.

My program was written using the Trie tree data structure which was then transformed and developed into a game. I made a structure for someones name and score when they start a game at the main menu.
A discussion of the current status of your program, what works and what doesn't, etc.

Everything works in my program its just, I could have used less for loops to speed up the time it takes to read in the files to the structure.

### Your plan that you used to write your code.

I planned without knowing what a trie tree was before, I looked at it to do something similar each node having 26 array pointers to hold each letter of the alphabet. I was going to have 26 roots linked on like a list at the top and every word starting with that letter derived from that and it would delete each root nodes that didn't have the first character of that word so it could search faster. I tried implementing this but it was to complicated and then i realized what a trie tree was.
