#include "WProgram.h" //include the Arduino library
#include <stdio.h>
#include "avr_ros/ros.h" //main avrRos library
#include "avr_ros/Compass.h" //std_msg/Compass library


//Define global message objects to use in
//the callback functions and throughout the program
ros::Publisher resp;

higgs_arduino::Compass compass_msg;


void toggle()
{ //toggle an led to debug the program
    static char t=0;
    if (!t ) {
        digitalWrite(13, HIGH);   // set the LED on
        t = 1;
    } else {
        digitalWrite(13, LOW);    // set the LED off
        t = 0;
    }
}

void compass(const ros::Msg *msg){
        toggle();

        //make sure that if you are manipulating the raw string,
        //there is enough space in it
        //to handle all of the data
        
	// write the compass data in compass_
        node.publish(resp, &compass_msg);
}


// Since we are hooking into a standard
// arduino sketch, we must define our program in
// terms of the arduino setup and loop functions.

void setup()
{
    Serial.begin(57600);

    pinMode(13, OUTPUT); //set up the LED
    resp = node.advertise("compass");

}

void loop()
{
    for(;;) {
        int c = Serial.read();
        if (c == EOF)
            break;
        node.spin(c);
    }

    /* Do other work */
    delay(10);
}
