/*

T Robb 12 sep 12

just a dodgy bit of code, that ought to let you play morse through a speaker

*/

// include the library code:

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int buttonPin = 14;
int speaker = 3;

  // define all the morse lengths and pitch here.
  
int key = 700;  // pitch of the morse key 900hz?
int dit = 320;    // length of a dit in milliseconds
int dah = 960;  // length of a dit in milliseconds

int space_dahdits = 70;  // space between dots and dashes
int space_char = 150;      // space between letters (may not be used)
int space_word = 900;      // space between words (may not be used)

int programnumber = 1;           


void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
tone(speaker, 900, 75);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" My Morse V0.2B  ");    //Print a little message
lcd.setCursor(0, 1);
lcd.print("Long Live Morse! ");
delay(1500);

menu();

}
void loop() { 
}

void menu(){


  Serial.println(programnumber);
  Serial.println(analogRead(14));
  
  switch(programnumber){

// This is where you add or remove menu items and changs the menu names
// dont forget to increase the menu numbers at the bottom
 
   case 1:       
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("Call CQ twice   ");
          break;
     
      case 2:    
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("CQ with callsign");
          break;


    case 3:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("Play Callsign   ");
          break;
          
    case 4:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("This is callsign");
          break;
          
      case 5:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("Special tone 1  ");
          break;
          
      case 6:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("Special tone 2  ");
          break;
          
      case 7:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu ..");
          lcd.setCursor(0, 1);
          lcd.print("Faster    ");
          lcd.print(space_dahdits);
          lcd.print("ms");
          break;
          
          
      case 8:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Slower    ");
          lcd.print(space_dahdits);
          lcd.print("ms");
          break;
          
    default:  
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Plays Callsign  ");
          break;
    }

while((analogRead(buttonPin))>=1000){}   // do nothing while no buttons pressed to chill out
delay(5);

if((analogRead(buttonPin))<=50){

  programnumber++;
  delay(300);
  }   

  if(analogRead(buttonPin)>=100 && analogRead(buttonPin)<=200){
  programnumber--;
  delay(30);
  } 

  if(analogRead(buttonPin)>=200 && analogRead(buttonPin)<=400){
  
  programnumber++;
  delay(10);
  }
  
  if(analogRead(buttonPin)>=400 && analogRead(buttonPin)<=600){
  programnumber--;
  delay(300);
  } 

    if(programnumber > 8){programnumber = 1;}          // dont forget to increase the menu numbers here!!
    if(programnumber < 1){programnumber = 8;}
    
    if(analogRead(buttonPin)>=600 && analogRead(buttonPin)<=800){
      Serial.println("Button Pressed");
      
      switch(programnumber){
        
        case 1:
          Serial.println("play 1");
          cq();
          break;
        
        case 2:
          Serial.println("play 3");
           cqCallsign();
          break;
        
        case 3:
          Serial.println("play 2");
          callsign(); 
          break;
        
        case 4:
          Serial.println("play 4");
           thisIs();
          break;
  
        case 5:
          Serial.println("play 5");
          special_1();
          break;
        
        case 6:
          Serial.println("play 5");
          special_2();
          break;
          
       case 7:
          Serial.println("speed up");
           faster();
          break;               
          
          
        case 8:
          Serial.println("slow down");
           slower();
          break;
          
     
                     
        default:  
          Serial.println("play 1");
           callsign();
          break;
      }
    } 
  delay(300);
  lcd.clear();
  menu();
   }

 
void faster(){
  space_dahdits= space_dahdits - 10;
}

void slower(){
  space_dahdits= space_dahdits + 10;
}

void dot(){                        // This is the main dot routine
  for(int a = 0; a <= dit; a++){
  tone(speaker, key);
  }
    noTone(speaker);
delay(space_dahdits);
delay(5);
  
}
void dash(){                        // this is the main dash routine
  for(int a = 0; a <= dah; a++){
  tone(speaker, key);
   
  }
  noTone(speaker);
delay(space_dahdits);
delay(5);
}

void special_1(){

 for(int i = 0; i <=3000; i = i + 100){
   
  tone(speaker, i);
  delay(60);  
 noTone(speaker);
  }
  delay(60);
  
  for(int i = 3000; i >=0; i = i - 100){
   
  tone(speaker, i);
  delay(60);  
 noTone(speaker);
  }
 
}


 void special_2(){

   for(int i = 0;i <=10; i++){ 
     
  tone(speaker, 300, 500);
  delay(50);
  tone(speaker, 900, 500);
}
 }


void callsign(){
 
   dot();
    dot();
     dot();
      dash();
  
    delay(space_dahdits);
  
  dash();
  dot();
  dash();

  delay(space_dahdits);
  
 dot();
  dot();
   dash();
    dash();
     dash();
  
    delay(space_dahdits);
     
      dot();
    dot();
     dash();
     dot();
  
    delay(space_dahdits);
     
      dash();     
      dot();
       dash();
  
    delay(space_dahdits);
       
       dot();
        dash();
  
    delay(space_dahdits);
        
         dash();

} 
  
void cq(){
 
  dash();
  dot();
  dash();
  dot();
  
  delay(space_dahdits);
  
  dash();
  dash();
  dot();
  dash();
  
  delay(space_dahdits);
  
  delay(space_word);
  
  dash();
  dot();
  dash();
  dot();
  
  delay(space_dahdits);
  
  dash();
  dash();
  dot();
  dash();
  }
  
void cqCallsign(){
  
  cq();                // CQ DE callsign twice
  
  delay(space_word);
  
  dash();            // DE
  dot();
  dot();
  dot();
  delay(space_dahdits);
  dot();
  delay(space_dahdits);
  
  delay(space_word);
   
  callsign();
  
  delay(space_word);
   
  cq();
  
  delay(space_word);
  
  dash();            // DE
  dot();
  dot();
  dot();
  delay(space_dahdits);
  dot();
  delay(space_dahdits);
  
  delay(space_word);
   
  callsign();
 
}

void thisIs(){
  // this is 
  
  dash();
  delay(space_dahdits);

  dot();
  dot();
  dot();
  dot();
  delay(space_dahdits);

  dot();
  dot();
  delay(space_dahdits);

  dash();
  dash();
  dash();
  delay(space_dahdits);


  delay(space_word);
   
  dot();
  dot();
  delay(space_dahdits);

  dash();
  dash();
  dash();
  delay(space_dahdits);


  delay(space_word);
   
  callsign();
}
