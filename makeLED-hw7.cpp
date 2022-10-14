/** Simple On-board LED flashing program - written in C++ by Derek Molloy
*    simple functional struture for the Exploring BeagleBone book
*
*    This program uses USR LED 3 and can be executed in three ways:
*         makeLED on
*         makeLED off
*         makeLED flash  (flash at 100ms intervals - on 50ms/off 50ms)
*         makeLED blink n times
*         makeLED status (get the trigger status)
*
* * Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
#include<cstring>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

// Function to display usage message
void usageMessage(){
   cout << "Usage is makeLED-hw7 and one of: " << endl;
   cout << "   on, off, flash, or status" << endl;
   cout << " e.g. makeLED-hw7 flash" << endl;
   cout << endl;
   cout << "If you want to make the LED blink n times." << endl;
   cout << "Usage is makeLED-hw7 and the number of times that the LED will blink." << endl;   cout << " e.g. makeLED-hw7 blink 5" << endl;
}

int main(int argc, char* argv[]){
   // Condition when to display the usage message
   if(argc==1){
   	usageMessage();
	return 1;
   }
   if(argc==2 && strcmp(argv[1],"blink") == 0){
	usageMessage();
	return 2;
   }
   if(argc==3 && strcmp(argv[1],"blink") != 0 || argc>3){
	usageMessage();
	return 3;
   }  
   
   // Convert the first argument to the string type
   string cmd(argv[1]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash, blink n times or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   // Condition to make the LED blink
   else if (cmd=="blink"){ // Check if the argument is "blink"
	// Variable to takes the number of times that the LED will blink
	string cmd1(argv[2]);
	// Display blink message
	cout << "Blinking the LED " << cmd1 << " times" << endl;
	removeTrigger();
	// A count up variable
	int counter = 0;
	// Loop to blink the n times LED
	while(counter!=stoi(cmd1)){
	writeLED("/brightness","1"); // Turn on the LED
	sleep(1); // Stay on a sec
	writeLED("/brightness","0"); // Turn off the LED
	sleep(1); // Stay off for a sec
	counter++; // Keep track the number of time that the LED has been blinked.
	}
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
