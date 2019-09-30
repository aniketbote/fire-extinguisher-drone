# fire-extinguisher-drone
Autonomous drone for assisting fire fighters in deadly situations.

## HOW TO INSTALL BLYNK ON PC AND GET IT WORKING VIA APP ##

INSTALLING BLYNK ON PC
1. Download and install the latest Arduino IDE.
https://www.arduino.cc/en/Main/Donate 
2. Download and extract the latest zip of Blynk library.
https://github.com/blynkkk/blynk-library/releases
3. Extracted folder must contain two folders library and tools.
4. Paste the content of library folder(from extracted zip) into Arduino's library folder.
Probable path is "C:\Program Files (x86)\Arduino\libraries"
5. Do the same for tools folder. Paste the content of tools folder(from extracted zip) into Arduino's tools folder.
Probable path is "C:\Program Files (x86)\Arduino\tools"
6. Restart the Arduino IDE and Blynk must be installed. To check go on to "File>Examples>Blynk" 
and if its there then Blynk has been successfully installed.

To get it working
1. Install the Blynk app from play store and sign in.
2. Create a new project and select NodeMCU for Board and create a new project
3. Now you must have received a token in mail just copy and paste in char auth section 
path is fire-extinguisher-drone\flight_controller_main\flight_controller_main.ino
4. Again copy paste ID and password of the local hotspot to which NodeMCU and Blynk app will be connected to.
5. Add buttons preferably virtual pin and start using it.
