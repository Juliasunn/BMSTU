#pragma once
#include <filesystem>
#include <vector>
#include <set>
#define NPOS -1

typedef std::vector<bool> edge;
typedef std::vector<bool> edgemark;

/* is one a subset of another */
bool is_subset_of(const std::vector<bool> &one, const std::vector<bool> &another);

/* true if no bits are set, and otherwise returns false. */
bool none(const std::vector<bool> &one);
/* the lowest index i greater than pos such as bit i is set, or npos if no such index exists. */
int find_next(const std::vector<bool> &one, int pre_pos);
/* the number of seted bit i in pos */
int number(const edge &one, int pos);
/* the position of seted bit number  number*/
int pos(const edge &one, int number);
/* the lowest index i such as bit i is set, or npos if *this has no on bits. */
int find_first(const std::vector<bool> &one);

void set(std::vector<bool> &one, int pos);

/* Effects: Sets every bit in this bitset to 1. */
void set(std::vector<bool> &one);
void reset(std::vector<bool> &one);

/* Clears bit pos */
void reset(std::vector<bool> &one, int pos);
/* A new bitset that is the set difference of the bitsets a and b. */
edge operator-(const edge& a, const edge& b);

/* It performs bitwise-AND  */
edge operator&(const edge& a, const edge& b);

/* It returns notA  */
edge operator~(const edge& a);

/* It returns the number of set bits in dynamic_bitset.*/
int count(const edge& a);

edgemark operator||(const edgemark &one, const edgemark &another);

void print(const edge& a);

class Hypergraph {
 private:
  edge::size_type m_numVertices;
  std::vector<edge> m_Edges;

 public:
  Hypergraph() = delete;
  explicit Hypergraph(edge::size_type numVertices);

  std::vector<edge>::size_type numEdges() const { return m_Edges.size(); }
  edge::size_type numVertices() const { return m_numVertices; }

  inline void addEdge(const edge& newEdge) { m_Edges.push_back(newEdge); }
  inline void addEdge(edge&& newEdge) { m_Edges.push_back(newEdge); }
  inline void removeLastEdge() { m_Edges.pop_back(); }

  void addEdgeAndMinimizeInclusion(const edge& newEdge);

  inline edge& operator[](std::vector<edge>::size_type i_e) {
    return m_Edges[i_e];
  }
  inline const edge& operator[](std::vector<edge>::size_type i_e) const {
    return m_Edges[i_e];
  }

  inline std::vector<edge>::iterator begin() { return m_Edges.begin(); }
  inline std::vector<edge>::const_iterator begin() const {
    return m_Edges.begin();
  }

  inline std::vector<edge>::iterator end() { return m_Edges.end(); }
  inline std::vector<edge>::const_iterator end() const { return m_Edges.end(); }
};

