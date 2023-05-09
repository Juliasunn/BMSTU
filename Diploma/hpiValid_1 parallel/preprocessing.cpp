#include "preprocessing.hpp"
#include "tools.hpp"
#include <iterator>





PLITable preprocess(const std::string& input_file, ProcInfo& info) {
  PLITable res;

  ETable tbl = load_essential_table(input_file, info);

 // return res;
  std::vector<std::set<int>> distributed_cols = tbl.distributed_cols;
  std::set<int> m_cols = distributed_cols[info.this_rank()]; /*Номера столбцов обработанные этим процессом */


  res.nr_rows = tbl.nr_rows;
  res.nr_cols = tbl.nr_cols;

  res.inverse_mapping.clear();
  res.inverse_mapping.resize(
      res.nr_cols, std::vector<unsigned>(res.nr_rows, size_one_cluster));

  res.PLIs.clear();
  res.PLIs.resize(res.nr_cols);
  unsigned max_cluster_size = tbl.value_to_rows[0].size();

  /* Заполняем столбцы которые есть сейчас у этого процесса (обработанные им)*/
  int c_in_table = 0;
  for (auto i_c  : m_cols) {
  //for (unsigned i_c = 0; i_c < res.nr_cols; ++i_c) {
    unsigned counter = 0;

    for (auto& cluster : tbl.value_to_rows[c_in_table]) {
      if (cluster.second.size() > 0) {
        for (const unsigned& i_r : cluster.second) {
          res.inverse_mapping[i_c][i_r] = counter;
        }
        counter++;
        res.PLIs[i_c].emplace_back(std::move(cluster.second));
        if (cluster.second.size() > max_cluster_size) max_cluster_size = cluster.second.size();

      }

    }
    c_in_table++;

    res.PLIs[i_c].shrink_to_fit();

    /* Отправка нового  PLI*/
    PLIMessage *msg = new PLIMessage();
    msg->putPLI(res.PLIs[i_c], max_cluster_size);
    push_to_send(info, msg);

    /* */
  }

  /* Получить PLI для всех столбцов */
 // std::vector<std::vector<std::vector<unsigned>>> full_PLIs;

 // std::vector<std::set<int>> distributed_cols = tbl.distributed_cols;
  //std::vector<PLIMessage *> rec_plis;
  //res.PLIs.clear();

  for (int n = 0; n <  res.nr_cols - m_cols.size(); n++) {
      /* Свой процесс пропускаем - он итак у нас*/
     PLIMessage *rec_pli = dynamic_cast<PLIMessage *>(pop_from_rec(info, TAG_PLI));
     printf("\n\nSender = %d, Sender's columns: ", rec_pli->sender_rank);
     int col_it = *distributed_cols[rec_pli->sender_rank].begin();
     printf("\n Col it = %d, ", col_it);
     distributed_cols[rec_pli->sender_rank].erase(col_it);
     res.PLIs[col_it] = rec_pli->getPLI();

     /* Дополняем обратные PLI*/

     unsigned counter = 0;
     for (auto& cluster : res.PLIs[col_it]) {
       if (cluster.size() > 0) {
         for (const unsigned& i_r : cluster) {
           res.inverse_mapping[col_it][i_r] = counter;
         }
         counter++;

       }

     }

     //     }

       //   for (auto col : distributed_cols[rec_pli->sender_rank]) {
             // printf(" %d, ", col);
       //   }
          //res.PLIs.push_back(rec_pli->getPLI());
         // res.nr_cols++;
         // rec_plis.push_back(rec_pli);


     // }

  }
  printf("\nNr cols = %d", res.nr_cols);
 // print_plis(res.PLIs);


  print_inverse_mapping(res.inverse_mapping);

  return res;
}





