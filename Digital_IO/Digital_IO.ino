/*
  Digital Input/Output

 8 Digital Inputs are connected through Multiplexer 74HC151
 This code reads Inputs through Mulitplexer & displays prints it on the Serial Terminal

  5 Relays are connected through ULN2003 relay driver on the Digital pins
  These can be set by using this code


 74HC151 COnnections
 A = A5
 B = D9
 C = D12
 DI = A4

  Relay Connections
  R1 = D2 
  R2 = D3
  R3 = D4
  R4 = D5
  R5 = D6
  
*/

#define A A5
#define B 9
#define C 12
#define DI A4

#define R1 2
#define R2 3
#define R3 4
#define R4 5
#define R5 6


String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int inputs[8]={0,0,0,0,0,0,0,0};           //Array to save state of 8 Inputs
int prev_inputs[8]={0,0,0,0,0,0,0,0};      //Array to save Previous state of 8 Inputs


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(DI, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
 
}

// the loop routine runs over and over again forever:
void loop() 
{
  
  read_inputs();
  for(int i=0;i<8;i++)
  {
      if(prev_inputs[i] != inputs[i])
      {
           Serial.print("Input");
           Serial.print(i);
           Serial.print("=");
           Serial.print(inputs[i]);
           prev_inputs[i] = inputs[i];
      }
  }
  
  if(stringComplete)
  {
      stringComplete=0;
      set_relay();
  }
   
}


void set_relay()
{
  
  switch(inputString)
  {
      case "R10":
          R1=0;
          break;
      case "R11":
          R1=1;
          break;
      case "R20":
          R2=0;
          break;
      case "R21":
          R2=1;
          break;
      case "R30":
          R3=0;
          break;
      case "R31":
          R3=1;
          break;
      case "R40":
          R4=0;
          break;
      case "R41":
          R4=1;
          break;
      case "R50":
          R5=0;
          break;
       case "R51":
          R5=1;
          break; 
       default:
        
  }
  

}

void read_inputs()
{

    digitalWrite(A,LOW);    digitalWrite(B,LOW);    digitalWrite(C,LOW);
    inputs[0]=   digitalRead(DI);  
    delay(50);

    digitalWrite(A,LOW);    digitalWrite(B,LOW);    digitalWrite(C,HIGH);
    inputs[1]=   digitalRead(DI);  
    delay(50);

    digitalWrite(A,LOW);    digitalWrite(B,HIGH);    digitalWrite(C,LOW);
    inputs[2]=   digitalRead(DI);  
    delay(50);


    digitalWrite(A,LOW);    digitalWrite(B,HIGH);    digitalWrite(C,HIGH);
    inputs[3]=   digitalRead(DI);  
    delay(50);
    
    digitalWrite(A,HIGH);    digitalWrite(B,LOW);    digitalWrite(C,LOW);
    inputs[4]=   digitalRead(DI);  
    delay(50);
    
    digitalWrite(A,HIGH);    digitalWrite(B,LOW);    digitalWrite(C,HIGH);
    inputs[5]=   digitalRead(DI);  
    delay(50);
    
    digitalWrite(A,HIGH);    digitalWrite(B,HIGH);    digitalWrite(C,LOW);
    inputs[6]=   digitalRead(DI);  
    delay(50);
    
    digitalWrite(A,HIGH);    digitalWrite(B,HIGH);    digitalWrite(C,HIGH);
    inputs[7]=   digitalRead(DI);  
    delay(50);

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
