#include "tree_search.hpp"
#include <algorithm>
#include "hypergraph.hpp"
#include "preprocessing.hpp"
#include <stdlib.h>
#include <set>
#include <algorythm.h>
#define SAMPLE_EXP 0.3

//В intersect_queue номера столбцов, которые находятся в S (то есть которые надо пересечь чтобы найти PLI)
//В crit - вершины частичного гиперграфа


std::vector<std::set<int> > TreeSearch::distribute_branches(bool &d_flag, int n_proc,
                                                            int n_br)
{
  //  int branches_to_take = count(C);
  //  int nr_process_to_share = info.num_process();
    int n_owners, n_assigned;

    d_flag  = (n_br >= n_proc); //назначаем ветви процессу или процессы ветвям

    if (d_flag) { //процесс -> ветви
        n_owners = n_proc;
        n_assigned =  n_br;
    }
    else {
        n_owners =  n_br;
        n_assigned = n_proc;
    }



    std::vector<std::set<int>> distributed_branches(n_owners); //набор ветвей распределенных для данного процесса
    distributed_branches = ProcInfo::distribute(n_owners, n_assigned);


  //  int n_to_assign = n_owners / n_assigned;
    //последние ветви мб не распределены если не делится нацело
   // for (int o_idx = 0; o_idx < n_owners; o_idx ++) {

    //    for (int a_idx = o_idx*n_to_assign; a_idx < (o_idx+1)*n_to_assign; a_idx ++) {
    //        distributed_branches[o_idx].insert(a_idx);
    //    }
   //  }

  //  for  (int a_idx = (n_to_assign*n_owners), o_idx = 0;
   //                       a_idx < n_assigned; a_idx++, o_idx++) {
    //    distributed_branches[o_idx].insert(a_idx);
   //  }
    return distributed_branches;
}

        //назначить 1 ветвь нескольким процессам до возможности разделения



TreeSearch::TreeSearch(const PLITable& tab, ProcInfo &info_)
    : m_tab(tab),
      info(info_),
      m_partial_HG(tab.nr_cols),
      m_clusterid_to_recordindeces(tab.nr_rows)
    //  m_gen(cfg.seed)
{
  // add single edge containing all vertices to partial hypergraph
    // initial seed for the random number generator
 // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  m_gen = std::default_random_engine{};
  m_partial_HG.addEdge(~(edge(m_partial_HG.numVertices())));
  //printf("\n Edge: %d", count(m_partial_HG[0]));

}

