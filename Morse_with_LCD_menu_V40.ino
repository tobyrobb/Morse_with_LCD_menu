/*

T Robb 12 sep 12

just a dodgy bit of code, that ought to let you play morse through a speaker or a relay

$ver 0.40


NOTES:

all the functions are at the bottom

there are functions for each letter

you may need to put delays in between each letter


TODO:


press any key to abort

change pitch of morse key sound

add numbers and special characters

maybe reduce system to one key

add saving of the variables to non volatile ram

provide ability to enter a custom message ie callsign

beacon support

serial control or ethernet if possible

special sounds? psk replies??

*/

// include the library code:

#include <LiquidCrystal.h>
#include <EEPROM.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int buttonPin = 14;
int speaker = 3;

  // define all the morse lengths and pitch here.

int key = 700;  // pitch of the morse key 900hz?
int dit = 320;    // length of a dit in milliseconds
int dah = 960;  // length of a dit in milliseconds

int space_dahdits = 70;  // space between dots and dashes
int space_char = 300;      // space between letters (may not be used)
int space_word = 900;      // space between words (may not be used)

int maxprogramnumber = 15;  // dont forget to increase the menu numbers here!!
int programnumber = 1;           


void setup() {
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
tone(speaker, 900, 75);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("T.Robb     V0.40");    //Print a little message
lcd.setCursor(0, 1);
lcd.print("Long Live Morse! ");
delay(1500);

  

readEeprom();    // this is where we read in the eeprom values

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
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Alphabet        ");
          break;
          
      case 8:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Increase speed +");
          break;
          
          
      case 9:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Decrease speed -");
          break;
                   
     case 10:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Space length   +");
          break;
     
     case 11:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Space length   -");
          break;
      
      case 12:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Increase pitch +");
          break;
          
      case 13:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Decrease pitch -");
          break;
          
      case 14:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print(" Save Settings  ");
          break;
      
      case 15:
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Default Settings");
          break;
          
              
    default:  
          lcd.setCursor(0, 0);
          lcd.print("Select a menu...");
          lcd.setCursor(0, 1);
          lcd.print("Plays Callsign  ");
          break;
    }

// dont forget to increment maxprogramnumber at the top of file


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

    if(programnumber > maxprogramnumber){programnumber = 1;}          // this is where the menu goes around and around
    if(programnumber < 1){programnumber = maxprogramnumber;}
    
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
          Serial.println("alphabet");
           alphabet();
          break;
          
       case 8:
          Serial.println("speed up");
           faster();
          break;               
          
          
        case 9:
          Serial.println("slow down");
           slower();
          break;
          
       case 10:
          Serial.println("space length increase");
           spaceLonger();
          break;
        
       case 11:
          Serial.println("space length decrease");
           spaceShorter();
          break;
          
       case 12:
          Serial.println("Key pitch up");
           pitchUp();
          break;
                  
       case 13:
          Serial.println("Key pitch down");
           pitchDown();
          break;
          
       case 14:
          Serial.println("Save Settings");
           save();
          break;

       case 15:
          Serial.println("Default Settings");
           clearEeprom();
      
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

 for(int i = 0; i <=3000; i = i + space_dahdits * 4){
   
  tone(speaker, i);
  delay(60);  
 noTone(speaker);  
  }
  delay(60);
  
  for(int i = 3000; i >=0; i = i - space_dahdits * 4){
   
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


void cq(){
  
  c();
    delay(space_char);
  q();
    delay(space_word);
  c();
    delay(space_char);
  q();
    delay(space_word);
    
 }
 
void callsign(){
 
   v();
    delay(space_char);
   k();
    delay(space_char);
   two();
    delay(space_char);
   f();
    delay(space_char);
   k();
    delay(space_char);
   a();
    delay(space_char);
   t();
    
} 
  

  
void cqCallsign(){
  
  cq();                // call CQ  calls cq twice
  delay(space_word);
  
  t();
      delay(space_char);
  h();
      delay(space_char);
  i();
      delay(space_char);
  s();
    
      delay(space_word);

  i();
      delay(space_char);
  s();
    
      delay(space_word);

  callsign();

}

void thisIs(){
  // this is 
  
  t();
      delay(space_char);
  h();
      delay(space_char);
  i();
      delay(space_char);
  s();
    
      delay(space_word);

  i();
      delay(space_char);
  s();
    
      delay(space_word);

  callsign();

}

 
void faster(){

  space_dahdits = space_dahdits - 10;
  
  if(space_dahdits <=10){
  space_dahdits = 10;
}
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Current speed");
          lcd.setCursor(0, 1);
          lcd.print(space_dahdits);
          delay(250);
}

void slower(){
  space_dahdits= space_dahdits + 10;
 if(space_dahdits >=2540){
  space_dahdits = 2540;
}

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Current speed");
          lcd.setCursor(0, 1);
          lcd.print(space_dahdits);
          delay(250);
          
}
void spaceLonger(){
  space_char = space_char + 10;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Current space  ");
          lcd.setCursor(0, 1);
          lcd.print(" length =");
          lcd.setCursor(10, 1);
          lcd.print(space_char);
          delay(250);
}

void spaceShorter(){
  
  space_char = space_char - 10;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" Current space  ");
          lcd.setCursor(0, 1);
          lcd.print(" length =");
          lcd.setCursor(10, 1);
          lcd.print(space_char);
          delay(250);  
}


