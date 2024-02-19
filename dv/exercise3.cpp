#include <VExercise3.h>
#include <cstdlib>
#include <random>

int main() {
  VExercise3 model;
}

// Mystery1 -> Doesn't depend on clk cycles, so can use function instead
uint16_t mystery1(uint16_t a, uint16_t b, uint16_t c) {
  // Assume I've passed in all bits correctly
  // Should return a 8-bit number
  switch (a) {
    case 0:
    return (model.b & 0x7) << 3 | (model.c & 0x7);
    case 1:
    return 1 << 6 | (model.c & 0x7) << 3 | (model.b & 0x7);
    case 2:
    return model.b & 0xFF;
    case 3:
    return model.c & 0xFF;
  }
}

// Use Struct for Mystery2 to implement methods
struct mystery2 {
  uint16_t count;
  uint16_t out;

  uint16_t reset(uint8_t a_in, uint8_t b_in) {
    out = b_in << 8 | a_in;
    count = 0;
    return out;
  }

  // 0: out <= {a_in, out[7:0]};
  // 1: out <= {out[15:8], b_in};
  // 2: out <= {out[7:0], out[15:8]};
  // 3: out <= {out[3:0], out[7:4], out[11:8], out[15:12]};
  // 4: out <= {15'b0, ^out};
  // count <= (count + 1) % 5;

  uint16_t step(uint8_t a_in, uint8_t b_in) {
    count %= 5;
    switch(count++) {
      case 0:
      out = a_in << 8 | (out & 0xFF);
      break;
      case 1:
      out = (out & 0xFF00) | b_in;
      break;
      case 2:
      out = out << 8 | out >> 8;
      break;
      case 3:
      out = (out & 0xF) << 12 | (out & 0xF0) << 8 | (out & 0xF00) << 4 | (out & 0xF000);
      break;
      case 4:
      out = (^out) & 1;
      break;
    }
    return out;
  }
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