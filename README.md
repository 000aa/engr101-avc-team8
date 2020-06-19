# Installation Instructions

## macOS Catalina

Follow the instructions below to install the software on macOS Catalina.

### Install the SFML gaming library

The software depends on the SFML gaming library, so this must be installed first.

1. Ensure Xcode is up to date. From the Apple menu in the top right, open System Preferences > Software Update. If there is an update available for Command Line Tools for Xcode, install it.
1. Open a new Terminal window.
1. Intall Homebrew by pasting the following into the terminal window: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"`
1. Once Homebrow is installed, paste the following into the terminal window to install the SFML gaming library: `brew install sfml`
1. You may now close the Terminal window.

### Download, make, and run the software

1. Download the GitHub repository as .zip file.
1. Extract the .zip file in a place of your choice. It will contain two folders: AVC_robot and AVC_server.
1. Open two new Terminal windows: one in the AVC_robot folder, and one in the AVC_server folder. If the two folders are in your home folder, you can open them in either of the Terminal windows by typing `cd AVC_robot` or `cd AVC_server`.
1. Type `make` into both Terminal windows. This will use the makefile contained in each folder to create an executable file. The makefiles provided are ready to use, and do not need to be edited.
1. Open config.txt from the AVC_server folder in a text editor of your choice to change the maze file to either core.txt, completion.txt, or challenge.txt. Save the file.
1. In the Terminal window for the AVC_server folder, type `./server3` to start the server.
1. In the Terminal window for the AVC_robot folder, type `./robot` to run the software.
1. To change the maze file, close the software window, and press control-C in both Terminal windows. You can then repeat steps 5 - 7.

# AVC Team Plan

## Team Members

* aknineamaz (000aa)
* forsytgrac
* phamkhan

Team members contact each other via Facebook Messenger and Zoom

## Roles

* **Grace:** Project Manager (organise team meetings and report on progress), software writing, core code for controlling robot, debugging code.
* **Khanh:** Software Coordinator (put core components of the code together and check they work), software writing, testing code, debugging code.
* **Amazir:** Software Architect (support overall development of functioning code), software writing, core code for detecting maze, debugging code.

## Timeline & Tasks

Start Date | Objectives | Due Date | Item Due | Conflicts
---------- | ---------- | -------- | -------- | ---------
3 / 6 | Start the Project | 4 / 6 | Successful installations, AVC team plan | COMP, 121, CYBR
4 / 6 | Start Core & Completion Code | 12 / 6 | Core & Completion Code | COMP, 121, CYBR
13 / 6 | Start Challenge Code | 19 / 6 | Challenge Code | COMP, 121

### Tasks: Start the Project

* **Group Zoom:** Complete AVC team plan.
* **Group Zoom:** Test all installations. Help to install SFML on all team computers.
* **Amazir:** Check in that teammates could successfully save images from robot.

### Tasks: Start Core & Completion Code

* **_All_:** Write code so robot moves through Core and Completion
* **_All_:** Intro & Background for progress report started 
* **Amazir, by morning Saturday 6:** In charge of detecting white line code
* **Group Zoom:** Check in with progress on above code
* **Grace, by evening Tuesday 9:** In charge of code for moving robot so that it responds to white line
* **Group Zoom:** Check in with progress on above code
* **Khanh:** In charge of main code
* **Group Zoom:** Debug program & check report, plan meetings for following week
* **Khanh, by evening Friday 12:** Check all components of code enables robot to complete circuits, debug/fix if necessary

### Tasks: Start Challenge Code

* **_All_:** Write code so robot moves through Challenge
* **_All_:** Continue with progress report
* **Amazir:** In charge of detecting brick walls code
* **Group Zoom:** Check in with progress on above code
* **Grace:** In charge of code for moving robots so that it responds to brick wall locations
* **Group Zoom:** Check in with progress on above code
* **Khanh:** In charge of main code
* **Group Zoom:** Debug program & check report
* **Khanh, by evening Friday 12:** Check all components of code enables robot to complete circuits, debug/fix if necessary
* **_All_:** Confirm we are happy with the way robot moves through all courses
