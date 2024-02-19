#include <VExercise1.h>
#include <cstdint>
#include <iostream>

bool test_op(int op) {
  VExercise1 model;
  model.op = op;
  model.a = 0;
  model.b = 0;
    do {
      do {
        model.eval();
        switch (op) {
        case 0:
          if (model.out != (uint8_t) (model.a ^ model.b)) return true;
          break;
        case 1:
          // Why are the bit-shifts so goddamn stingy????
          // Q: Why doesn't this work: 
          //    if ((model.b >= 8) && (model.out != 0)) return true;
          // A: Probably needs to skip over case instead of evaluating it
          if (model.b >= 8){
            if (model.out != 0) return true;
          } 
          else if (model.out != (uint8_t) (model.a << model.b)) return true;
          break;
        case 2:
          // Why is case 2 so weird?
          if (model.b == 0) {
            if (model.out != 0) return true;
          }
          else if (model.out != (uint8_t) (model.a % model.b)) return true;
          break;
        case 3:
          if (model.out != (uint8_t) (~(model.a & model.b))) return true;
          break;
        default: return true;
        }
      } while (++model.b);  
    } while(++model.a);
  return false;
}


int main() {
  for (int op = 0; op < 4; ++op) {
    if (test_op(op)) {
      std::cerr << "Failed test" << std::endl;
      return 1;
    }
  }
  std::cout << "Passed all tests" << std::endl;
  return 0;
}

// Use functor -> class/struct
// Use do-while to run all possible inputs for either a or b

// Need to account for edge cases -> Case 2 % by 0