#include <DigiMouse.h>

//マウスをわかりやすく動かすモードにする
//#define MOUSE_MOVE_RANDOM

//停止ボタンを接続する
#define CONNECT_STOP_BUTTON

#define PIN_BUTTON  0
#define PIN_LED     1

//マウスをちょっと動かすインターバル時間
unsigned int moveInterval = 1*60*1000;    //約１分おき

int previousButtonStatus = HIGH;
bool modePause = false;


void setup() {
#ifdef CONNECT_STOP_BUTTON
  pinMode(PIN_BUTTON, INPUT); 
#endif
  pinMode(PIN_LED, OUTPUT); 
  DigiMouse.begin(); //start or reenumerate USB - BREAKING CHANGE from old versions that didn't require this
}

bool checkButton()
{
#ifdef CONNECT_STOP_BUTTON
  int buttonStatus = digitalRead(PIN_BUTTON);
  if(buttonStatus == LOW && buttonStatus != previousButtonStatus){
    modePause = !modePause;
    previousButtonStatus = buttonStatus;
    return true;
  }
  previousButtonStatus = buttonStatus;
#endif
  return false;
}

#ifdef MOUSE_MOVE_RANDOM
void moveMouse(int x,int y,int distance,int speed)
{
  static unsigned int ledCount = 0;
  if(x==0 && y==0) return;
  for(int i=0;i<distance;i++)
  {
    
    DigiMouse.move(x, y, 0);
    DigiMouse.delay(speed);
    ledCount += speed;

    digitalWrite(PIN_LED,((ledCount>>8)&0x1==0x1) ? HIGH : LOW);
    if(checkButton()){
      return;
    }
  }
}
#endif

void loop() {

   if(modePause){
    digitalWrite(PIN_LED,LOW);
    DigiMouse.delay(30);
    checkButton();
    return;
  }
#ifdef MOUSE_MOVE_RANDOM
  moveMouse(random(-1,2),random(-1,2),random(100,500),random(1,5));
#else
  DigiMouse.moveX(1);
  DigiMouse.moveX(-1);
  for(int i=0;i<moveInterval>>8;i++){
    digitalWrite(PIN_LED,(i&0x1==0x1) ? HIGH : LOW);
    for(int j=0;j<8;j++){
      DigiMouse.delay(32);
      if(checkButton())
      {
        return;
      }
    }
  }
#endif
}