void TreeSearch::run() {
 // m_RC.start_timer(timer::sample_diff_sets);
    int to_sample =  m_tab.PLIs.size() / info.num_process() + ((m_tab.PLIs.size() % info.num_process()) > 0);
    int start = info.this_rank()*to_sample, stop = std::min((info.this_rank()+1)*to_sample, (int)m_tab.PLIs.size());

 // if (info.this_rank() == 0 ) {
      // for (const auto& PLI : m_tab.PLIs) {
       for (int i = start; i < stop; i++) {
        //Hypergraph gen = sample(PLI);
         Hypergraph gen = sample(m_tab.PLIs[i]);

        for (const edge& e : gen) {
            m_partial_HG.addEdgeAndMinimizeInclusion(e);
            print(e);
        }
      }


     //  int content_size;

       /* Отправка гиперграфа */

       EDGEMessage *msg = new EDGEMessage();
       msg->putEdges(m_partial_HG);


       push_to_send(info, msg);
      // return;


       /* */
 // }
//  else {
      Message *rec_msg = pop_from_rec(info, TAG_HYPERGRAPH);
     // return;
      EDGEMessage *e_msg = dynamic_cast<EDGEMessage *>(rec_msg);
      e_msg->takeEdges(m_partial_HG, m_tab.nr_cols);

//  }
   printf("\nHypergraph: ");
  for (const edge& e : m_partial_HG) {
      print(e);
  }
  printf("\n");
//  return;

  // S, CAND
  edge S(m_partial_HG.numVertices());
  edge CAND(m_partial_HG.numVertices());
  set(CAND);

  // crit, uncov
  std::vector<edgemark> crit;
  edgemark uncov(m_partial_HG.numEdges());
  set(uncov);
  //printf("\n UNCOV SIZE %d UNCOV COUNT %d ", uncov.size(), count(uncov));

  // vertexhittings
  std::vector<edgemark> vertexhittings(m_partial_HG.numVertices(),
                                       edgemark(m_partial_HG.numEdges()));
  for (std::vector<edge>::size_type i_e = 0; i_e < m_partial_HG.numEdges();
       ++i_e) {
    for (int i_v = find_first(m_partial_HG[i_e]);
         i_v != NPOS; i_v = find_next(m_partial_HG[i_e], i_v)) {
          set(vertexhittings[i_v], i_e);
    }

  }


  // removed_criticals_stack
  std::vector<std::vector<edgemark>> removed_criticals_stack;

  // intersections
  std::stack<std::vector<std::vector<unsigned>>> intersection_stack;
  std::deque<edge::size_type> tointersect_queue;

  // Searching
  // find edge from uncov with smallest intersecton C with CAND


  edge C = m_partial_HG[find_first(uncov)] & CAND;
  for (int i_e = find_next(uncov, find_first(uncov)); i_e != NPOS; i_e = find_next(uncov, i_e)) {
    if (count(m_partial_HG[i_e] & CAND) < count(C))
      C = m_partial_HG[i_e] & CAND;

  }
  //C - это пересечение одного из РЕБЕР частичного гиперграфа с CAND,
  //Из C мы выбираем начальные атрибуты ветвления (обычно один)

 // CAND = CAND - C;

  edge my_C(C.size());

  bool d_flag;
  std::vector<std::set<int>> distributed_branches = distribute_branches(d_flag, info.num_process(), count(C));
  std::set<int> procs;
  int m_idx;

  if (!d_flag) { //branches -> process
      for (int idx = 0; idx < distributed_branches.size(); idx++) {
          if (distributed_branches[idx].count(info.this_rank()) > 0) { //находим свою ветку
              m_idx = idx;
              procs = distributed_branches[idx]; //процессы которые обрабатывают ту же ветку
              break;

          }
      }
      int position = pos(C, m_idx+1);
      set(my_C, m_idx);

  }
  else {
      for (auto m_idx : distributed_branches[info.this_rank()]) {
          int position = pos(C, m_idx+1); //отдаем номер установленного бита получаем пзицию
           set(my_C, position);
      }
  }
  CAND = CAND - my_C;
  printf("\n My C = ");
  print(C);
  print(my_C);


  try {
    //  int branch_idx=0;
    for (int v = find_first(my_C); v != NPOS; v = find_next(my_C, v)) {
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        if (rank == 0) {
            printf("V = %d All = %d", v, count(C));
        }

      // update crit and uncov
      update_crit_and_uncov(removed_criticals_stack, crit, uncov,
                            vertexhittings[v]);

      // branch
      set(S, v);



      if (rank == 0) {
          std::string output = "Candidate (S): ";
         // printf("S = ");
          for (auto col_id = 0; col_id < S.size(); col_id++) {
              output+=  " " + std::to_string(S[col_id]);
          }

          printf("!!!!!!!!!!!!!!!!%s\n", output.c_str());
      }
      intersection_stack.push(m_tab.PLIs[v]); //

      extend_or_confirm_S(S, CAND, crit, uncov, vertexhittings,
                          removed_criticals_stack, intersection_stack,
                          tointersect_queue,
                          procs);
      intersection_stack.pop();
      reset(S, v);

      // reset update of crit and uncov
      restore_crit_and_uncov(removed_criticals_stack, crit, uncov);

      // update CAND
      set(CAND, v);
      //return;
    }
    // report final hypergraph
  } catch (unsigned timeout) {
      //printf(" I HAVE FINISHED ");
     // return;
    // report current partial hypergraph
  }
}



