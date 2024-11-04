#include <Arduino.h>
char incomingByte; 

String incoming;

#define red 4
#define green 5
#define blue 6

// blink button
#define btn2 3
// stop button
#define btn1 2


int time;

//indicates if the game has started or not
int btnState = 0; 

String  dictionar[] = { "buna", "ziua",  "clan", "telefon", "sticla", "bilet"};



volatile int i = 0;
unsigned int  h = 0;

int score = 0;

int nr;

unsigned word1 = 0;


//

//method for randomly displaying a nre word for the game 
void newWord(){
  delay(500);
  nr = random(6);
  Serial.println(dictionar[nr]);
  String incoming = "";
  word1 = millis();
}



//method to select the difficulty, i is incremented in the interrupt
void dificultyselect(){
  if(i>2){
    i = 0;
  }

  if( i == 0){
    Serial.print("Easy\n");  
  }else if(i == 1){
    Serial.print("Medium\n");  

  }else if(i == 2){
    Serial.print("Hard\n");  
  }


}


void setup()
{
  Serial.begin(9600);




  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);


   // Enable PCIE2 Bit3 = 1 (Port D)
  PCICR |= B00000100;
  // Enable PCINT18  & PCINT19 (Pins D2 & D3)
  PCMSK2 |= B00001100;
}

void loop()
{
  

  

  if(btnState == 1){
      //initiates the game by flashing 3 times white
      for (int j = 3; j > 0; j--)
      {
        digitalWrite(red, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);
        delay(500);
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
        delay(500);
        Serial.println(j);
      }

      //generates the first word
      newWord();
      
      int startTime = millis();
        //stays in the game for 30s or until the button is pressed again to stop the game
        while( millis() - startTime <30000 && btnState == 1){
          //generates a new word if the old one is not gussed in the right amount of time (3,4,5s depending on the dificulty)
          if(millis() - word1 >= 5000 - i*1000){
                newWord();
          }
          //receives a character from serial
          if (Serial.available() > 0) {
              incomingByte = Serial.read();

          
              Serial.print(incomingByte);
              //verifies if the char is correct and only increments it if the char is correct
              
              if(dictionar[nr][h] == incomingByte){
                incoming[h] = incomingByte;
                h++;
              }else if(incomingByte == '*' ){
                
                digitalWrite(red, LOW);  
              }else{
                digitalWrite(red, HIGH);
                Serial.println("Litera Gresita!");
              }

            
              //if the number of chars is the same as the word it puts it as a correct word

              if(h == dictionar[nr].length()){
                Serial.println("");  

                Serial.println("Cuvant Corect!");  
                score++;
                digitalWrite(green, HIGH);
                delay(500);
                newWord();
                digitalWrite(green, LOW);
                h = 0;
                
              }
          }
          
        }

    //finishes the game and resets the score
    btnState = 0;
    Serial.println("Joc terminat. Scor: ");
    Serial.print(score);
    score = 0;


        

  }


  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);

  
}

//interrupt for both buttons
ISR (PCINT2_vect)
{
  // Port D Interrupt occured
  
  // Check if this was D2
  if (digitalRead(btn1) == LOW) {
    //Pin D2 triggered the ISR on a Falling pulse
    i++;
    dificultyselect();
  }

  // Check if this was D7
  if (digitalRead(btn2) == LOW) {
    //Pin D7 triggered the ISR on a Falling pulse
    btnState = !btnState; 
  }

}



