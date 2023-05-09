#include "table.hpp"
#include <time.h>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <unistd.h>


void Table::readTable(const std::string& path, int start, int step) {
  // // start timer 'Table Reading and Preconversion'


  sleep(5);
 // std::cout << "sleep time: "<< (5);
  return;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Could not open file '" + path + "'";
  }

  std::string line;

  for (int curLine = 0; curLine < start; curLine++) {
      getline(file, line);
  }



  if (!getline(file, line)) {
    throw std::runtime_error("Table has no records.");
  }

  // count columns
  std::vector<std::string> strvec;
  splitLine(strvec, line);
  natNumber nr_columns = strvec.size();

  // setup
  m_nr_of_values = std::vector<natNumber>(nr_columns, 0);
  std::vector<std::unordered_map<std::string, natNumber>> str_to_int_value(
      nr_columns);
  // only for debugging
  // std::vector<std::vector<std::string>> int_to_str_value(nr_columns);

  // read table
  int pos = step-1;

  do {
    if (pos > 0) {
        pos--;
        continue;
    }
    pos = step-1;

    splitLine(strvec, line);

    if (strvec.size() != nr_columns) {
      std::cout << "warning: wrong number of entries in line "
                << m_Records.size() << std::endl;
      std::cout << "number of entries in first line: " << nr_columns
                << std::endl;
      std::cout << "number of entries in current line: " << strvec.size()
                << std::endl;
      std::cout << "line was skipped" << std::endl;
      std::cout << line << std::endl;
      continue;
    }

    m_Records.push_back(std::vector<natNumber>(nr_columns));

    for (natNumber col = 0; col < nr_columns; ++col) {
      auto it = str_to_int_value[col].find(strvec[col]);
      if (it != str_to_int_value[col].end()) {
        m_Records.back()[col] = it->second;
      } else {
        str_to_int_value[col][strvec[col]] = m_nr_of_values[col];
        // int_to_str_value[col].push_back(strvec[col]);
        m_Records.back()[col] = m_nr_of_values[col];
        m_nr_of_values[col]++;
      }
    }
  } while (getline(file, line));

  file.close();


  // // stop and print timer 'Table Reading and Preconversion'
  // stopAndPrintTimer(timer_readingAndPreconversion,
  //                   "Table Reading and Preconversion");
}

void Table::splitLine(std::vector<std::string>& strvec, const std::string& line) {
  strvec.clear();

  strvec.push_back("");
  bool flag = true;
  for (const char& c : line) {
    if (c == ',' && flag) {
      strvec.push_back("");
    } else {
      if (c == '\"' &&
          (strvec.back().empty() || strvec.back().back() != '\\')) {
        // non-escaped quotation mark
        flag = !flag;
      }
      strvec.back() += c;
    }
  }
}

void Table::writeToFile(const std::string &path) const {
    std::ofstream file (path);
    if (!file.is_open()) throw std::runtime_error("Could not open file '" + path + "'");

    for (const record& r : m_Records) {
        file << r[0];
        for (record::size_type i = 1; i < r.size(); ++i) {
            file << ',' << r[i];
        }
        file << std::endl;
    }

    file.close();
}

Table Table::subTable(const std::vector<natNumber>& row_indices,
                      const std::vector<natNumber>& col_indices) {
  Table sub;
  sub.m_Records =
      std::vector<record>(row_indices.size(), record(col_indices.size()));
  natNumber sub_row = 0;
  for (natNumber row : row_indices) {
    natNumber sub_col = 0;
    for (natNumber col : col_indices) {
      sub.m_Records[sub_row][sub_col] = m_Records[row][col];
      ++sub_col;
    }
    ++sub_row;
  }

  sub.m_nr_of_values = m_nr_of_values;

  return sub;
}

Table Table::subTable(natNumber max_rows, natNumber max_cols) {
  if (max_rows == 0) {
    max_rows = numRecords();
  }
  if (max_cols == 0) {
    max_cols = numColumns();
  }

  max_rows = std::min(max_rows, numRecords());
  max_cols = std::min(max_cols, numColumns());

  std::vector<natNumber> row_indices(max_rows);
  std::vector<natNumber> col_indices(max_cols);

  std::iota(row_indices.begin(), row_indices.end(), 0);
  std::iota(col_indices.begin(), col_indices.end(), 0);

  return subTable(row_indices, col_indices);
}

