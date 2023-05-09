#ifndef TOOLS_H
#define TOOLS_H
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "hypergraph.hpp"

typedef std::unordered_map<std::string, std::vector<unsigned>>
    value_to_rows_map;

struct ETable {
  // for each column (vector), map from the value value to a vector of
  // rows with this value
  std::vector<value_to_rows_map> value_to_rows;
  std::vector<std::set<int>> distributed_cols;

  unsigned long nr_cols;
  unsigned long nr_rows;
};

template<typename K, typename V>
void print_map(const std::unordered_map<K, V> &m)
{
    for (auto const &pair: m) {
        std::cout << pair.first << ":  {";
        for (auto val : pair.second) {
            std::cout << val << " ,";
        }
        std::cout << "}; ";
    }
    std::cout << "\n";
}

void print_inverse_mapping(const std::vector<std::vector<unsigned> > &inverse_mapping);

void print_plis(const std::vector<std::vector<std::vector<unsigned>>> &PLIs);

void print_inverse_mapping(const std::vector<std::vector<unsigned> > &inverse_mapping);

void print_plis(const std::vector<std::vector<std::vector<unsigned>>> &PLIs);

int *putPLI(const std::vector<std::vector<unsigned>> &pli_, const int &nr_rows, int buf_size);
std::vector<std::vector<unsigned>> getPLI(int *buf, int buf_size);

int appendPLI(ETable &PLIs, int start, std::string &content);

bool *putHypergraph(const Hypergraph &hg, int &content_size);

void takeHypergraph(Hypergraph &hg, bool *buf, int buf_size, int edge_size);
#endif // TOOLS_H
