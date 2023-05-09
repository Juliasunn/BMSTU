#include "essential_table.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "tools.hpp"




unsigned long parse_next_line(std::vector<std::string>& strvec,
                              const std::string& contents,
                              unsigned long start_pos) {
  strvec.clear();
 // printf("\n    Parse_next_line: %d, start_pos: %d\n", contents.size(), start_pos);
  unsigned long last_start_pos = start_pos;


  unsigned long pos = start_pos;
  bool flag = true;
  while (contents[pos] != '\n' && pos < contents.size()) {
    if (contents[pos] == ',' && flag) {

      strvec.push_back(contents.substr(last_start_pos, pos - last_start_pos));
      last_start_pos = pos + 1;
    } else if (contents[pos] == '\"' &&
               (pos == 0 || contents[pos - 1] != '\\')) {
      // non-escaped quotation mark
      flag = !flag;
    }
    ++pos;
  }
  strvec.push_back(contents.substr(last_start_pos, pos - last_start_pos));

  return pos + 1;
}

ETable load_essential_table(const std::string& input_file, ProcInfo& info) {

    ETable result;

  //  if (info.this_rank() == 0) {
  /*  Main process part start*/
  //    std::ifstream file(input_file);
    //  std::vector<std::string> file_as_string(info.num_process());
    //  int num_symb;

     // file.seekg(0, std::ios::end);
    //  num_symb = file.tellg();

    //  file.seekg(0, std::ios::beg);
    //  int symb_in_part = num_symb/info.num_process()-1;
      //printf("\nString len: %d\n", symb_in_part);

     // for (int cur_proc = 0; cur_proc < info.num_process(); cur_proc++) {
      //    file_as_string[cur_proc].resize(symb_in_part);

        //  file.read(&file_as_string[cur_proc][0], symb_in_part);
        //  std::string line_end;
        //  getline(file, line_end);
         // file_as_string[cur_proc] += line_end;
         // printf("\n Current position in file: %d\n", file.tellg());

      //    if (cur_proc != info.this_rank()) {
      //        Message new_msg = Message(TAG_DATA, file_as_string[cur_proc]);
         //     push_to_send(info, new_msg);
      //    }
      //}
     // file.close();
      DBmanager db("letters_7");


      std::vector<std::string> col_names  = db.get_col_names();
      int ncols = col_names.size();
      printf("col names %d", ncols);


      std::vector<std::string> m_col_names;

      std::vector<std::set<int>> distributed_cols = ProcInfo::distribute(info.num_process(), ncols);

      std::set<int> m_col_nums = distributed_cols.at(info.this_rank());



      for (auto col : m_col_nums) {
          m_col_names.push_back(col_names.at(col));
      }

     // return result;
      ETable res = { std::vector<value_to_rows_map>(col_names.size()), distributed_cols, col_names.size(), 0};


      load(m_col_names, db, res);
  /* Main process part end */
//    }
  //  else {
     //   Message msg = pop_from_rec(info);
   //     while (msg.tag != TAG_DATA) {
    //        msg = pop_from_rec(info);
    //    }

    //    std::string my_part = msg.content;
    //    result =  load(my_part);
   // }
    //merge(result, info);
    return res;
}

void load(const std::vector<std::string> &col_names, const DBmanager &db, ETable &res) {

   // const std::string contents(file_as_string);
   // std::vector<std::string> strvec;
   // unsigned long start_pos = 0;
   // parse_next_line(strvec, contents, start_pos);

  //  ETable res = { std::vector<value_to_rows_map>(col_names.size()), col_names.size(), 0};

    for (unsigned int col = 0; col < col_names.size(); ++col) { //запросить свои столбцы
        std::vector<std::string> vals = db.selectColumn(col_names[col]);
        int row=0;
        for (auto &val :vals) {
            printf("\nval = %s, row = %d ", val.c_str(), row);

            auto it = res.value_to_rows[col].find(val);
            if (it == res.value_to_rows[col].end()) {
                res.value_to_rows[col][val] = std::vector<unsigned>(1, row);
              } else {
                (*it).second.push_back(row);
              }
            row++;
            }
        res.nr_rows = vals.size();
        }
    for (auto &pli_ : res.value_to_rows) {
       print_map<>(pli_);
    }
    printf ("\nNumber of rows = %d", res.value_to_rows.size());





   // unsigned int row = 0;
    // reading more liens
  //  do {
     // start_pos = parse_next_line(strvec, contents, start_pos);

    //  if (strvec.size() != res.nr_cols) {
    //    std::cout << "warning: wrong number of entries in line " << row
          //        << std::endl;
      //  std::cout << "number of entries in first line: " << res.nr_cols << std::endl;
      //  std::cout << "number of entries in current line: " << strvec.size()
        //          << std::endl;
       // std::cout << "line was skipped" << std::endl;
       // continue;
//      }

     // for (unsigned int col = 0; col < res.nr_cols; ++col) {
      //  auto it = res.value_to_rows[col].find(strvec[col]);
       // if (it == res.value_to_rows[col].end()) {
       //   res.value_to_rows[col][strvec[col]] = std::vector<unsigned>(1, row);
     //   } else {
      //    (*it).second.push_back(row);
     //   }
    //  }
    //  row++;
   // } while (start_pos < contents.size());

   // res.nr_rows = row;

}


void merge(ETable &tbl, ProcInfo& info) {
 //  for (int col_id = 0; col_id < tbl.value_to_rows.size(); col_id++) {
 //       std::string content;
 //       putPLI(tbl.value_to_rows[col_id], col_id, content);
 //       Message new_msg = Message(TAG_PLI, content);
  //      push_to_send(info, new_msg);
  //  }
  //  int start  = tbl.nr_rows;
  //  for (int received_PLIs = 0; received_PLIs < tbl.nr_cols; received_PLIs++) {
   //      Message msg = pop_from_rec(info);
   //     appendPLI(tbl, start, msg.content);
   // }
  //  printf("\n !!!!     Number of rows: %d", tbl.nr_rows);
   // for (auto &pli_ : tbl.value_to_rows) {
       // print_map<>(pli_);
   // }
   // print_map(std::unordered_map<K, V> const &m)
}
