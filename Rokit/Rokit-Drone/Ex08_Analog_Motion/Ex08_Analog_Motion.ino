/*****************************************************************
  ■ Drone을 전방 센서 3개와 밑면 센서로 전체 조종하기
  - 전, 후, 좌, 우로 흐르는지 확인 후 구동
*******************************************************************/
#include <SmartDroneControl.h>  // 스마트 드론을 사용하기 위한 헤더파일 

void setup()
{
  Serial.begin(9600);                 // 시리얼 통신(무선통신) 개시
  SmartDroneControl.begin();        // 드론 플러그의 기능 개시
  delay(1000);
}

void loop()
{
  //아래의 내용은 실시간으로 계속 제어보드의 센서값을 체크한다.
  byte dipBt1 = digitalRead(8);    // 딥스위치 1번 상태 체크
  byte dipBt2 = digitalRead(9);    // 딥스위치 2번 상태 체크
  byte dipBt3 = digitalRead(10);    // 딥스위치 3번 상태 체크

  byte bt1 = digitalRead(11);       // ■ □ □ □ □ □ □   밑면 적외선 센서
  byte bt2 = digitalRead(12);       // □ ■ □ □ □ □ □   밑면 적외선 센서
  byte bt3 = digitalRead(13);       // □ □ ■ □ □ □ □   밑면 적외선 센서
  byte bt4 = digitalRead(14);       // □ □ □ ■ □ □ □   밑면 적외선 센서
  byte bt6 = digitalRead(16);       // □ □ □ □ ■ □ □   밑면 적외선 센서
  byte bt7 = digitalRead(17);       // □ □ □ □ □ ■ □   밑면 적외선 센서
  byte bt8 = digitalRead(18);       // □ □ □ □ □ □ ■   밑면 적외선 센서


  int analogValue0 = analogRead(A0);  // 자기가 원하는 것과 연결가능
  int analogValue1 = analogRead(A1);  // 자기가 원하는 것과 연결가능
  int analogValue2 = analogRead(A2);  // 자기가 원하는 것과 연결가능
  int analogValue3 = analogRead(A3);  //pitch       상  하
  int analogValue4 = analogRead(A4);  //yaw         좌  우
  int analogValue5 = analogRead(A5);  //throttle    위 아래
  int analogValue6 = analogRead(A6);  //roll        회전

  ///////////////////////////◆프로그램부분◆///////////////////////////////


  if (bt4) //  □  □ □ ■ □ □  □ 밑면 4 번째 센서 감지시 (핀번호 14 or 15 : 붙어있음)
  {
    SmartDroneControl.ResetYaw();
    delay(500);
  }

  // A0의 센서의 감지거리가 드론의 높이가 되도록 한다.

  if ( bt8 ) // 밑면 마지막 센서 감지하면서 비행
  {
    THROTTLE = map(analogValue1, 0, 900, -100, 100) + 20;                             //상하 높이 조정
    ROLL = map(analogValue0, 0, 1023, 100, 0) + map(analogValue2, 0, 1023, -100, 0);  //좌우 조정
    SmartDroneControl.Send();
  }

  else if ( bt7 ) // 센서 감지하면서 비행
  {
    THROTTLE = map(analogValue1, 0, 900, -100, 100) + 20;                                 //상하 높이 조절
    PITCH = map(analogValue0, 0, 1023, -100, 0) + map(analogValue2, 0, 1023, 100, 0);    //전후 조정

    SmartDroneControl.Send();
  }

  else if ( bt6 )
  {
    SmartDroneControl.Stop();
  }

  
  ////////////////////////////////////////////////////////////////////////////

}

