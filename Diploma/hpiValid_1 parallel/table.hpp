#pragma once

#include <vector>
#include <filesystem>
#include <string>
#include <thread>
// #include "global.hpp"

typedef unsigned long natNumber;
typedef std::vector<natNumber> record;



class Table {
 private:
  std::vector<record> m_Records; //вектор строк таблцы (читай таблица)
  std::vector<natNumber> m_nr_of_values; //кол-во значений в строке (по идее одинаковое)

 public:
  Table():m_Records({}), m_nr_of_values(0) {}
  void readTable(const std::string& path, int start, int step);

  static void splitLine(std::vector<std::string>& strvec,
                        const std::string& line);

  std::vector<record>::size_type numRecords() const { return m_Records.size(); }
  record::size_type numColumns() const { return m_Records.front().size(); };


  natNumber nrOfValues(natNumber column) const {
    return m_nr_of_values[column];
  }

  void writeToFile(const std::string& path) const;

  // operators and related

  inline record& operator[](std::vector<record>::size_type i_e) {
    return m_Records[i_e];
  }
  inline const record& operator[](std::vector<record>::size_type i_e) const {
    return m_Records[i_e];
  }

  inline std::vector<record>::iterator begin() { return m_Records.begin(); }
  inline std::vector<record>::const_iterator begin() const {
    return m_Records.begin();
  }

  inline std::vector<record>::iterator end() { return m_Records.end(); }
  inline std::vector<record>::const_iterator end() const {
    return m_Records.end();
  }

  Table subTable(const std::vector<natNumber>& row_indices,
                 const std::vector<natNumber>& col_indices);


  Table subTable(natNumber max_rows, natNumber max_cols);
};

