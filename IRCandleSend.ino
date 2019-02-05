


#include  <IRremote.h>
IRsend  irsend;


// Serial communication interface setup
void Serial_Communication_Setup(long Serial_Baud_Rate) {
  Serial.begin(Serial_Baud_Rate);           // PC serial interface begin, with defined buad rate
  Serial.println("System Start up...");     // Start up message
}



  // Function to setup command line interface
  void Command_Line_Interface_Setup() {
    Serial.println("--- Command Line Interface Initialized ---");
    Serial.println("Type 'help' for a list of commands.");
  }
 





const int  khz  =  38;  //  38kHz  carrier  frequency  

static  unsigned  int  offSignal[]  =  {600, 1600, 650, 1600, 650, 1600, 550, 1650, 650, 1600, 650, 1600, 650, 1600, 550, 1650, 650, 1600, 650, 1600, 600, 1650, 600, 1600, 650, 1600, 650, 1600, 600, 1650, 600, 1600, 650, 1600, 650, 1600, 9000, 4400, 650, 450, 650, 1600, 650, 500, 600, 1600, 650, 1600, 650, 450, 650, 500, 550, 1700, 600, 500, 650, 500, 550, 550, 650, 500, 550, 550, 650, 500, 550, 550, 650, 1600, 650, 500, 550, 550, 650, 1600, 650, 500 ,600, 1600, 650, 1600, 650, 1600, 650, 450, 650 };
static  unsigned  int  onSignal[]  =  { 650, 1600 , 650 , 1600,  600,  1650 , 550,  1700,  600,  1600,  650,  1600,  650,  1600,  650,  1600,  600,  1650 , 550,  1700,  600,  1600,  650,  1600,  650,  1600,  650,  1600,  600,  1650,  550,  1700,  600,  1600,  650,  1600,  9050,  4400,  650,  500,  600,  1600,  650,  500,  600,  1650,  600,  1600,  650,  500,  600,  500,  650,  1600,  650,  1600,  650,  500,  550,  550,  650,  500,  600,  1650,  550,  1700,  600,  500,  650,  500,  600,  1650,  550,  550,  650,  1600,  650,  500,  600,  500,  650,  1600,  650,  500,  600,  500,  650  };
static  unsigned  int txArray[200]  =  {};
 
void  setup()
{
  Serial.begin(115200);
   Command_Line_Interface_Setup();     // Command line interface setup function
  Serial.println("Starting...");

}

void turnOn()
{
    Serial.println("Turning on");
    irsend.sendRaw(onSignal ,  sizeof(onSignal)  /  sizeof(onSignal[0]),   khz);  //Note  the  approach  used  to  automatically  calculate  the  size  of  the  array.
}

void turnOff()
{
   Serial.println("Turning off");
   irsend.sendRaw(offSignal ,  sizeof(offSignal)  /  sizeof(offSignal[0]),   khz);  //Note  the  approach  used  to  automatically  calculate  the  size  of  the  array.
}

void  loop()  
{
  Command_Line_Interface_Input();
  // turnOn();
   //delay(5000);
   //turnOff();
  // delay(5000);
}

 // Handles incoming serial commands
  void Command_Line_Interface_Input(){
    // Check for incoming serial data from PC
    if (Serial.available() > 0) {
      String Serial_Data = Serial.readStringUntil("/n");        // Stores the current serial data into a variable
      Serial.print("> ");
      Serial.println(Serial_Data);
            // Check command length
      unsigned int Serial_Data_Length = Serial_Data.length();   // Determine length of serial data
      if (Serial_Data_Length > 32) {
        // Command too long, inform user
        Serial.println("Error: Command to long, type 'help' for a list of commands");
      }
      // Command acceptable length
      else {
        // Compare entered command to list of available commands, if a match is found the command function is triggered
       
        // Help command
        if (Serial_Data == "help"){
            // Lists the available commands
            Serial.println("System commands:");
            Serial.println(" - help");
            // Add extra commands here
        }
        // ??? command
        else  if (Serial_Data == "off")
          turnOff();
        else  if (Serial_Data == "on")
          turnOn();
        // Unknown command
        else {
          // Command not listed, inform user
          Serial.println(Serial_Data);
            Serial.println("Error: Command not recognised, type 'help' for list of commands");
        }
      }
    }
  }
