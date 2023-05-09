#pragma once

#include <random>
#include <stack>
#include <math.h>
#include "hypergraph.hpp"
#include "messageService.h"

struct PLITable;

class TreeSearch {
 public:
  std::vector<edge> UCCs;
  TreeSearch(const PLITable& tab, ProcInfo& info);
  ProcInfo &info;

  void run();

 private:
  const PLITable& m_tab;

  // the partial hypergraph of difference sets
  Hypergraph m_partial_HG;

  // exception to throw, when timeout happens
  const unsigned timeout = 10;

  // a mapping from clusterid to recordindices that is used for the
  // intersection of PLIs with single-column PLIs
  std::vector<std::set<int>> distribute_branches(bool &distribution_flag, int n_proc,
                                                 int n_br);

  std::vector<std::vector<unsigned>> m_clusterid_to_recordindeces;

  std::default_random_engine m_gen;
  Hypergraph sample(const std::vector<std::vector<unsigned>>& PLI);

  inline void update_crit_and_uncov(
      std::vector<std::vector<edgemark>>& removed_criticals_stack,
      std::vector<edgemark>& crit, edgemark& uncov, const edgemark& v_hittings);
  inline void restore_crit_and_uncov(
      std::vector<std::vector<edgemark>>& removed_criticals_stack,
      std::vector<edgemark>& crit, edgemark& uncov);

  inline bool extend_or_confirm_S(
      edge& S, edge& CAND, std::vector<edgemark>& crit, edgemark& uncov,
      std::vector<edgemark>& vertexhittings,
      std::vector<std::vector<edgemark>>& removed_criticals_stack,
      std::stack<std::vector<std::vector<unsigned>>>& intersection_stack,
      std::deque<edge::size_type>& tointersect_queue,
          std::set<int> procs);

  inline void pullUpIntersections(
      std::stack<std::vector<std::vector<unsigned>>>& intersection_stack,
      std::deque<edge::size_type>& tointersect_queue);

  std::vector<std::vector<unsigned>> intersectClusterListAndClusterMapping(
      const std::vector<std::vector<unsigned>>& PLI,
      const std::vector<unsigned>& inverse_mapping);

  inline void updateEdges(
      std::vector<edgemark>& crit, edgemark& uncov,
      std::vector<edgemark>& vertexhittings,
      std::vector<std::vector<edgemark>>& removed_criticals_stack,
      const std::vector<std::vector<unsigned>>& PLI);

  inline bool S_fulfills_minimality_condition(
      const std::vector<edgemark>& crit);

  inline bool isViolater(const std::vector<edgemark>& crit,
                         const edgemark& v_hittings);
};



