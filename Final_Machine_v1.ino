#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////XXXXXXXXXXX((STRING CONTANTS ))/////////////////////////////////////////////////

String new_line0a = "       WELCOME TO  ";
String new_line0b = "    ******AJF*****";


//////////////////////XXXXXXXXXX(((INTEGER CONSTANTS )))XXXXXXXXXXXXXXXXXXXXXXXXX//////////////////////////


const int A = 8, B = 9, C = 10, D = 11; // the number of the pushbutton pin
int A_STATE, B_STATE, C_STATE, D_STATE = 0;    // variable for reading the pushbutton status
int c_cnt;
int addr;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;
int tmr=0;

    

/////////////////////XXXXXXXXXXXXXXXX((( CUSTOM FUNCTIONS )))XXXXXXXXXXXXXXXXXXXX//////////////////////////


void ch_bits()
{
  A_STATE = digitalRead(A);
  B_STATE = digitalRead(B);
  C_STATE = digitalRead(C);
  D_STATE = digitalRead(D);

}

void WriteEpInt(int location , int value){
  EEPROM.write(location, value);
  EEPROM.write(location + 1, value >> 8);
}

int ReadEpInt(int location){
  int val;

  val = (EEPROM.read(location + 1) << 8);
  val |= EEPROM.read(location);

  return val;
}


/////////////////////XXXXXXXXXXXXXXXX(((BOOT WARMUP )))XXXXXXXXXXXXXXXX/////////////////


void setup()
{
  
  Serial.begin(9600);   // Initialize Serial Communication
  addr=0;
  
//////////////////////COUNTER INITIALISATION //////////////////////////////////////////

       c_cnt=ReadEpInt(addr);
//     WriteEpInt(addr,c_cnt);
//     Serial.println(ReadEpInt(addr));

////////////////////////////////////////////////////////////////////////////////////

  lcd.init();                      // initialize the lcd
                                   // Print a message to the LCD.
  lcd.backlight();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0, 1);
  lcd.print("   WELCOME TO AJF");
  lcd.setCursor(0,2);
  lcd.print("     AUTOMATION");
  lcd.setCursor(0, 3);
  lcd.print("********************");
 
  delay (2000); //// BOOT DELAY 
  lcd.clear();  /// CLEANOUT 

  // // initialize the pushbutton pin as an input:////////////////////////////////

  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);

  A_STATE = digitalRead(A);
  B_STATE = digitalRead(B);
  C_STATE = digitalRead(C);
  D_STATE = digitalRead(D);

tmr=0;

}

//////////////////////////////XXXXXXXXXXXXX(((MAIN CODE CYCLE)))XXXXXXXXXXXXXX///////////

void loop()
{

      ch_bits(); // check the pin status every cycle startup
 
      unsigned long currentTime = millis();
 
 if (currentTime - previousTime >= eventInterval)
 {
      tmr++;
      previousTime = currentTime;

 }

/////////////////////////////////////////// WHAT IF ?(0000) /////////////////////////////////
//standby stuff ( if machine on emergency reset condition )

if (A_STATE == LOW && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW) 
{
   
      lcd.clear();
      lcd.noBlink();
      lcd.setCursor(0, 0);
      lcd.print("        AMAR");
      lcd.setCursor(0, 1);
      lcd.print("   JIGS & FIXTURE");
      lcd.setCursor(0, 2);
      lcd.print("5804 & 9994 ASSEMBLY");
      lcd.setCursor(0, 3);
      lcd.print("*..................*");
  
  while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW)
  {
    ch_bits();
  }

  
   //break; // unused 
   
}

/////////////////////////////////////////// WHAT IF ?(0001) /////////////////////////////////

else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW )
{
      tmr=0;
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);  // use it if u want to used 1st line for msg
//    lcd.print("Put gasket on ");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14, 0);
      lcd.print("01(12)");
      lcd.setCursor(0, 1);
      lcd.print("PUT GASKET & PCBA ON");
      lcd.setCursor(0, 2);
      lcd.print("FXTR CAVI & APLY FRC");
