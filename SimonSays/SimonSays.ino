/*Simon Says game. Now with sound effects. 

Originaly made by Robert Spann
Code trimmed and sound effects added by digimike

Buttons are to be set on there designated pins without pull down resistors
and connected to ground rather then +5. 
*/

// Turn debug mode on or off; this toggles serial monitor printing.
const boolean DEBUG = true;
const boolean SOUND = false;

#include <Tone.h>
Tone speakerpin;
int starttune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4};
int duration2[] = {100, 200, 100, 200, 100, 400, 100, 100, 100, 100, 200, 100, 500};
int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int duration[] = {100, 100, 100, 300, 100, 300};

int button[] = {6, 7, 8, 9}; //The four button input pins
int ledpin[] = {2, 3, 4, 5};  // LED pins
int turn = 0;  // turn counter
int buttonstate = LOW;  // button state checker
int randomArray[100]; //Intentionally long to store up to 100 inputs (doubtful anyone will get this far)
int inputArray[100];  
int show = 500 ; // Show the led for
int gap = 200 ; // Gap between
const int TOTAL_LIVES = 3;
int lives = TOTAL_LIVES;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 20000;

void setup() 
{
  if (DEBUG) Serial.begin(9600);
  speakerpin.begin(12); // speaker is on pin 13

  for(int x=0; x<4; x++)  // LED pins are outputs
  {
    pinMode(ledpin[x], OUTPUT);
  }
  
  for(int x=0; x<4; x++) 
  {
    if (DEBUG) Serial.print("ButtonPin: ");
    if (DEBUG) Serial.println(button[x]);
      
    pinMode(button[x], INPUT);  // button pins are inputs
    digitalWrite(button[x], HIGH);  // enable internal pullup; buttons start in high position; logic reversed
  }

  randomSeed(analogRead(0)); //Added to generate "more randomness" with the randomArray for the output function
  for (int thisNote = 0; thisNote < 13; thisNote ++) {
     // play the next note:
     if (SOUND) speakerpin.play(starttune[thisNote]);
     // hold the note:
     if (thisNote==0 || thisNote==2 || thisNote==4 || thisNote== 6)
     {
       digitalWrite(ledpin[0], HIGH);
     }
     if (thisNote==1 || thisNote==3 || thisNote==5 || thisNote== 7 || thisNote==9 || thisNote==11)
     {
       digitalWrite(ledpin[1], HIGH);
     }
     if (thisNote==8 || thisNote==12)
     {
       digitalWrite(ledpin[2], HIGH);
     }  
     if (thisNote==10)
     {   
       digitalWrite(ledpin[3], HIGH);
     }
     delay(duration2[thisNote]);
     // stop for the next note:
     if (SOUND) speakerpin.stop();

    
     digitalWrite(ledpin[0], LOW);
     digitalWrite(ledpin[1], LOW);
     digitalWrite(ledpin[2], LOW);
     digitalWrite(ledpin[3], LOW);
     delay(25);
    }
  delay(1000);
}
 
void loop() 
{   
  for (int y=0; y<=99; y++)
  {
    //function for generating the array to be matched by the player
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
  
    for (int thisNote = 0; thisNote < 6; thisNote ++) {
     // play the next note:
     if (SOUND) speakerpin.play(note[thisNote]);
     // hold the note:
     delay(duration[thisNote]);
     // stop for the next note:
     if (SOUND) speakerpin.stop();
     delay(25);
    }
    
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    delay(1000);
  
    for (int y=turn; y <= turn; y++)
    { //Limited by the turn variable
      Serial.println(""); //Some serial output to follow along
      Serial.print("Turn: ");
      Serial.print(y);
      Serial.println(" ");

      digitalWrite(ledpin[0], HIGH);
      digitalWrite(ledpin[1], HIGH);
      digitalWrite(ledpin[2], HIGH);
      digitalWrite(ledpin[3], HIGH);
    
      randomArray[y] = random(1, 5); //Assigning a random number (1-4) to the randomArray[y], y being the turn count
      for (int x=0; x <= turn; x++)
      {

        Serial.print(randomArray[x]);
        Serial.print(" ");
        for(int y=0; y<4; y++)
        {
      
          if (randomArray[x] == 1 && ledpin[y] == ledpin[0]) 
          {  //if statements to display the stored values in the array
            digitalWrite(ledpin[y], LOW);
            if (SOUND) speakerpin.play(NOTE_G3, 100);
            delay(show);
            digitalWrite(ledpin[y], HIGH);
            delay(gap);
          }

          if (randomArray[x] == 2 && ledpin[y] == ledpin[1]) 
          {
            digitalWrite(ledpin[y], LOW);
            if (SOUND) speakerpin.play(NOTE_A3, 100);
            delay(show);
            digitalWrite(ledpin[y], HIGH);
            delay(gap);
          }
  
          if (randomArray[x] == 3 && ledpin[y] == ledpin[2]) 
          {
            digitalWrite(ledpin[y], LOW);
            if (SOUND) speakerpin.play(NOTE_B3, 100);
            delay(show);
            digitalWrite(ledpin[y], HIGH);
            delay(gap);
          }

          if (randomArray[x] == 4 && ledpin[y] == ledpin[3]) 
          {
            digitalWrite(ledpin[y], LOW);
            if (SOUND) speakerpin.play(NOTE_C4, 100);
            delay(show);
            digitalWrite(ledpin[y], HIGH);
            delay(gap);
          }
        }
      }
    }
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    Serial.println("");
    input();
  }
}
 
 
 