//Выборка
Hypergraph TreeSearch::sample(const std::vector<std::vector<unsigned>>& PLI) {
  Hypergraph difference_graph(m_tab.nr_cols);
  edge temp_edge(m_tab.nr_cols);

 // for (int i = 0; i< PLI.size(); i++) {
//      std::cout << " value_id: " << i << " row id_s: {";
//      for (int j = 0; j< PLI[i].size(); j++) {
 //         std::cout << PLI[i][j] << ", ";
 //     }
  //    std::cout << " } ";
 // }
//  std::cout << "\n";

  if (PLI.size() == 0) {
    return difference_graph;
  }

  std::vector<unsigned long> weights;
  unsigned long total_pairs = 0;

  ///Тут надо разделить PLI между процессами


  for (const auto& cluster : PLI) {
    unsigned long pairs = (cluster.size() * (cluster.size() - 1)) / 2;
    total_pairs += pairs;
    weights.push_back(pairs);
  }

  // calculate how many to view
  std::size_t to_view = static_cast<std::size_t>(
      std::round( std::pow(static_cast<double>(total_pairs), SAMPLE_EXP)));
  if (to_view < 1) to_view = 1;

 // m_RC.count_diff_sets(to_view);

  std::discrete_distribution<int> rand_cluster(weights.begin(), weights.end());
  std::uniform_int_distribution<> rand_int(0, std::numeric_limits<int>::max());


  std::vector<std::tuple<int, int, int>> samples(to_view);


  for (unsigned int i = 0; i < to_view; ++i) {
    std::get<0>(samples[i]) = rand_cluster(m_gen);
    unsigned int size = PLI[std::get<0>(samples[i])].size();



    if (size <= 1 ) {
        //printf("\n !!! OH FUCK I AM DIVIDING BY ZERO !!!! \n");
         continue;
    }

    int i_i_r1 = rand_int(m_gen) % size;

    int i_i_r2 = (i_i_r1 + 1 + rand_int(m_gen) % (size - 1)) % size;
    std::get<1>(samples[i]) = i_i_r1;
    std::get<2>(samples[i]) = i_i_r2;
  }
  std::sort(samples.begin(), samples.end());
  for (unsigned int i = 0; i < to_view; ++i) {
    const auto& cluster = PLI[std::get<0>(samples[i])];
    int i_i_r1 = std::get<1>(samples[i]);
    int i_i_r2 = std::get<2>(samples[i]);

    reset(temp_edge);

    // calculate difference edge
    for (unsigned i_c = 0; i_c < m_tab.nr_cols; ++i_c) {
      // set bit if records have different cluster id's or if they
      // have maxint as id (indicating that they are unique)
      if (m_tab.inverse_mapping[i_c][cluster[i_i_r1]] !=
              m_tab.inverse_mapping[i_c][cluster[i_i_r2]] ||
          m_tab.inverse_mapping[i_c][cluster[i_i_r1]] == size_one_cluster) {
             set(temp_edge, i_c);
      }
    }
    // add difference edge to difference graph
    difference_graph.addEdgeAndMinimizeInclusion(temp_edge);
  }

  // std::cout << "sampled pairs: " << to_view << std::endl;
  // std::cout << "number of new edges: " << difference_graph.numEdges() <<
  // std::endl;
  return difference_graph;
}

inline void TreeSearch::update_crit_and_uncov(
    std::vector<std::vector<edgemark>>& removed_criticals_stack,
    std::vector<edgemark>& crit, edgemark& uncov, const edgemark& v_hittings) {
  // update crit[] for vertices in S and put changes on stack

  removed_criticals_stack.emplace_back(crit.size());

  for (std::vector<edgemark>::size_type i = 0; i < crit.size(); ++i) {
    removed_criticals_stack.back()[i] = crit[i] & v_hittings;
    crit[i] = crit[i] - v_hittings;
  }

  // set critical edges for v and remove them from uncov

  crit.emplace_back(v_hittings & uncov);
  uncov = uncov -v_hittings;
}

inline void TreeSearch::restore_crit_and_uncov(
    std::vector<std::vector<edgemark>>& removed_criticals_stack,
    std::vector<edgemark>& crit, edgemark& uncov) {
  uncov = uncov || crit.back();
  crit.pop_back();

  for (std::vector<edgemark>::size_type i = 0; i < crit.size(); ++i) {
    crit[i] = crit[i] || removed_criticals_stack.back()[i];
  }

  removed_criticals_stack.pop_back();
}

inline bool TreeSearch::extend_or_confirm_S(
    edge& S, edge& CAND, std::vector<edgemark>& crit, edgemark& uncov,
    std::vector<edgemark>& vertexhittings,
    std::vector<std::vector<edgemark>>& removed_criticals_stack,
    std::stack<std::vector<std::vector<unsigned>>>& intersection_stack,
    std::deque<edge::size_type>& tointersect_queue,
         std::set<int> procs) //количество процессов между которыми надо поделить ответвленя от этой ветви