//    lcd.setCursor(0, 3);
//    lcd.print("Apply Pressure"); //use it if want last line for msg
      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
 
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
  
  while(A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW)
  {
    currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
    {
      tmr++;
      previousTime = currentTime;
    }
      ch_bits();
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
   }
}
//  /////////////////////////////////////////// WHAT IF ?(0010) /////////////////////////////////

else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW && D_STATE == LOW ) 
{
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Take 4127,and Instl");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14, 0);
      lcd.print("02(12)");
      lcd.setCursor(0, 1);
      lcd.print("CONFIG 4127 WITH RNG");
      lcd.setCursor(0, 2);
      lcd.print("INSTL HARNES ON PCB");
//    lcd.setCursor(0, 3);
//    lcd.print("IntSL harnes on PCB");
      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
  
  while(A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW && D_STATE == LOW)
  {

      currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
    {
      
      tmr++;
      previousTime = currentTime;

    }
      
      ch_bits();
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);

      
////////////////////////////////////////////////    
    if(tmr>=1000)  //reset tm(sec) when 1000 //
    tmr=0;                                   //
///////////////////////////////////////////////
      
  }
  
}
 



  /////////////////////////////////////////// WHAT IF ? (0011)/////////////////////////////////

 else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == LOW) {
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("As per VA4450-787879");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14, 0);
      lcd.print("03(12)");
      lcd.setCursor(0, 1);
      lcd.print("AS/VA4450-787879,RUT");
      lcd.setCursor(0, 2);
      lcd.print("H AS/VA,PCB445-78789"); 
//    lcd.setCursor(0, 3);
//    lcd.print("On abv assbly,Plce");
      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);

  
   while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == LOW)
    {

      currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
    {
      tmr++;
      previousTime = currentTime;

    }
      
      ch_bits();
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
    }
}


 /////////////////////////////////////////// WHAT IF ? (0100)/////////////////////////////////

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW) {
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Cble Guid On Asbly");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14, 0);
      lcd.print("04(12)");
      lcd.setCursor(0, 1);
      lcd.print("PLCE CBLE,ROUT HARNS");
      lcd.setCursor(0, 2);
      lcd.print("AS/VA ADSIV TAP");
//    lcd.setCursor(0, 3);
//    lcd.print("Routed Harnes");

      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
  
  while(A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW)
    {

       currentTime = millis();
     if (currentTime - previousTime >= eventInterval)
     {
        tmr++;
        previousTime = currentTime;

     }
      
        ch_bits();
        lcd.setCursor(10, 3);
        lcd.print("T(SEC):");
        lcd.setCursor(17, 3);
        lcd.print(tmr);
    
    }
}


  /////////////////////////////////////////// WHAT IF ? (0101)/////////////////////////////////

 else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW) {
        lcd.clear();
        lcd.noBlink();
//      lcd.setCursor(0, 0);
//      lcd.print("Instl Harnes Covr");
        lcd.setCursor(0, 0);
        lcd.print("PROGRESS:>>> ");
        lcd.setCursor(14,0);
        lcd.print("05(12)");
        lcd.setCursor(0, 1);
        lcd.print("INSTL HRNS COVER");
        lcd.setCursor(0, 2);
        lcd.print("HELP OF 3 SCREWS");

        lcd.setCursor(0, 3);
        lcd.print("C.CNT:");
        lcd.setCursor(6, 3);
        lcd.print(ReadEpInt(addr));
        lcd.setCursor(10, 3);
        lcd.print("T(SEC):");
        lcd.setCursor(17, 3);
        lcd.print(tmr);
   // delay(200);
  while(A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW)
  {


        currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
 {
        tmr++;
        previousTime = currentTime;

 }
   
        ch_bits();
        lcd.setCursor(10, 3);
        lcd.print("T(SEC):");
        lcd.setCursor(17, 3);
        lcd.print(tmr);
 }
 
//      break;

}





  /////////////////////////////////////////// WHAT IF ? (0110)/////////////////////////////////

 else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW) {
    
       lcd.clear();
       lcd.noBlink();
//     lcd.setCursor(0, 0);
//     lcd.print("Unlok abv assbly");
       lcd.setCursor(0, 0);
       lcd.print("PROGRESS:>>> ");
       lcd.setCursor(14, 0);
       lcd.print("06(12)");
       lcd.setCursor(0, 1);
       lcd.print("UNLOK CAVI A & INSTL");
       lcd.setCursor(0, 2);
       lcd.print("HOUSING,NOTCH FIT");
//     lcd.setCursor(0, 3);
//     lcd.print("Notch fit"); 

       lcd.setCursor(0, 3);
       lcd.print("C.CNT:");
       lcd.setCursor(6, 3);
       lcd.print(ReadEpInt(addr));
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr); 
//     delay(200);
 
 while(A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW)
  {

      currentTime = millis();
   if (currentTime - previousTime >= eventInterval)
   {
      tmr++;
      previousTime = currentTime;
 }
      
      ch_bits();
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
   }
   
