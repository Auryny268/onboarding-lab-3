#include <VExercise2.h>
#include <cstdlib>

bool check_init(uint16_t init) {
  // NOTE: Must initialize clock with 1 bc negedge
  VExercise2 model;
  // Testing reset
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.reset = 1;
  model.init = init;
  model.eval();
  if (model.out != (uint16_t)(~model.init)) return true;
  model.reset = 0;

  // Check Cycles
  for (int i = 0; i < 10000; ++i) {
      model.clk = 1;
      model.eval();
      uint16_t tap10 = (model.out >> 10) & 1;
      uint16_t tap8 = (model.out >> 8) & 1;
      uint16_t tap3 = (model.out >> 3) & 1;
      uint16_t tap1 = (model.out >> 1) & 1;
      uint16_t actual_out = (model.out << 1) | (tap10 ^ tap8 ^ tap3 ^ tap1);
      model.clk = 0;
      model.eval();
      if (model.out != actual_out) return true;
  }
  return false;
}

int main() {
  int status = 0;
  if (check_init(0x11)) status = 1;
  if (check_init(0x55)) status = 1;
  if (check_init(0x99)) status = 1;
  if (check_init(0xdd)) status = 1;
  if (check_init(0xff)) status = 1;
  if (status) std::cerr << "Failed test cases" << std::endl;
  else std::cout << "Passed all test cases" << std::endl;
  return status;
}


// NOTE: clk must alternate between 1 and 0!!!


/*
 Idea: Try a few initial values (Vito does 4)
 Run those for a few steps.

 Must recreate circuit in code


 Also test reset!!!!!
*/

