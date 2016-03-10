# KAGServerBrowser
Server browser/launcher for King Arthur's Gold

Cross platform server browser for the game King Arthur's Gold

[Technical]
- Custom JSON Generics Library for handling server data. See Jacobious52/Json-Generics
- Custom UI controls and UI system built from scratch. Views, Material Style Button, Scrollable Listbox, etc
- Openframeworks for rendering and http access

[Preview]
![List of servers]
(list.png)

![Expanded server]
(fav.png)

[Current]
- designed for people who usually only join 1 or 2 servers often.
- Puts your favourite servers at the top
- shows list of connected players for fav 


[Planned]
- See forum players avatars next to name
- See in game chat log of fav servers

[build]
- built with openframeworks 0.9.0.
- download openframeworks for your OS at http://openframeworks.cc/download/
- clone source to {openframeworks}/apps/myapps/KAGServers
[osx]
- open xcode project and build
[windows]
- open visual studio 2015 sln
[linux]
- goto {openframeworks}/project-generator
- run it and choose the repo for the source
- add qt-creator or makefiles in the OS drop down