void pitchUp(){
  
key = key + 10;

if(key >= 2540){
  key = 2540;
}

   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Key pitch is  ");
   lcd.setCursor(0, 1);
   lcd.print(key);
 
 delay(300);
   
}

void pitchDown(){
 
key = key - 10;  

if(key <= 10){
  key = 10;
}
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Key pitch is  ");
   lcd.setCursor(0, 1);
   lcd.print(key);
 
 delay(300);
 
}



void readEeprom(){
  
  // this is where we read the values from the eeprom and put them into the program

space_dahdits = (EEPROM.read(0)* 10);

space_char = (EEPROM.read(1) * 10);

space_word = (EEPROM.read(2) * 10);

key = (EEPROM.read(3) * 10);

for(int i = 0; i <= 3; i++){
    Serial.print("EEPROM contains: ");
    Serial.println(EEPROM.read(i));
}


}

void save(){
  
// lets write the values to the eeprom

 EEPROM.write(0, (space_dahdits/10)); // Write byte
 EEPROM.write(1, (space_char/10)); // Write byte
 EEPROM.write(2, (space_word/10)); // Write byte
 EEPROM.write(3, (key/10)); // Write byte
 
 
Serial.println("Saving....");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("    Saving    ");
      lcd.setCursor(0, 1);
      lcd.print("   Settings   ");
 
  tone(speaker, 900, 75);

delay(1000);

for(int i = 0; i <=3; i++){
  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Address ");
      lcd.print(i);
      lcd.setCursor(0, 1);
      lcd.print(EEPROM.read(i)*10); 
  
   delay(1000);

}

}

void clearEeprom(){

// lets write the default values to the eeprom

 key = 700;  // pitch of the morse key 900hz?
 dit = 320;    // length of a dit in milliseconds
 dah = 960;  // length of a dit in milliseconds

 space_dahdits = 70;  // space between dots and dashes
 space_char = 300;      // space between letters (may not be used)
 space_word = 900;      // space between words (may not be used)


 EEPROM.write(0, 7);   // this is the spot for space_dahdits
 EEPROM.write(1, 30); // Write byte
 EEPROM.write(2, 90); // Write byte    
 EEPROM.write(3, 70); // Write byte  

  
 Serial.println("Saving default values....");

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Saving default");
      lcd.setCursor(0, 1);
      lcd.print("    Values    ");
 
 tone(speaker, 900, 75);

      delay(1000);
}




void alphabet(){
  
  delay(1000); // let the button press settle
          
          int delayAmount;
          delayAmount = (space_dahdits * 10);  // How much to wait between letters
          
          lcd.setCursor(0, 0);
          lcd.print("Hold key to stop");
          
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          a();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          b();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          c();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          d();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          e();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          f();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          g();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          h();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          i();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          j();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          k();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          l();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          m();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          n();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          o();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          p();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          q();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          r();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          s();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          t();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          u();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          v();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          w();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          x();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          y();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
          z();
          delay(delayAmount); if((analogRead(buttonPin))<=1000){menu();}
           
  
     
   
 }

