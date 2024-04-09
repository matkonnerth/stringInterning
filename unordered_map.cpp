//! g++ -O3 intern_hash.cpp -std=c++14 -Wall -Wextra -o intern_stl_hash

#include <stdio.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <iostream>

struct Intern_pool {
  std::unordered_map<std::string, uint> map;
  uint next;
};

Intern_pool new_intern_pool() {
  Intern_pool pool;
  pool.next = 0;
  return pool;
}

void del_intern_pool(Intern_pool) {}

uint add(Intern_pool *pool, std::string s) {
  auto &map = pool->map;
  if (map.find(s) != std::end(map))
    return map.at(s);
  map.insert(std::make_pair(s, ++pool->next));
  return pool->next;
}

// Intern pool API:
//
// Intern_pool new_intern_pool();
// void        del_intern_pool();
// uint        add(Intern_pool*, const char*);

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "r");
    if (file == 0) {
      perror("main");
      continue;
    }

    Intern_pool intern_pool = new_intern_pool();
    char buffer[256];
    while (fgets(buffer, 256, file)) // one identifier per line
    {
      buffer[strlen(buffer) - 1] = '\0'; // removes the `\n` from fgets()
      add(&intern_pool, buffer);
      std::cout << buffer << "\n";
    }

    del_intern_pool(intern_pool);
    if (fclose(file) != 0)
      perror("main");
  }
  return 0;
}