//    break;
  
 }



/////////////////////////////////////////// WHAT IF ? (1110)/////////////////////////////////0

 else  if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW) {
    
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Align hol to");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14,0);
      lcd.print("07(12)");
      lcd.setCursor(0, 1);
      lcd.print("ALIGN HOL TO INSTL");
      lcd.setCursor(0, 2);
      lcd.print("1 SCREW ON HOUSING");

      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
      
//    delay(200);

  while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW)
  
  {

      currentTime = millis();
 if (currentTime - previousTime >= eventInterval)
 {
      tmr++;
      previousTime = currentTime;

 }
      
      ch_bits();  
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
   
    }
  
 }


//////////////////////////////////////////// WHAT IF ? (1000)/////////////////////////////////

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH) 
{
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Plac Unit in B ");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14,0);
      lcd.print("08(12)");
      lcd.setCursor(0, 1);
      lcd.print("PLCE UNIT IN B CAVI");
      lcd.setCursor(0, 2);
      lcd.print("FIXTR & LOCK");

      lcd.setCursor(0, 3);
      lcd.print("C.CNT:");
      lcd.setCursor(6, 3);
      lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);

 while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH)
   {

      currentTime = millis();
  if (currentTime - previousTime >= eventInterval)
 {
      tmr++;
      previousTime = currentTime;

 }
    
        ch_bits();
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr);
    }
   
}


 /////////////////////////////////////////// WHAT IF ? (1001)/////////////////////////////////

else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH) 
{
      lcd.clear();
      lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Plc PCBA-4450789");
      lcd.setCursor(0, 0);
      lcd.print("PROGRESS:>>> ");
      lcd.setCursor(14,0);
      lcd.print("09(12)");
      lcd.setCursor(0, 1);
      lcd.print("PLCE PCBA-4450789");
      lcd.setCursor(0, 2);
      lcd.print("CNECT HRNES TO PCBA");
//    lcd.setCursor(0, 3);
//    lcd.print("PCBA");

       lcd.setCursor(0, 3);
       lcd.print("C.CNT:");
       lcd.setCursor(6, 3);
       lcd.print(ReadEpInt(addr));
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr);
  while(A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH)
  {

        currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
    {
        tmr++;
        previousTime = currentTime;

    }
    
        ch_bits();
        lcd.setCursor(10, 3);
        lcd.print("T(SEC):");
        lcd.setCursor(17, 3);
        lcd.print(tmr);
   }
}


 /////////////////////////////////////////// WHAT IF ? (0101)/////////////////////////////////


