//! g++ -O3 intern_hash.cpp -std=c++14 -Wall -Wextra -o intern_stl_hash

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == 0) {
      perror("main");
      continue;
    }

   
    char buffer[256];
    while (fgets(buffer, 256, file)) // one identifier per line
    {
      buffer[strlen(buffer) - 1] = '\0'; // removes the `\n` from fgets()
      std::string{buffer};
      std::cout << buffer << "\n";
    }

    if (fclose(file) != 0)
      perror("main");
  }
  return 0;
}
