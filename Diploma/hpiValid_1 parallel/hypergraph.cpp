#include "hypergraph.hpp"

#include <fstream>

Hypergraph::Hypergraph(edge::size_type numVertices)
    : m_numVertices(numVertices), m_Edges() {}

void Hypergraph::addEdgeAndMinimizeInclusion(const edge &newEdge) {
  // is newEdge a supset of an edge in m_Edges?
  bool is_supset = false;
  // list of indeces of supsets of newEdge from m_Edges in descending order
  std::vector<std::vector<edge>::size_type> supsets_indeces;
  for (std::vector<edge>::size_type i_e = this->numEdges(); i_e > 0;
       /* gets decreased below */) {
    --i_e;

    if (is_subset_of(m_Edges[i_e], newEdge)) {
      is_supset = true;
      break;
    }

    if (is_subset_of(newEdge, m_Edges[i_e])) {
      supsets_indeces.push_back(i_e);
    }
  }

  if (!is_supset) {
    for (std::vector<edge>::size_type i_e : supsets_indeces) {
      m_Edges[i_e] = m_Edges[m_Edges.size() - 1];
      m_Edges.pop_back();
    }
    m_Edges.push_back(newEdge);
  }
}

bool is_subset_of(const std::vector<bool> &one, const std::vector<bool> &another)
{
    bool is_subset = true;
    for (size_t i = 0; i < one.size(); i++) {
        if (!one[i]) {
            continue;
        }
        else {
            if (!another[i]) {
                is_subset = false;
                break;
            }

        }
    }
   return is_subset;
}

bool none(const std::vector<bool> &one)
{
    for (size_t i = 0; i < one.size(); i++) {
        if (one[i]) {
            return false;
        }
    }
    return true;
}

void set(std::vector<bool> &one, int pos)
{
    one[pos] = true;
}

int find_next(const std::vector<bool> &one, int pre_pos)
{
    if (pre_pos +1 >= (int)(one.size())) {
        return -1;
    }
    //unsigned int next_pos = pre_pos;
    for (int pos = pre_pos+1; pos < (int)one.size(); pos++ ) {
        if (one[pos]) {
            return pos;
        }
    }
    return -1;
}

int find_first(const std::vector<bool> &one)
{
    //unsigned int next_pos = pre_pos;
    for (unsigned int pos = 0; pos < one.size(); pos++ ) {
        if (one[pos]) {
            return pos;
        }
    }
    return -1;
}

void reset(std::vector<bool> &one, int pos)
{
    one[pos] = false;
}

edge operator-(const edge &a, const edge &b)
{
    edge AdiffB = a;
    for (unsigned int pos = 0; pos < a.size(); pos++ ) {
        if (b[pos]) {
            AdiffB[pos] = 0;
        }
    }
    return AdiffB;


}

edge operator&(const edge &a, const edge &b)
{
    edge AandB = a;
    for (unsigned int pos = 0; pos < AandB.size(); pos++ ) {
        if (!b[pos]) {
            AandB[pos] = 0;
        }
    }
    return AandB;
}

int count(const edge &a)
{
    int seted = 0;
    for (unsigned int pos = 0; pos < a.size(); pos++ ) {
        if (a[pos]) {
            seted++;
        }
    }
    return seted;
}



edge operator~(const edge &a)
{
    edge notA(a.size());
    for (unsigned int pos = 0; pos < notA.size(); pos++ ) {
        if (!a[pos]) {
            notA[pos] = true;
        }
    }
    return notA;

}

void set(std::vector<bool> &one)
{
    for (unsigned int pos = 0; pos < one.size(); pos++ ) {
        one[pos] = 1;
    }
}

void reset(std::vector<bool> &one)
{
    for (unsigned int pos = 0; pos < one.size(); pos++ ) {
        one[pos] = 0;
    }
}

void print(const edge &one)
{
    for (unsigned int pos = 0; pos < one.size(); pos++ ) {
        printf(" %d ", one[pos]);
    }
    printf("\n");
}

edgemark operator||(const edgemark &one, const edgemark &another)
{
    edgemark ORedgemark(one.size());
    for (size_t i = 0; i < ORedgemark.size(); i++) {
        ORedgemark[i] = one[i] || another[i];
    }
    return ORedgemark;
}

int number(const edge &one, int pos) //с 0
{
    if (pos > one.size() || !one[pos]) {
        return -1;
    }
    int num = 0;
    for (int i =0; i < pos; i++) {
        if (one[pos]) {
            num++;
        }
    }
    return num;

}

int pos(const edge &one, int number) //с 0
{
    int pos = 0;
    int cnt = 0;
    while (cnt < number)  {
        if (one[pos]) {
            cnt++;
        }

        pos++;
    }
    return pos-1;
}
