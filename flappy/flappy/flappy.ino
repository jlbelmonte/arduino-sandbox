#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>


// RGBmatrix constants
#define CLK 11 //change to 11 if using the Arduino Mega 2560
#define LAT 10
#define OE  9
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

//gamepad control
int button = 12;
int buttonState =0; 

//default height of the bird
int height;
boolean gameOver = true;

struct COLUMN {
  int x;
  int gap;
};

//struct COLUMN c = {32, random(2, 11)};
//struct COLUMN d = {c.x + random(5,12), random(2, 11)};
//struct COLUMN e = {d.x + random(5,12), random(2, 11)};

struct COLUMN colArray[3];


void setup() {
  matrix.begin();
  Serial.begin(9600);
  pinMode(button, INPUT);
  resetGame(true);
}

void resetGame(boolean newValue){
  gameOver = newValue;
  // set columns randomly
  struct COLUMN c = {33, random(2, 11)      };
  struct COLUMN d = {
    c.x + random(9,14), random(2, 11)      };
  struct COLUMN e = {
    d.x + random(9,16), random(2, 11)      };
  colArray[0] = c;
  colArray[1] = d;
  colArray[2] = e;
  // reset bird
  height = 6;
}


void loop() {
  matrix.fillScreen(0); //clears screen, prepares for a redraw  
  buttonState = digitalRead(button);
  if (gameOver) {
    gameOverScreen(buttonState);
  } 
  else {
    gameLoop(buttonState);
  }



  matrix.swapBuffers(false);
  delay(350);
}

void setNextCoordinates(struct COLUMN& col){
  col.x = col.x-1;

}

void gameLoop(int buttonState) {
  showBackground();
  showBird();
  // get data for next loop
  if(buttonState == HIGH){
    height-=3;
  } 
  else {
    height++;
  }

  // recalc columns and mark collision
  boolean collision = (height > 14);
  
  for ( int i = 0; i<3; i++){
    struct COLUMN& column = colArray[i];
    if(column.x == -4){
      struct COLUMN c = {36 + random(0,4), random(2, 11)      };   
      colArray[i] = c;
    } else {
      collision = collision || collidedWith(column.x, column.gap);
      drawColumn(column);
      setNextCoordinates(column);
    }
  }
  if (collision){
    gameOver=true;
  }
}

boolean collidedWith(int x, int gap) {
  if(x <=10 && x > 5){
    return (height < gap || height > gap +5 );
  }
  return false;
}
void showBackground(){
  matrix.fillRect(0,0,32,16, matrix.Color888(69, 222, 224, true));
  matrix.fillRect(0,8,32,12, matrix.Color888(224, 224, 224, true));

  matrix.drawLine(4,7,7,7, matrix.Color888(224, 224, 224, true)); 
  //clouds
  matrix.drawLine(5,6,6,6, matrix.Color888(224, 224, 224, true)); 
  matrix.drawLine(1,8,3,8, matrix.Color888(69, 222, 224, true)); 
  matrix.drawLine(15,7,17,7, matrix.Color888(224, 224, 224, true)); 
  matrix.drawLine(25,7,29,7, matrix.Color888(224, 224, 224, true)); 
  matrix.drawLine(27,6,28,6, matrix.Color888(224, 224, 224, true));
  matrix.drawLine(0, 13, 32, 13, matrix.Color888(24, 158, 7, true)); 
  //mountains
  matrix.drawLine(9, 12, 14, 12, matrix.Color888(24, 158, 7, true));
  matrix.drawLine(10, 13, 13, 13, matrix.Color888(140, 239, 152, true)); 

  matrix.drawLine(19, 12, 25, 12, matrix.Color888(24, 158, 7, true));
  matrix.drawLine(20, 13, 24, 13, matrix.Color888(140, 239, 152, true));      
  //lines
  matrix.drawLine(0, 14, 32, 14, matrix.Color888(140, 239, 152, true));    
  matrix.drawLine(0, 15, 32, 15, matrix.Color888(170, 129, 54, true)); 

}

void showBird(){
  matrix.drawLine(10, height, 10, height+1, matrix.Color888(249, 247, 4, true));
  matrix.drawLine(11, height, 11, height+1, matrix.Color888(249, 149, 0, true));
}

void drawColumn(struct COLUMN col){
  for (int i =0; i<16; i++) {
    if (i < col.gap || i> col.gap+4){
      if (i == col.gap+6 || i== col.gap-2){
        matrix.drawLine(col.x,i,col.x+3, i, matrix.Color888(169, 114, 92, true));
      } 
      else {
        matrix.drawLine(col.x,i,col.x+3, i,  matrix.Color888(169, 36, 8, true));
      }
    }
  }
}


void gameOverScreen(int buttonState){
  int x =0;
  int y =0;
  if (buttonState == HIGH){
    resetGame(false);
  }
  matrix.drawPixel(x + 1, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 2, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 3, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 7, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 8, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 11, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 18, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 20, y + 2, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 27, y + 2, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 11, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 14, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 3, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 27, y + 3, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 3, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 7, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 8, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 11, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 13, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 18, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 4, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 25, y + 4, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 26, y + 4, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 27, y + 4, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 28, y + 4, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 29, y + 4, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 11, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 5, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 27, y + 5, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 2, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 3, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 11, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 18, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 20, y + 6, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 27, y + 6, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 27, y + 7, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 2, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 3, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 10, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 13, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 14, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 18, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 8, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 26, y + 8, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 27, y + 8, matrix.Color888(224, 105, 71, true));
  matrix.drawPixel(x + 28, y + 8, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 1, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 6, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 10, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 20, y + 9, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 25, y + 9, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 26, y + 9, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 27, y + 9, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 28, y + 9, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 29, y + 9, matrix.Color888(224, 49, 6, true));
  matrix.drawPixel(x + 1, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 7, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 13, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 14, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 18, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 20, y + 10, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 25, y + 10, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 26, y + 10, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 27, y + 10, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 28, y + 10, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 29, y + 10, matrix.Color888(129, 128, 153, true));
  matrix.drawPixel(x + 1, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 7, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 9, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 19, y + 11, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 1, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 2, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 3, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 4, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 8, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 12, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 13, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 14, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 15, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 17, y + 12, matrix.Color888(224, 224, 224, true));
  matrix.drawPixel(x + 20, y + 12, matrix.Color888(224, 224, 224, true));
}



