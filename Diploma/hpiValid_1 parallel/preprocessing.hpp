#pragma once
#include <essential_table.hpp>
#include <stdlib.h>
#include <vector>
#include <filesystem>


struct PLITable {
  // the PLIs: for each column, we have a vector of clusters where
  // each cluster is a vector of row IDs
  std::vector<std::vector<std::vector<unsigned>>> PLIs;

  // the inverse mapping: for each column, we have a vector of mapping
  // a row ID to a cluster ID
  std::vector<std::vector<unsigned>> inverse_mapping;

  // the number of rows
  unsigned nr_rows;

  // the number of columns
  unsigned nr_cols;
};

constexpr unsigned size_one_cluster = std::numeric_limits<unsigned>::max();

PLITable preprocess(const std::string& input_file,  ProcInfo& info);

void print_plis(const std::vector<std::vector<std::vector<unsigned>>> &PLIs);

