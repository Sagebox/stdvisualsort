
The full GitHub Sagebox libraries for Windows C++ (using Microsoft Visual Stuio) can be downloaded:

https://www.github.com/Sagebox/Sagebox

*************************
std::sort() Visualization 
*************************

This is a relatively short program that looks at what is going on in std::sort() while it is sorting
and then graphs it on the screen. 

It originally was part of a 10-line sort visualization I am collecting in the 10-liner example set 
(at https://github.com/Sagebox/sagebox/tree/master/Examples) - if it isn't in there yet, I will be putting
it there in a couple days. 

This program shows how we can take a program -- such as a standard console program, or whatever -- and 
insert elements into it to get a nice real-time graphical display of what is going on. 

This program started as a console program, but then I moved it to a Windows program (with Sagebox projects,
this is typically just a configuration setting with no code changes at all).

This particular program is set to a Debug configuration -- I added some code to make it faster and it started
running too fast, so I had to slow it down -- any faster and will have to start looking at the ms timer between
updates to slow it down. 


Look at the file https://raw.githubusercontent.com/Sagebox/stdvisualsort/main/video.webm to see the .webm video of it working.

