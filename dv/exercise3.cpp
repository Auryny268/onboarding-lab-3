#include <VExercise3.h>
#include <cstdlib>
#include <random>

// Mystery1 -> Doesn't depend on clk cycles, so can use function instead
uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  // Assume I've passed in all bits correctly
  // Should return a 8-bit number
  switch (a) {
    case 0: return ((b & 0x7) << 3) | (c & 0x7);
    case 1: return (1 << 6) | ((c & 0x7) << 3) | (b & 0x7);
    case 2: return b;
    // (case 3):
    default: return c;
  }
}

// Use Struct for Mystery2 to implement methods
// -> Think Mystery2 "machine"
struct Mystery2 {
  uint16_t count = 0;
  uint16_t out;

  uint16_t reset(uint8_t a_in, uint8_t b_in) {
    out = b_in << 8 | a_in;
    count = 0;
    return out;
  }

  uint16_t step(uint8_t a_in, uint8_t b_in) {
    count %= 5;
    switch(count++) {
      case 0: out = a_in << 8 | (out & 0xFF);
      break;
      case 1: out = (out & 0xFF00) | b_in;
      break;
      case 2: out = out << 8 | out >> 8;
      break;
      case 3: out = (out << 12) | ((out & 0xF0) << 4) | ((out >> 4) & 0xF0) | (out >> 12);
      break;
      // (case 4): Reduction XOR - All bits XOR'ed with each other
      default: out = (std::popcount(out)) & 1;
    }
    return out;
  }
};

struct Exercise3_Sim {
  Mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = mystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = mystery1(a >> 2, b >> 8, c >> 8);
    return state.reset(a_in, b_in);
  }

  uint16_t step (uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = mystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = mystery1(a >> 2, b >> 8, c >> 8);
    return state.step(a_in, b_in);
  }
};

void step(VExercise3& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

int main() {
  VExercise3 model;
  Exercise3_Sim sim;
  int status = 0;

  // Randomize a, b, and c
  for (int num_test = 1; num_test < 100; ++num_test){
    model.a = rand() & 0xF;
    model.b = rand() & 0xFFFF;
    model.c = rand() & 0xFFFF;
    // Reset model first
    model.reset = 1;
    step(model);
    if (model.out != sim.reset(model.a, model.b, model.c)) status = 1;
    // Check for 100 cycles

    model.reset = 0;
    for (int cycles = 0; cycles < 100; ++cycles) {
      uint16_t result = sim.step(model.a, model.b, model.c);
      step(model);
      if (model.out != result) status = 1;
    }
  }
  if (status) std::cerr << "Failed test cases" << std::endl;
  else std::cout << "Passed all test cases" << std::endl;
  return status;
}

/*
Test Mystery 1:

case(a)
  0: d <= {b'00, b[2:0], c[2:0]}
  1: d <= {b'01, c[2:0], b[2:0]}
  2: d <= b
  3: d <= c


Test Mystery 2
clocked on negedge
if (reset == 1) out = {b_in, a_in}
else:
  0: out <= {a_in, out[7:0]};
  1: out <= {out[15:8], b_in};
  2: out <= {out[7:0], out[15:8]};
  3: out <= {out[3:0], out[7:4], out[11:8], out[15:12]};
  4: out <= {15'b0, ^out};
  count <= (count + 1) % 5;

Testing alpha, beta, then gamma


// NEW IDEA: Create structs to mimic Mystery1 and Mystery2 
-> When model.eval() evaluate "out" from gamma!

*/