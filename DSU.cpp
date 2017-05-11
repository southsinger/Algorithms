#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>
#include <unordered_map>
#include <algorithm>
#include <cstdint>


class DSU {
 public:
  void SetVertexCount(size_t count) {
    roots_.resize(count);
    std::iota(roots_.begin(), roots_.end(), 0);
  }
  
  void AddEdge(size_t from, size_t to) {
    static std::mt19937 generator(static_cast<unsigned>(time(0)));
    static std::uniform_int_distribution<int> distribution(0, 1);
    auto where = distribution(generator);
    if (where) {
      roots_[FindRoot(from)] = roots_[FindRoot(to)];
    } else {
      roots_[FindRoot(to)] = roots_[FindRoot(from)];
    }
  }
  
  size_t FindRoot(size_t id) {
    if (is_root(id)) {
      return id;
    }
    return roots_[id] = FindRoot(roots_[id]);
  }
  
 private:
  void SetRoot(size_t id, size_t root_id) {
    if (is_root(id)) {
      roots_[id] = root_id;
      return;
    }
    SetRoot(roots_[id], root_id);
    roots_[id] = root_id;
  }
  
  inline bool is_root(size_t id) {
    return id == roots_[id];
  }
  
  std::vector<size_t> roots_;
};
