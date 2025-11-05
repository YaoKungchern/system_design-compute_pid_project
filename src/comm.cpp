#include "comm.h"
void command_cb() 
{
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\n' || c == '\r') {
            // 处理完整命令
            processCommand(rx_buffer);
            rx_buffer = ""; // 清空命令缓存
        } else {
            rx_buffer += c; // 累积命令字符
        }
    }
}

void processCommand(String cmd) {
    cmd.trim(); // 去除前后空格
    
    if (cmd.startsWith("kp=")) {
        float value = cmd.substring(3).toFloat();
        servo_pid.kp = value;
        Serial.print("Kp set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("ki=")) {
        float value = cmd.substring(3).toFloat();
        servo_pid.ki = value;
        Serial.print("Ki set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("kd=")) {
        float value = cmd.substring(3).toFloat();
        servo_pid.kd = value;
        Serial.print("Kd set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("il=")) {
        float value = cmd.substring(3).toFloat();
        servo_pid.i_lm = value;
        Serial.print("I's limit set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("ol=")) {
        float value = cmd.substring(3).toFloat();
        servo_pid.output_lm = value;
        Serial.print("output limit set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("tg=")) { 
        float value = cmd.substring(3).toFloat();
        servo_pid.target = value;
        Serial.print("Target set to: ");
        Serial.println(value);
    }
    else if (cmd.startsWith("reset")) {
        servo_pid.kp = 0.0;
        servo_pid.ki = 0.0;
        servo_pid.kd = 0.0;
        Serial.println("PID parameters reset to 0");
    }
    else if (cmd.startsWith("show")) {
        Serial.print("Kp: ");
        Serial.print(servo_pid.kp);
        Serial.print(", Ki: ");
        Serial.print(servo_pid.ki);
        Serial.print(", Kd: ");
        Serial.println(servo_pid.kd);
    }
    else {
        Serial.println("Unknown command. Available commands:");
        Serial.println("kp=value, ki=value, kd=value, reset, show");
    }
}

void serial_cb() 
{
    // Serial.print("Distance:");
    Serial.print(distance);
    // Serial.print("\n");
    Serial.print(",");
    Serial.print(servo_pid.target);
    Serial.print("\n");
    // Serial.print(" cm, PID Output: ");
    // Serial.print(servo_pid.get_output());
    // Serial.print(", Kp: ");
    // Serial.print(servo_pid.kp);
    // Serial.print(", Ki: ");
    // Serial.print(servo_pid.ki);
    // Serial.print(", Kd: ");
    // Serial.println(servo_pid.kd);
}

/*__||_____||__
  __||_____||__
  ___\\___//___
  _===========_
  _____|||_____
  _____|||_____
  ______|______
  ___防伪专用___*/