else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH) 
{
       lcd.clear();
       lcd.noBlink();
//     lcd.setCursor(0, 0);
//     lcd.print( "Instl Hosing Cvr");
       lcd.setCursor(0, 0);
       lcd.print("PROGRESS:>>> ");
       lcd.setCursor(14,0);
       lcd.print("10(12)");
       lcd.setCursor(0, 1);
       lcd.print("INSTL HOUSING CVR");
       lcd.setCursor(0, 2);
       lcd.print("CO-X CVR 21 LBA");

       lcd.setCursor(0, 3);
       lcd.print("C.CNT:");
       lcd.setCursor(6, 3);
       lcd.print(ReadEpInt(addr));
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr); 
    
 while(A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH)
  {

       currentTime = millis();
   if (currentTime - previousTime >= eventInterval)
 {
       tmr++;
       previousTime = currentTime;

 }
    
       ch_bits();
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr);
  }
}
  
 /////////////////////////////////////////// WHAT IF ? (1101)/////////////////////////////////

else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH) {
       lcd.clear();
    
       lcd.noBlink();   
//     lcd.setCursor(0, 0);
//     lcd.print("ORING DIP On &");
       lcd.setCursor(0, 0);
       lcd.print("PROGRESS:>>> ");
       lcd.setCursor(14,0);
       lcd.print("11(12)");
       lcd.setCursor(0, 1);
       lcd.print("ORING DIP & 4SREW ");
       lcd.setCursor(0, 2);
       lcd.print("ON CBLE GUIDE COVER");
//     lcd.setCursor(0,3);
//     lcd.print("Guide cvr");

       lcd.setCursor(0, 3);
       lcd.print("C.CNT:");
       lcd.setCursor(6, 3);
       lcd.print(ReadEpInt(addr));
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr); 
 while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH)
  {

       currentTime = millis();
   if (currentTime - previousTime >= eventInterval)
    {
       tmr++;
       previousTime = currentTime;

     }
    
       ch_bits();
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr);
  }
}


/////////////////////////////////////////// WHAT IF ? (0011)/////////////////////////////////

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH) {
       lcd.clear();
       lcd.noBlink();
       lcd.setCursor(0, 0);
       lcd.print("PROGRESS:>>> ");
       lcd.setCursor(14,0);
       lcd.print("12(12)");
       lcd.setCursor(5, 1);
       lcd.print("TASK DONE");
       c_cnt++;
       WriteEpInt(addr,c_cnt);
       
//     Serial.println(ReadEpInt(addr));   //serial link for debug production counter
    
        lcd.setCursor(0, 3);
        lcd.print("C.CNT:");
        lcd.setCursor(6, 3);
        lcd.print(ReadEpInt(addr));
        lcd.setCursor(10, 3);
        lcd.print("T(SEC):");
        lcd.setCursor(17, 3);
        lcd.print(tmr);
//      delay(200);
  
  while(A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH)
  {


       currentTime = millis();
    if (currentTime - previousTime >= eventInterval)
    {
       tmr++;
       previousTime = currentTime;

    }
       ch_bits();
       lcd.setCursor(10, 3);
       lcd.print("T(SEC):");
       lcd.setCursor(17, 3);
       lcd.print(tmr);
  }
    
//     break;

}

  


  /////////////////////////////////////////// WHAT IF NOTHIG ? /////////////////////////////////

//ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE

 else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("DEFAULT FOE 1101");
   
   // delay(200);
    while(A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH)
    {
    currentTime = millis();
 if (currentTime - previousTime >= eventInterval)
 {
   tmr++;
   previousTime = currentTime;

 }
      
    ch_bits();
    }
   //  break;
  }

  else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("DEFAULT FOE 1110");
   
   // delay(200);
    while(A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH)
    {

    currentTime = millis();
 if (currentTime - previousTime >= eventInterval)
 {
   tmr++;
   previousTime = currentTime;

 }
      
    ch_bits();
    }
   //  break;
  }


   else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(2, 0);
    lcd.print("TOTAL PRODUCTION");
    lcd.setCursor(8,1);
    lcd.print(ReadEpInt(addr));
    lcd.setCursor(2,2);
    lcd.print("<B1+B2> TO RESET");
        lcd.setCursor(2,3);
    lcd.print("    COUNTER");

   
   // delay(200);
    while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH)
    {
    ch_bits();
    }
        c_cnt=0;   
    WriteEpInt(addr,c_cnt); 
   
   
    
   //  break;
  }
}
