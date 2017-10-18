/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>

#define DXL_BUS_SERIAL1 "1"            //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 "2"            //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 "3"            //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define DXL_BUS_SERIAL4 "/dev/ttyUSB0" //Dynamixel on Serial3(USART3)  <-OpenCR

#define BAUDRATE  57600
#define DXL_1   1
#define DXL_2   2

DynamixelWorkbench dxl_wb;

int32_t goal_position[2] = {1000, 1000};
int32_t *read_position;

void setup() 
{
  Serial.begin(57600);
  while(!Serial);

  dxl_wb.begin(DXL_BUS_SERIAL3, BAUDRATE);
  dxl_wb.ping(DXL_1);
  dxl_wb.ping(DXL_2);

  dxl_wb.jointMode(DXL_1);
  dxl_wb.jointMode(DXL_2);

  dxl_wb.addSyncWrite("Goal Position");
  dxl_wb.addSyncRead("Present Position");

  dxl_wb.write(DXL_1, "Torque Enable", 0);
  dxl_wb.write(DXL_2, "Torque Enable", 0);
}

void loop() 
{
  read_position = dxl_wb.read("Present Position");
  Serial.print("DXL_1 : "); Serial.println(read_position[0]);
  Serial.print("DXL_2 : "); Serial.println(read_position[1]);
  delay(500);

  // if ((abs(goal_position[0] - read_position[0]) < 10) && 
  //     (abs(goal_position[1] - read_position[1]) < 10))
  // {
    // int tmp = goal_position[0];
    // goal_position[0] = goal_position[1];
    // goal_position[1] = tmp;

    // goal_position[0] = 3000; goal_position[1] = 3000;
    // dxl_wb.write("Goal Position", goal_position);
    // delay(2000);

    // goal_position[0] = 1000; goal_position[1] = 1000;
    // dxl_wb.write("Goal Position", goal_position);
    // delay(2000);
  // }

}