void a(){

          lcd.setCursor(0, 1);
          lcd.print("       A        ");
 
          dot();
          dash();
          
 }

void b(){
          lcd.setCursor(0, 1);
          lcd.print("       B        ");
         
          dash();
          dot();
          dot();
          dot();
          
}

void c(){
          lcd.setCursor(0, 1);
          lcd.print("       C        ");
          
          dash();
          dot();
          dash();
          dot();
}

void d(){
          lcd.setCursor(0, 1);
          lcd.print("       D        ");
          
          dash();
          dot();
          dot();
          
}

void e(){
          lcd.setCursor(0, 1);
          lcd.print("       E        ");
          
          dot();
}

void f(){
          lcd.setCursor(0, 1);
          lcd.print("       F        ");
         
          dot();
          dot();
          dash();
          dot();
}

void g(){
          lcd.setCursor(0, 1);
          lcd.print("       G        ");
         
         dash();
         dash();
         dot();

}

void h(){
          lcd.setCursor(0, 1);
          lcd.print("       H        ");
         
          dot();
          dot();
          dot();
          dot();
}

void i(){
          lcd.setCursor(0, 1);
          lcd.print("       I        ");
          
          dot(); dot();
 }
 
 void j(){
          lcd.setCursor(0, 1);
          lcd.print("       J        ");
          
          dot(); dash(); dash(); dash();
 }
 
 void k(){
          lcd.setCursor(0, 1);
          lcd.print("       K        ");
          
          dash();dot();dash();
 }
 
 void l(){
          lcd.setCursor(0, 1);
          lcd.print("       L        ");
          
          dot();dash();dot();dot();
 }
  void m(){
          lcd.setCursor(0, 1);
          lcd.print("       M        ");
          
          dash();dash();
 }
  void n(){
          lcd.setCursor(0, 1);
          lcd.print("       N        ");
          
          dash();dot();
 }
   void o(){
          lcd.setCursor(0, 1);
          lcd.print("       O        ");
          
          dash();dash();dash();
 }
   void p(){
          lcd.setCursor(0, 1);
          lcd.print("       P        ");
          
          dot();dash();dash();dot();
 }
   void q(){
          lcd.setCursor(0, 1);
          lcd.print("       Q        ");
          
          dash();dash();dot();dash();
 }

    void r(){
          lcd.setCursor(0, 1);
          lcd.print("       R        ");
          
          dot();dash();dot();
 }
 
    void s(){
          lcd.setCursor(0, 1);
          lcd.print("       S        ");
          
          dot();dot();dot();
 }
 
    void t(){
          lcd.setCursor(0, 1);
          lcd.print("       T        ");
          
          dash();
}
 
    void u(){
          lcd.setCursor(0, 1);
          lcd.print("       U        ");
          
          dot();dot();dash();
 }
     void v(){
          lcd.setCursor(0, 1);
          lcd.print("       V        ");
          
          dot();dot();dot();dash();
 }
 
      void w(){
          lcd.setCursor(0, 1);
          lcd.print("       W        ");
          
          dot();dash();dash();
 }
 
      void x(){
          lcd.setCursor(0, 1);
          lcd.print("       X        ");
          
          dash();dot();dot();dash();
 }
 
      void y(){
          lcd.setCursor(0, 1);
          lcd.print("       Y        ");
          
          dash();dot();dash();dash();
 }
 
      void z(){
          lcd.setCursor(0, 1);
          lcd.print("       Z        ");
          
          dash();dash();dot();dot();
 }
 
      void one(){
          lcd.setCursor(0, 1);
          lcd.print("       1        ");
          
          dot();dash();dash();dash();dash();
 }
 
      void two(){
          lcd.setCursor(0, 1);
          lcd.print("       2        ");
          
          dot();dot();dash();dash();dash();
 }
 