{


    if (info.this_rank() == 0) {
      //  printf("\n - Intersection stack size: %d", intersection_stack.size());
      //  printf("\nS=");
       // print(S);

      //  printf("!!!!!!!!!!!!!!!!%s\n", output.c_str());
    }


  if (none(uncov)) { // UCC для частичного гиперграфа

    pullUpIntersections(intersection_stack, tointersect_queue); //Найти PLI комбинации S как пересечение PLI

    if (intersection_stack.top().empty()) {     //если PLI пересечения пуст (это UCC всей таблицы)
  //    if(!m_RC.ucc_found(S)) {
        // timeout
        UCCs.push_back(S);
       // throw timeout;
    //  }
      return false;
    }
     // PLI непустой, значит нужны еще ребра из PLI чтобы дополнить им частичный гиперграф

    // gain new edges and minimize
    updateEdges(crit, uncov, vertexhittings, removed_criticals_stack,
                intersection_stack.top());

    // check if minimality still holds
    if (!S_fulfills_minimality_condition(crit)) return true;
  }

  // find edge from uncov with smallest intersecton C with CAND
 // m_RC.count_tree_complexity(count(uncov));
  edge C = m_partial_HG[find_first(uncov)] & CAND;
  for (int i_e = find_next(uncov, find_first(uncov));
       i_e != NPOS; i_e = find_next(uncov, i_e)) {
    edge C_new = (m_partial_HG[i_e] & CAND);
    if (count(C_new) < count(C)
   //         || (count(C_new) == count(C) && niceness(C_new) < niceness(C))
            ) {
      C = C_new;
    }
  }
 // CAND = CAND - C;
  // всего C делить на количество процессов - сколько веток забирает 1 процесс
  edge my_C(C.size());
  if (procs.size() > 0)  {
      edge my_C(C.size());

      bool d_flag;
      std::vector<std::set<int>> distributed_branches = distribute_branches(d_flag, info.num_process(), count(C));
      std::set<int> procs;
      int m_idx;

      if (!d_flag) { //branches -> process
          for (int idx = 0; idx < distributed_branches.size(); idx++) {
              if (distributed_branches[idx].count(info.this_rank()) > 0) { //находим свою ветку
                  m_idx = idx;
                  procs = distributed_branches[idx]; //процессы которые обрабатывают ту же ветку
                  break;

              }
          }
          int position = pos(C, m_idx+1);
          set(my_C, m_idx);

      }
      else {
          int m_proc_idx = std::distance(procs.begin(), procs.find(info.this_rank()));
          for (auto m_idx : distributed_branches[m_proc_idx]) {
              int position = pos(C, m_idx+1); //отдаем номер установленного бита получаем пзицию
               set(my_C, position);
          }
      }
      CAND = CAND - my_C;
      printf("\n My C = ");
      print(C);
      print(my_C);
   }
  else {
      my_C = C;
  }

  for (int v = find_first(my_C), n = 0; v != NPOS; v = find_next(my_C, v), n++) {
    // don't branch if v is violater for S
    if (isViolater(crit, vertexhittings[v])) continue;

    // branch
    update_crit_and_uncov(removed_criticals_stack, crit, uncov,
                          vertexhittings[v]);
//////////////////!!!!!!!!!!
    set(S, v);

    tointersect_queue.push_back(v);
    bool check = extend_or_confirm_S(S, CAND, crit, uncov, vertexhittings,
                                     removed_criticals_stack,
                                     intersection_stack, tointersect_queue,
                                     procs);
    if (tointersect_queue.empty())
      intersection_stack.pop();
    else
      tointersect_queue.pop_back();
    reset(S, v);
    restore_crit_and_uncov(removed_criticals_stack, crit, uncov);

    // prove if deeper update of edges destroyed minimality condition
    if (check && !S_fulfills_minimality_condition(crit)) {
      // add C now to CAND; this also adds the violaters to CAND again and it is
      // equal to the CAND passed in
      CAND = CAND || C;

      return true;
    }

    // update CAND
    set(CAND, v);
  }

  // add C now to CAND; this also adds the violaters to CAND again and it is
  // equal to the CAND passed in
  CAND = CAND || C;

  return false;
}

inline void TreeSearch::pullUpIntersections(
    std::stack<std::vector<std::vector<unsigned>>>& intersection_stack,
    std::deque<edge::size_type>& tointersect_queue) {
 // m_RC.start_timer(timer::cluster_intersect);



  while (!tointersect_queue.empty()) {
     printf("%d ", tointersect_queue.front());
    intersection_stack.push(intersectClusterListAndClusterMapping(
        intersection_stack.top(), m_tab.inverse_mapping[tointersect_queue.front()]));

    tointersect_queue.pop_front();
  }
  //m_RC.stop_timer(timer::cluster_intersect);
}

