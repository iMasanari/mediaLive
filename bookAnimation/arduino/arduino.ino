int sensorPinZ = A0;
int sensorPinY = A1;
int sensorPinX = A2;

void setup(){
  // シリアルモニターの初期化をする
  Serial.begin(9600) ;
}

void loop(){
  int i;
  long x, y, z;
  //50回センサ値を読み込んで平均を算出
  x = y = z = 0;
  for (i = 0 ; i < 50 ; i++) {
    x = x + analogRead(sensorPinX); // Ｘ軸
    y = y + analogRead(sensorPinY); // Ｙ軸
    z = z + analogRead(sensorPinZ); // Ｚ軸
  }
  x = x / 50;
  y = y / 50;
  z = z / 50;
  
  int rotateX = (x - 266) / 0.75 - 90;
  int rotateY = (y - 277) / 0.75 - 90;
  int rotateZ = (z - 266) / 0.75 - 90;
  
//  Serial.print("X:");
//  Serial.print(rotateX);
//  Serial.print(" Y:");
//  Serial.print(rotateY);
//  Serial.print(" Z:");
//  Serial.println(rotateZ);

//  Serial.write(rotateZ);
  Serial.println(rotateZ);
  
  delay(50);
}
