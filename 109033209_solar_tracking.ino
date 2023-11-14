#include <Servo.h>

Servo myservoX;
Servo myservoY;

#define R_B_PR 14 //right bottom,14=A0
#define R_T_PR 15 //right top,15=A1
#define L_T_PR 16 //left top,16=A2
#define L_B_PR 17 //left bottom17=A3

int analogValue[4];
byte angleX = 90, angleY = 10;

//face to LPR angleX>90 to right
//face to LPR angleY>90 to down

const int compare = 20;
void setup() {
  myservoX.attach(5);
  myservoY.attach(6);
  myservoX.write(angleX);
  myservoY.write(angleY);

  pinMode(R_B_PR, INPUT);
  pinMode(R_T_PR, INPUT);
  pinMode(L_T_PR, INPUT);
  pinMode(L_B_PR, INPUT);
  Serial.begin(115200);
}

void loop() {

  for (int i = 0 ; i < 10 ; i++) {
    analogValue[0] += analogRead(L_T_PR); 
    analogValue[1] += analogRead(R_T_PR); 
    analogValue[2] += analogRead(L_B_PR); 
    analogValue[3] += analogRead(R_B_PR); 
    delay(2);
  }

  analogValue[0] /= 10; 
  analogValue[1] /= 10; 
  analogValue[2] /= 10; 
  analogValue[3] /= 10; 



  int dirX1 = analogValue[0] - analogValue[1];
  int diffValueX1 = abs(dirX1);

  int dirX2 = analogValue[2] - analogValue[3];
  int diffValueX2 = abs(dirX2);

  //calc Y
  int dirY1 = analogValue[0] - analogValue[2];
  int diffValueY1 = abs(dirY1);

  int dirY2 = analogValue[1] - analogValue[3];
  int diffValueY2 = abs(dirY2);

  //face to LPR angleX>90 to right
  //face to LPR angleY>90 to down

  if (diffValueX1 > compare) {
    if (dirX1 > 0 && angleX > 0) {
      angleX--;
    } else if (angleX < 180) {
      angleX++;
    }
    myservoX.write(angleX);
  }
  if (diffValueY1 > compare) {
    if (dirY1 > 0 && angleY > 0) {
      angleY--;
    } else if (angleY < 180) {
      angleY++;
    }
    myservoY.write(angleY);
  }
  if (diffValueX2 > compare) {
    if (dirX2 > 0 && angleX > 0) {
      angleX--;
    } else if (angleX < 180) {
      angleX++;
    }
    myservoX.write(angleX);
  }
  if (diffValueY2 > compare) {
    if (dirY2 > 0 && angleY > 0) {
      angleY--;
    } else if (angleY < 180) {
      angleY++;
    }
    myservoY.write(angleY);
  }

  if (diffValueX1 > compare || diffValueX2 > compare || diffValueY1 > compare || diffValueY2 > compare) {
    delay(20);
  }
  Serial.print(analogValue[0]);
  Serial.print(" | ");
  Serial.println(analogValue[1]);
  Serial.println("-----------");
  Serial.print(analogValue[2]);
  Serial.print(" | ");
  Serial.println(analogValue[3]);
  Serial.println();

  analogValue[0] = 0;
  analogValue[1] = 0;
  analogValue[2] = 0;
  analogValue[3] = 0;

}