void input() { //Function for allowing user input and checking input against the generated array

  int error = 0 ;
  for (int x=0; x <= turn;)
  { //Statement controlled by turn count

    for(int y=0; y<4; y++)
    {
      
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        sickofwaiting() ;
        previousMillis = currentMillis;
       }
       
      buttonstate = digitalRead(button[y]);
    
      if (buttonstate == LOW && button[y] == button[0])
      { //Checking for button push
        digitalWrite(ledpin[0], HIGH);
        if (SOUND) speakerpin.play(NOTE_G3, 100);
        delay(200);
        digitalWrite(ledpin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        Serial.print(" ");
        Serial.print(1);
        if (inputArray[x] != randomArray[x]) { //Checks value input by user and checks it against
          fail(); 
          if (DEBUG) Serial.println("fail returned");
          error = 1 ;
          turn--; //the value in the same spot on the generated array
        } else {                                     //The fail function is called if it does not match
          x++;
        }
      }
       if (buttonstate == LOW && button[y] == button[1])
      {
        digitalWrite(ledpin[1], HIGH);
        if (SOUND) speakerpin.play(NOTE_A3, 100);
        delay(200);
        digitalWrite(ledpin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        Serial.print(" ");
        Serial.print(2);
        if (inputArray[x] != randomArray[x]) {
          fail();
          error = 1 ;
          turn--;
        } else {                                     //The fail function is called if it does not match
          x++;
        }
      }

      if (buttonstate == LOW && button[y] == button[2])
      {
        digitalWrite(ledpin[2], HIGH);
        if (SOUND) speakerpin.play(NOTE_B3, 100);
        delay(200);
        digitalWrite(ledpin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        Serial.print(" ");
        Serial.print(3);
        if (inputArray[x] != randomArray[x]) {
          fail();
          error = 1 ;
          turn--;
        } else {                                     //The fail function is called if it does not match
          x++;
        }
      }

      if (buttonstate == LOW && button[y] == button[3])
      {
        digitalWrite(ledpin[3], HIGH);
        if (SOUND) speakerpin.play(NOTE_C4, 100);
        delay(200);
        digitalWrite(ledpin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        Serial.print(" ");
        Serial.print(4);
        if (inputArray[x] != randomArray[x]) 
        {
          fail();
          error = 1 ;
          turn--;
        } else {                                     //The fail function is called if it does not match
          x++;
        }
      }

    }
  }
  if (error > 0) {
  if (DEBUG) Serial.println("in error ");
  }
  delay(500);
  turn++; //Increments the turn count, also the last action before starting the output function over again
}

void fail() { //Function used if the player fails to match the sequence

    if (DEBUG) Serial.println("Fail");
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    if (SOUND) speakerpin.play(NOTE_G3, 300);
    delay(gap);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    if (SOUND) speakerpin.play(NOTE_C3, 300);
    delay(gap);

    // Remove a life from the current total.
    lives--;
    if (DEBUG) Serial.print("Lives left :");
    if (DEBUG) Serial.println(lives);
    
    // Turn on the next red LED.
    if (lives == TOTAL_LIVES - 1) ; // digitalWrite(RED_1, HIGH);
    else if (lives == TOTAL_LIVES - 2) ; //  digitalWrite(RED_2, HIGH);
    else if (lives == TOTAL_LIVES - 3) ; //digitalWrite(RED_3, HIGH);
    delay(gap);

    if (lives == TOTAL_LIVES - 3) {
      endofgame();
    }
   if (DEBUG) Serial.println("fail Done");
}


void endofgame() { //Function used if the player fails to match the sequence

  if (DEBUG) Serial.println("End of game");
  for (int y=0; y<=2; y++)
  { //Flashes lights for failure
    
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    if (SOUND) speakerpin.play(NOTE_G3, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    if (SOUND) speakerpin.play(NOTE_C3, 300);
    delay(200);
  }
  delay(500);
  turn = -1; //Resets turn value so the game starts over without need for a reset button
}


void sickofwaiting() { //Function used if the player fails to match the sequence

  if (DEBUG) Serial.println("Sick of waiting");
  for (int y=0; y<=2; y++)
  { //Flashes lights for failure
    
    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    if (SOUND) speakerpin.play(NOTE_G3, 300);
    delay(200);
    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
    if (SOUND) speakerpin.play(NOTE_C3, 300);
    delay(200);
  }

    digitalWrite(ledpin[0], HIGH);
    digitalWrite(ledpin[1], HIGH);
    digitalWrite(ledpin[2], HIGH);
    digitalWrite(ledpin[3], HIGH);
    
  int alive = 0 ;
  do
  {
    delay(50);          // wait for sensors to stabilize
        for(int y=0; y<4; y++)
    {
      buttonstate = digitalRead(button[y]);
      if (buttonstate == LOW && button[y] == button[0]){
        alive = 1 ;
        if (DEBUG) Serial.println("button[0]");
      }
      
      if (buttonstate == LOW && button[y] == button[1]){
        alive = 1 ;
      }

      if (buttonstate == LOW && button[y] == button[2]){
        alive = 1 ;
      }

      if (buttonstate == LOW && button[y] == button[3]){
        alive = 1 ;
      }
    }

  } while (alive < 1);

    digitalWrite(ledpin[0], LOW);
    digitalWrite(ledpin[1], LOW);
    digitalWrite(ledpin[2], LOW);
    digitalWrite(ledpin[3], LOW);
  delay (500);

    
}