std::vector<std::vector<unsigned>>
TreeSearch::intersectClusterListAndClusterMapping(
    const std::vector<std::vector<unsigned>>& PLI,
    const std::vector<unsigned>& inverse_mapping) {
 // m_RC.count_intersections();
  std::vector<std::vector<unsigned>> intersection;

  std::vector<unsigned long> clusterids;
  for (const auto& cluster : PLI) {
  //  m_RC.count_intersection_cluster_size(cluster.size());
    clusterids.clear();
    for (std::vector<unsigned>::size_type i_r : cluster) {
      if (inverse_mapping[i_r] != size_one_cluster) {
        auto& map_entry = m_clusterid_to_recordindeces[inverse_mapping[i_r]];
        if (map_entry.size() == 0) {
          clusterids.push_back(inverse_mapping[i_r]);
        }
        map_entry.push_back(i_r);
      }
    }
    for (auto clusterid : clusterids) {
      auto& map_entry = m_clusterid_to_recordindeces[clusterid];
      if (map_entry.size() != 1) {
        intersection.emplace_back(std::move(map_entry));
      }
      m_clusterid_to_recordindeces[clusterid] = {};
    }
  }

  return intersection;
}

inline void TreeSearch::updateEdges(
    std::vector<edgemark>& crit, edgemark& uncov,
    std::vector<edgemark>& vertexhittings,
    std::vector<std::vector<edgemark>>& removed_criticals_stack,
    const std::vector<std::vector<unsigned>>& PLI) {
  // sample new edges
  //m_RC.start_timer(timer::sample_diff_sets);
  Hypergraph new_edges = sample(PLI);
 // m_RC.stop_timer(timer::sample_diff_sets);

  // find out which edges are supersets and therefore can be removed and save
  // indeces in descending order
  std::vector<std::vector<edge>::size_type> supsets_indeces;
  for (std::vector<edge>::size_type i_e = m_partial_HG.numEdges(); i_e > 0;
       /* gets decreased below */) {
    --i_e;

    for (const edge& new_edge : new_edges) {
      if (is_subset_of(new_edge, m_partial_HG[i_e])) {
        supsets_indeces.push_back(i_e);
        break;
      }
    }
  }

  // remove these edges from difference_graph, vertexhittings, uncov, crit,
  // removed_criticals

  for (std::vector<edge>::size_type i_e : supsets_indeces) {
    // difference_graph
    m_partial_HG[i_e] = m_partial_HG[m_partial_HG.numEdges() - 1];
    m_partial_HG.removeLastEdge();

    // vertexhittings
    for (edgemark& hittings : vertexhittings) {
      hittings[i_e] = hittings[hittings.size() - 1];
      hittings.pop_back();
    }

    // uncov
    uncov[i_e] = uncov[uncov.size() - 1];
    uncov.pop_back();

    // crit
    for (edgemark& em_crit : crit) {
      em_crit[i_e] = em_crit[em_crit.size() - 1];
      em_crit.pop_back();
    }

    // removed_criticals
    for (auto& removed_criticals : removed_criticals_stack) {
      for (auto& removed : removed_criticals) {
        removed[i_e] = removed[removed.size() - 1];
        removed.pop_back();
      }
    }
  }

  // insert the new edges in difference_graph, vertexhittings, uncov, crit,
  // removed_criticals

  // difference graph
  for (const edge& e : new_edges) {
    m_partial_HG.addEdge(e);
  }

  // vertexhittings
  for (int i_v = 0; i_v < m_partial_HG.numVertices(); ++i_v) {
    vertexhittings[i_v].resize(m_partial_HG.numEdges());
  }
  for (std::size_t i_e = m_partial_HG.numEdges() - new_edges.numEdges();
       i_e < m_partial_HG.numEdges(); ++i_e) {
    for (int i_v = find_first(m_partial_HG[i_e]);
         i_v != NPOS; i_v = find_next(m_partial_HG[i_e], i_v)) {
      set(vertexhittings[i_v], i_e);
    }
  }

  // uncov
  uncov.resize(m_partial_HG.numEdges(), true);

  // crit
  for (edgemark& em : crit) {
    em.resize(m_partial_HG.numEdges());
  }

  // removed_criticals
  for (auto& removed_criticals : removed_criticals_stack) {
    for (auto& removed : removed_criticals) {
      removed.resize(m_partial_HG.numEdges());
    }
  }
}

inline bool TreeSearch::S_fulfills_minimality_condition(
    const std::vector<edgemark>& crit) {
  for (const edgemark& em : crit) {
    if (none(em)) return false;
  }

  return true;
}

inline bool TreeSearch::isViolater(const std::vector<edgemark>& crit,
                                   const edgemark& v_hittings) {
  for (const edgemark& em : crit) {
    if (is_subset_of(em, v_hittings)) return true;
  }

  return false;
}

