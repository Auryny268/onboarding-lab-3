#include <VExercise4.h>
#include <cstdlib>
#include <random>


// Just use rand numbers again
bool test_sel(VExercise4& model) {
  model.eval();
  switch(model.sel) {
    case 0: return (model.out != model.alpha);
    break;
    case 1: return (model.out != model.beta);
    break;
    case 2: return (model.out != model.gamma);
    break;
    default: return (model.out != (model.alpha & (model.beta | model.gamma)));
  }
}

int main() {
  VExercise4 model;
  int status = 0;
  // Testing cs / "don't care" for sel
  model.cs = 0;
  do { if (model.out != 0) status = 1;
  } while(++model.sel);
  model.cs = 1;
  // Testing various alpha, beta, gamma for all sel
  for (int trials = 0; trials < 10000; ++trials) {
    model.alpha = rand() & 0xFF;
    model.beta = rand() & 0xFF;
    model.gamma = rand() & 0xFF;
    do {
      model.eval();
      switch(model.sel) {
        case 0: if (model.out != model.alpha) status = 1;
        break;
        case 1: if (model.out != model.beta) status = 1;
        break;
        case 2: if (model.out != model.gamma) status = 1;
        break;
        default: if (model.out != (model.alpha & (model.beta | model.gamma))) status = 1;
      }
    } while(++model.sel);
  }
  if (status) std::cerr << "Failed test cases" << std::endl;
  else std::cout << "Passed all test cases" << std::endl;
  return status;
}


