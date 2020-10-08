
#include <webots/keyboard.h>
#include <webots/robot.h>

#include <arm.h>
#include <base.h>
#include <gripper.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIME_STEP 32

static void step() {
  if (wb_robot_step(TIME_STEP) == -1) {
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}
int ja = 0;
int jb = 0;
int jc = 0;
int jd = 0;
int je = 0;

static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do {
    step();
  } while (start_time + sec > wb_robot_get_time());
}

static void display_helper_message() {
  printf("Control commands:\n");
  printf(" 1:       Move joint1\n");
  printf(" 2:       Move joint2\n");
  printf(" 3:       Move joint3\n");
  printf(" 4:       Move joint4\n");
  printf(" 5:       Move joint5\n");
}
void move_arm1(){
  ++ja;
  wb_motor_set_position(wb_robot_get_device("arm1") ,M_PI/8*(ja%4));
}
void move_arm2(){
  ++jb;
  wb_motor_set_position(wb_robot_get_device("arm2"),M_PI/8*(jb%4));
}
void move_arm3(){
  ++jc;
  wb_motor_set_position(wb_robot_get_device("arm3"),M_PI/8*(jc%2));
}
void move_arm4(){
  ++jd;
  wb_motor_set_position(wb_robot_get_device("arm4"),M_PI/8*(jd%4));
}
void move_arm5(){
  ++je;
  wb_motor_set_position(wb_robot_get_device("arm5"),M_PI/4*(je%4));
}

int main(int argc, char **argv) {
  wb_robot_init();

  base_init();
  arm_init();
  gripper_init();
  passive_wait(2.0);

  // if (argc > 1 && strcmp(argv[1], "demo") == 0)
    // automatic_behavior();

  display_helper_message();

  int pc = 0;
  wb_keyboard_enable(TIME_STEP);

  while (true) {
    step();

    int c = wb_keyboard_get_key();
    if ((c >= 0) && c != pc) {
      printf("%d\n",c);
      switch (c) {
        case 49:
        // case WB_KEYBOARD_UP | WB_KEYBOARD_SHIFT:
          printf("Moving joint1\n");
          move_arm1();
          break;
        case 50:
        // case WB_KEYBOARD_DOWN | WB_KEYBOARD_SHIFT:
          printf("Moving joint2\n");
          move_arm2();
          break;
        case 51:
        // case WB_KEYBOARD_RIGHT | WB_KEYBOARD_SHIFT:
          printf("Moving joint3\n");
          move_arm3();
          break;
        case 52:
        // case WB_KEYBOARD_LEFT | WB_KEYBOARD_SHIFT:
          printf("Moving joint4\n");
          move_arm4();
          break;
        case 53:
        // case WB_KEYBOARD_LEFT | WB_KEYBOARD_SHIFT:
          printf("Moving joint5\n");
          move_arm5();
          break;
        default:
          fprintf(stderr, "Wrong keyboard input\n");
          break;
      }
    }
    pc = c;
  }

  wb_robot_cleanup();

  return 0;
}
