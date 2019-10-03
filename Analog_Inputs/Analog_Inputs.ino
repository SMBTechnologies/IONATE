/*
 Analog Inputs
 4 Analog Inputs are connected to A0-A3 via Opamps 

*/

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int AI[4] ={A0,A1,A2,A3};    // select the input pin for the Analog Input 
int AnalogValue[4] ={0,0,0,0};  // array to store the values coming from the Analog Inputs


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 
}

// the loop routine runs over and over again forever:
void loop() 
{
  for(int i=0;i<4;i++)
  {
    AnalogValue[i] = analogRead(AI[i]);   
  }
  if(stringComplete)
  {
      stringComplete=1;
      for(int i=0;i<4;i++)
      {
         Serial.print("Analog Input ");   Serial.print(i);  Serial.print("=");      Serial.println(AI[i]);    //Print all Analog Input Values         
      }
  }
 
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
