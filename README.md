# CarGenAI
Video of the project: https://youtu.be/aslTSS2VpCA  

This project was for learning about genetic algorithms and testing my neural network library, it may contains some errors and not being compatible with your OS/Version.  
I won't provide support, however you can still use and/or adapt the code yourself.

## Requirements

- Linux (You can still use Windows but i won't provide instructions for it you will probably have some changes to do)
- Basic knowledge about linux
- Unreal Engine 4 version 4.22

## Preparation

The files contain some hard path from my computer, you will need to changes them:
- Open **start.sh** in the root project folder and modify the path (read the comments in the file).
- Go into **ThirdParty/libvnn** and open the **Makefile**, you'll have to modify the path the variables **COMPILER_UE4** (line 13) and **ARCHIVER_UE4** (line 17) to use the clang compiler from Unreal Engine

You should now be able to launch the project, just start **start.sh**, it will install the libvnn and start the project
