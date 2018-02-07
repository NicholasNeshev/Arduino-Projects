/*
  Nicholas Neshev
  Dash n' Blast
  A fun game where you try and run as far as you can while dodging walls. You have a lazer gun that can shoot thin walls.
*/

void clearLight(); // clears all pixels
void dot(int row, int collumn); // draws a pixel

bool buttonPressed = false; // button press bool to assign a true or false depending on button state
int playert = 13; // collumn for the top pixel of the player
int playerb = 13; // collumn for the bottom pixel of the player
int lazerRow = -1; // row for the laser
int lazerCollumn = -1; // collumn for the laser
int lazerFrames = 0; // special delay for laser
int leftWall = -1; // edge collumn for left wall
int rightWall = -1; // edge collumn for right wall  
int firstWall = 2; // row for bottom wall 
int wallFrames = 0; // special delay for walls

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // magical number
  // sets all pins to output
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  if(leftWall == -1 && rightWall == -1) // checks to see if wall variables are clear
  {
    leftWall = random(13, 19); // assigns random value to leftWall
    switch(leftWall) // assigns value to rightWall based on leftWall value to ensure a 3-space gap
    {
      case 13:
      rightWall = 9;
      break;
      case 14:
      rightWall = 10;
      break;
      case 15:
      rightWall = 11;
      break;
      case 16:
      rightWall = 12;
      break;
      case 17:
      rightWall = 13;
      break;
      case 18:
      rightWall = 14;
      break;
    }
  }
  if(!(leftWall == -1 && rightWall == -1)) // checks to see if leftWall and rightWall have values
  {
    // displays first wall row
    dot(firstWall, leftWall);
    dot(firstWall, leftWall+1);
    dot(firstWall, leftWall+2);
    dot(firstWall, leftWall+3);
    dot(firstWall, leftWall+4);
    dot(firstWall, rightWall);
    dot(firstWall, rightWall-1);
    dot(firstWall, rightWall-2);
    dot(firstWall, rightWall-3);
    dot(firstWall, rightWall-4);
    
    // displays second wall row
    dot(firstWall - 1, leftWall);
    dot(firstWall - 1, leftWall+1);
    dot(firstWall - 1, leftWall+2);
    dot(firstWall - 1, leftWall+3);
    dot(firstWall - 1, leftWall+4);
    dot(firstWall - 1, rightWall);
    dot(firstWall - 1, rightWall-1);
    dot(firstWall - 1, rightWall-2);
    dot(firstWall - 1, rightWall-3);
    dot(firstWall - 1, rightWall-4);

    // displays third wall row
    dot(firstWall - 2, leftWall);
    dot(firstWall - 2, leftWall+1);
    dot(firstWall - 2, leftWall+2);
    dot(firstWall - 2, leftWall+3);
    dot(firstWall - 2, leftWall+4);
    dot(firstWall - 2, rightWall);
    dot(firstWall - 2, rightWall-1);
    dot(firstWall - 2, rightWall-2);
    dot(firstWall - 2, rightWall-3);
    dot(firstWall - 2, rightWall-4);

    wallFrames++; // increases value for special delay
    if(wallFrames >= 35) // checks to see if special delay has reached special value
    {
      firstWall++; // moves all 3 wall rows down 1 pixel
      wallFrames = 0; // resets special delay
    }
  }
  // checks to see if the player has hit the wall
  if((firstWall == 9 || firstWall == 8 || firstWall - 1 == 9 || firstWall - 1 == 8 || firstWall - 2 == 9 || firstWall - 2 == 8) && (playert == leftWall || playert == rightWall || playert == leftWall+1 || playert == rightWall-1 || playert == leftWall+2 || playert == rightWall-2 || playert == leftWall+3 || playert == rightWall-3 || playert == leftWall+4 || playert == rightWall-4))
  {
    // displays game over screen for a long enough time to make the player restart
    clearLight();
    dot(2, 10);
    dot(9, 17);
    delay(100000);
  }
  if(firstWall == 13) // checks if the wall has reached the bottom
  {
    // resets all values for the wall, "clears" them
    firstWall = 2;
    leftWall = -1;
    rightWall = -1;
  }
  clearLight(); // clears all pixels after displaying walls

  

  // displays player position
  dot(8, playert);
  dot(9, playerb);
  int buttonValue; // creates a variable to hold button values
  buttonValue = analogRead(A7); // assigns button values to buttonValue variable
  if(buttonValue <= 150 && buttonValue >= 130 && buttonPressed == false) // checks to see if left button is pressed and if the button is newly pressed
  {
    if(playert >= 11 && playerb >= 11) // makes sure the player isn't at edge of screen
    {
      // moves player to the right one pixel
      --playert;
      --playerb;
      buttonPressed = true; // states that the button is pressed
    }
  }
  if(buttonValue <= 510 && buttonValue >= 490 && buttonPressed == false) // checks to see if right button is pressed and if the button is newly pressed 
  {
    if(playert <= 16 && playerb <= 16) // makes sure the player isn't at edge of screen
    {
      // moves player to the left one pixel
      ++playert;
      ++playerb;
      buttonPressed = true;
    }
  }
  if(buttonValue >= 1000 && buttonPressed == true) // checks to see if no buttons are pressed and if it was just pressed
  {
    buttonPressed = false; // says button is no longer pressed
  }
  clearLight(); // clears all pixels after displaying player
  

  // handles laser
  if(buttonValue <= 750 && buttonValue >= 730) // checks to see if the spare button is pressed
  {
    if(lazerCollumn == -1 && lazerRow == -1) // checks to see if lazer variables are blank
    {
      lazerCollumn = playert; // assigns lazerCollumn to current player collumn
      lazerRow = 8; // assigns lazerRow to the row of playert
    }
  }
  if(lazerRow >= 2) // checks to see if value was applied to lazerRow and if it is not at the edge of the screen
  {
    dot(lazerRow, lazerCollumn); // displays laser position
    lazerFrames++; // increases value for special delay
    if(lazerFrames >= 25)// checks to see if special delay has reached special value
    {
      lazerRow--; // moves laser up 1 pixel
      lazerFrames = 0; // resets special delay
    }
  }
  // checks to see if the laser hit the wall
  if(lazerRow == firstWall && (lazerCollumn == leftWall || lazerCollumn == rightWall || lazerCollumn == leftWall+1 || lazerCollumn == rightWall-1 || lazerCollumn == leftWall+2 || lazerCollumn == rightWall-2 || lazerCollumn == leftWall+3 || lazerCollumn == rightWall-3 || lazerCollumn == leftWall+4 || lazerCollumn == rightWall-4))
  {
    // clears laser values, "destroying" it
    lazerCollumn = -1;
    lazerRow = -1;
  }
  if(lazerRow == 1) // checks to see if the laser hit the edge of the screen
  {
    // clears laser values, "destroying" it
    lazerCollumn = -1;
    lazerRow = -1;
  }
  clearLight(); // clears all pixels after displaying laser
}



void clearLight() // resets all collumns and rows on boards to their default values
{
  delay(1); // delays by 1 ms so that LEDs are on for long enough to produce enough light
  // resets board to default values
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
}

void dot(int row, int collumn) // displays 1 pixel
{
  digitalWrite(row, HIGH); // turns on row for pixel
  digitalWrite(collumn, LOW); // turns off collumn for pixel
}

