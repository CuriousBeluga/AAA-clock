#include <ezButton.h> //for switch control
#include <Adafruit_NeoPixel.h> //for led control
#include <Servo.h> // for motor control
#include <LiquidCrystal_I2C.h> //for LCD screen

#define LED_PIN 52
#define LED_COUNT 8

//create the led object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//create the lcd object
LiquidCrystal_I2C lcd(0x27, 16, 2); // create LCD with I2C address 0x27, 16 characters per line, 2 lines

ezButton limitSwitch1(2); // assigning all buttons to their ports;
ezButton limitSwitch2(3);
ezButton limitSwitch3(4);
ezButton limitSwitch4(5);
ezButton limitSwitch5(6);
ezButton limitSwitch6(7);
ezButton limitSwitch7(8);
ezButton limitSwitch8(9);

// create two servo object to control
Servo myservo1;
Servo myservo2;

const int seq_count = 4; //number of sequences
int sequence[seq_count]; //the size of array determines number of button presses in game
int your_sequence[seq_count]; //user-input values, same array size
int level = 1; //number of rounds in the game
int n = 500;
int velocity = 1000; //controls the pace of the sequences time

void setup() {
 Serial.begin(9600);
 limitSwitch1.setDebounceTime(50); // set debounce time to 50 milliseconds
 limitSwitch2.setDebounceTime(50);
 limitSwitch3.setDebounceTime(50);
 limitSwitch4.setDebounceTime(50);
 limitSwitch5.setDebounceTime(50);
 limitSwitch6.setDebounceTime(50);
 limitSwitch7.setDebounceTime(50);
 limitSwitch8.setDebounceTime(50);
 //initialize pin for servos
 myservo1.attach(10);
 myservo2.attach(11);
 //initialize pin 17 for speaker output
 pinMode(17, OUTPUT);
lcd.init(); // initialize lcd
lcd.backlight(); // switch-on lcd backlight
 strip.begin();

//initiate pin for random seed generation
pinMode(A8,INPUT);

}
//---------------------------------------------------------------------------------------
void loop() {
//clear all the leds
strip.clear();
for(int i = 0;i<=7;i++)
{
strip.setPixelColor(i, 0, 0 , 0);
}
//time to initialize wake up!!
noTone(42);//clear the reset
music();
lcd.clear(); // clear LCD display
 lcd.setCursor(0, 0);
 lcd.print("WAKE UPPPP!!");
 delay(1000);
lcd.clear(); // clear LCD display
 lcd.setCursor(0, 0);
 lcd.print("It's 7:30 AM!!");
 lcd.setCursor(0, 1);
 lcd.print("Wake up!!");
Serial.println("music done");
 move_bot();
Serial.println("Movement complete");
Serial.println("Finding user input");

strip.setPixelColor(4, strip.Color(0, 145, 0));; //define color R,G,B
strip.show();
for (int trigger = 0; trigger<1;)
 {
 Serial.println("In loop");
 tone(17,440);

limitSwitch5.loop(); // MUST call the loop() function first
//int state_on = limitSwitch5.getState();
//
//Serial.print(state_on);
 if (limitSwitch5.isReleased())
 {
 trigger = 1;
 Serial.println("This is trigger value: ");
 Serial.println(trigger);
strip.setPixelColor(4, strip.Color(0, 0 , 0) ); //define color R,G,B
strip.show();
 }
 }
 generate_sequence();//generate a sequence
 show_sequence(); //show the sequence
 get_sequence(); //user inputs the sequence

} //void loop end
//--------------------------------------------------------------------------------------------------
//music time hahaha
void music()
{
//for (int i = 0; i <= 10; i++)
//
// {
 //Let the music begin
 // Whoop up
 for (int hz = 440; hz < 1000; hz += 25) {
 tone(17, hz, 50);
 delay(5);
 // Whoop down
 for (int hz = 1000; hz > 440; hz -= 25) {
 tone(17, hz, 50);
 delay(5);
 }
 }
 //}
}
//----------------------------------------------------------------
//move robot move!
void move_bot()
{
for (int i = 0; i <= 1000; i++) {
 int control = 10;
 int pos1 = 90 + control;
 int pos2 = 90 - control;
 myservo1.write(pos1);
 myservo2.write(pos2);
 }
 delay(500);
 for (int i = 0; i <= 1000; i++) {
 int control = 10;
 int pos1 = 90 + control;
 int pos2 = 90;
 myservo1.write(pos1);
 myservo2.write(pos2);
 }
 delay(500);
 for (int i = 0; i <= 1000; i++) {
 int control = 10;
 int pos1 = 90 + control;
 int pos2 = 90 - control;
 myservo1.write(pos1);
 myservo2.write(pos2);
 }
 for (int i = 0; i <= 1000; i++) {
 int control = 10;
 int pos1 = 90;
 int pos2 = 90 - control;
 myservo1.write(pos1);
 myservo2.write(pos2);
 }
}
//----------------------------------------------------------------
void generate_sequence()
{
randomSeed(analogRead(A8)); //using pin Noise to create random seed for rand generator
Serial.println("Sequence generated");
for (int i = 0; i < seq_count; i++)
{
sequence[i] = random(0,8); //create random numbers from 1 to 8, corresponding to buttons 1-8
Serial.println(sequence[i]+1);
}
}
//---------------------------------------------------------------------
void show_sequence()
{
lcd.clear(); // clear LCD display
 lcd.setCursor(0, 0);
 lcd.print("Showing Sequence");

for (int i = 0; i < seq_count; i++)
{
strip.setPixelColor(sequence[i], strip.Color(255, 0 , 255) ); //define color R,G,B
strip.show();
Serial.println("Sequence is shown");
Serial.println(sequence[i]+1);
delay(velocity);
strip.setPixelColor(sequence[i],strip.Color(0,0,0));
 strip.show();
 delay(150);
}
}
//----------------------------------------------------------------
//user input sequence
void get_sequence()
{
lcd.clear();
 lcd.setCursor(1, 0);
 lcd.print("Enter sequence");

for (int i = 0; i<seq_count;)
{
 limitSwitch1.loop(); // MUST call the loop() function first
 limitSwitch2.loop();
 limitSwitch3.loop();
 limitSwitch4.loop();
 limitSwitch5.loop();
 limitSwitch6.loop();
 limitSwitch7.loop();
 limitSwitch8.loop();

int state1 = limitSwitch1.getState(); //getting the states for each of the switches
int state2 = limitSwitch2.getState();
int state3 = limitSwitch3.getState();
int state4 = limitSwitch4.getState();
int state5 = limitSwitch5.getState();
int state6 = limitSwitch6.getState();
int state7 = limitSwitch7.getState();
int state8 = limitSwitch8.getState();
// Serial.print("State 1: ");
// Serial.println(state1);
// Serial.print("State 2: ");
// Serial.println(state2);
// Serial.print("State 3: ");
// Serial.println(state3);
// Serial.print("State 4: ");
// Serial.println(state4);
// Serial.print("State 5: ");
// Serial.println(state5);
// Serial.print("State 6: ");
// Serial.println(state6);
// Serial.print("State 7: ");
// Serial.println(state7);
// Serial.print("State 8: ");
// Serial.println(state8);
//
//---------------------------------------------------------------------------------------------
//Logic for how the colors on the rgb strip will work
 //if(state1 == LOW)
//-----------------------------------
 //Button 1
 if(limitSwitch1.isReleased())

 {

 Serial.println("Button 1 is pressed");
 strip.setPixelColor(0, 0, 0 , 255);
 strip.show();
 delay(200);

 your_sequence[i] = 0;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }

 i++;
 strip.setPixelColor(0, 0, 0, 0);
 strip.show();

 delay(n);

 }
 //-----------------------------------
 //Button 2
 if(limitSwitch2.isReleased())
 {
 Serial.println("Button 2 is pressed");
 strip.setPixelColor(1, 63, 76 , 124);
 strip.show();
 delay(1000);

 your_sequence[i] = 1;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;

 strip.setPixelColor(1, 0, 0, 0);
 strip.show();

 delay(n);
 }
 //-----------------------------------
 //Button 3
 if(limitSwitch3.isReleased())
 {
 Serial.println("Button 3 is pressed");
 strip.setPixelColor(2, 65, 98 , 32);
 strip.show();
 delay(200);
 your_sequence[i] = 2;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;

 strip.setPixelColor(2, 0, 0, 0);
 strip.show();
 delay(n);

 }

 //-----------------------------------
 //Button 4
 if(limitSwitch4.isReleased())
 {
 Serial.println("Button 4 is pressed");
 strip.setPixelColor(3, 140, 67 , 32);
 strip.show();
 delay(200);
 your_sequence[i] = 3;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;

 strip.setPixelColor(3, 0, 0, 0);
 strip.show();
 delay(n);
 }
//-----------------------------------
 //Button 5

 if(limitSwitch5.isReleased())
 {
 Serial.println("Button 5 is pressed");
 strip.setPixelColor(4, 12, 200 , 255);
 strip.show();
 delay(200);
 your_sequence[i] = 4;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;
 strip.setPixelColor(4, 0, 0, 0);
 strip.show();
 delay(n);
 }
//-----------------------------------
 //Button 6

 if(limitSwitch6.isReleased())
 {
 Serial.println("Button 6 is pressed");
 strip.setPixelColor(5, 234, 126 , 255);
 strip.show();
 delay(200);
 your_sequence[i] = 5;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;

 strip.setPixelColor(5, 0, 0, 0);
 strip.show();
 delay(n);
 }
//-----------------------------------
 //Button 7

 if(limitSwitch7.isReleased())
 {
 Serial.println("Button 7 is pressed");
 strip.setPixelColor(6, 173, 127 , 23);
 strip.show();
 delay(200);
 your_sequence[i] = 6;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;

 strip.setPixelColor(6, 0, 0, 0);
 strip.show();
 delay(n);
 }
//-----------------------------------
 //Button 8

 if(limitSwitch8.isReleased())
 {
 Serial.println("Button 8 is pressed");
 strip.setPixelColor(7, 189, 98 , 25);
 strip.show();
 delay(200);
 your_sequence[i] = 7;
 if (your_sequence[i] != sequence[i])
 {
 wrong_sequence();
 return;
 }
 i++;
 strip.setPixelColor(7, 0, 0, 0);
 strip.show();
 delay(n);
 }
} //for loop end
right_sequence(); // play celebration
} //get sequence end
//-----------------------------------------------------------------------
//display the wrong sequence end condition
void wrong_sequence()
{

lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Wrong! HAHA");
 lcd.setCursor(0, 1);
 lcd.print("You're Wrong!");
 music();

Serial.println("Wrong Sequence Detected");
 for (int n =0; n<4;n++)
 {

 //create a sea of red
 strip.setPixelColor(0,strip.Color(255, 0,0));
 strip.setPixelColor(1,strip.Color(255, 0, 0));
 strip.setPixelColor(2,strip.Color(255, 0,0));
 strip.setPixelColor(3,strip.Color(255, 0, 0));
 strip.setPixelColor(4,strip.Color(255, 0,0));
 strip.setPixelColor(5,strip.Color(255, 0, 0));
 strip.setPixelColor(6,strip.Color(255, 0,0));
 strip.setPixelColor(7,strip.Color(255, 0, 0));
 strip.show();
delay(500);
 strip.setPixelColor(0,strip.Color(0, 0,0));
 strip.setPixelColor(1,strip.Color(0, 0, 0));
 strip.setPixelColor(2,strip.Color(0, 0,0));
 strip.setPixelColor(3,strip.Color(0, 0, 0));
 strip.setPixelColor(4,strip.Color(0, 0,0));
 strip.setPixelColor(5,strip.Color(0, 0, 0));
 strip.setPixelColor(6,strip.Color(0, 0,0));
 strip.setPixelColor(7,strip.Color(0, 0, 0));
 strip.show();
delay(500);
}
level = 1;
velocity = velocity - 100; //maybe decrease the time to punish the user hahaha
lcd.clear();
 lcd.setCursor(0, 0);
lcd.print("try again fool");
} //wrong sequence end
//-------------------------------------------------------------------------------
//display the right sequence celebration
void right_sequence()
{
noTone(17);
tone(42,365);
Serial.println("Congrats you have won!");
for (int n =0; n<5;n++)
 {

 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("You are");
 lcd.setCursor(0, 1);
 lcd.print("awake haha!");

 //create a mix of colors
 strip.setPixelColor(0,strip.Color(0, 0,255));
 strip.setPixelColor(1,strip.Color(0, 255, 0));
 strip.setPixelColor(2,strip.Color(0, 0,255));
 strip.setPixelColor(3,strip.Color(0, 255, 0));
 strip.setPixelColor(4,strip.Color(0, 0,255));
 strip.setPixelColor(5,strip.Color(0, 255,0 ));
 strip.setPixelColor(6,strip.Color(0, 0,255));
 strip.setPixelColor(7,strip.Color(0, 255, 0));
 strip.show();
delay(200);
 strip.setPixelColor(0,strip.Color(23, 44,35));
 strip.setPixelColor(1,strip.Color(0, 0, 98));
 strip.setPixelColor(2,strip.Color(0, 34,0));
 strip.setPixelColor(3,strip.Color(255, 23, 0));
 strip.setPixelColor(4,strip.Color(56, 100,53));
 strip.setPixelColor(5,strip.Color(204, 55, 25));
 strip.setPixelColor(6,strip.Color(0, 0,45));
 strip.setPixelColor(7,strip.Color(0, 34, 0));
 strip.show();
delay(200);
 }
strip.clear();
lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Press to ");
 lcd.setCursor(0, 1);
 lcd.print("play again!");


strip.setPixelColor(0, strip.Color(0, 145, 0));; //define color R,G,B
strip.show();
for (int trigger = 0; trigger<1;)
 {
 Serial.println("In loop");

limitSwitch1.loop(); // MUST call the loop() function first
//int state_on = limitSwitch5.getState();
//
//Serial.print(state_on);
 if (limitSwitch1.isReleased())
 {
 trigger = 1;
 Serial.println("This is trigger value: ");
 Serial.println(trigger);
strip.setPixelColor(0, strip.Color(0, 0 , 0) ); //define color R,G,B
strip.show();
strip.clear();
 }

 }
} //right sequence end