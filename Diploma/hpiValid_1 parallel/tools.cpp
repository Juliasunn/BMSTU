#include "tools.hpp"
#define END_CLUSTER -1
#define END_PLI -2
/* Debug print */
void print_inverse_mapping(const std::vector<std::vector<unsigned> > &inverse_mapping)
{
    for (auto const &row: inverse_mapping) {
        std::cout << " \nNext column:  ";
        for (int i = 0; i< row.size(); i++) {
            std::cout << "str_id: " << i << " in sluster: " << row[i] << " ; ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_plis(const std::vector<std::vector<std::vector<unsigned>>> &PLIs)
{
    for (auto const &column: PLIs) {
        std::cout << " \n Next column:  ";
        for (int i = 0; i< column.size(); i++) {
            std::cout << " value_id: " << i << " row id_s: {";
            for (int j = 0; j< column[i].size(); j++) {
                std::cout << column[i][j] << ", ";
            }
            std::cout << " } ";
        }
        std::cout << "\n";
    }
}

int appendPLI(ETable &PLIs, int start, std::string &content)
{
    std::stringstream ss(content);
    std::string line, value;
    int max_row = start;

    std::getline(ss, line);
    int column_n = std::stoi( line );

    while (std::getline(ss, line)) {
        std::stringstream ss_(line);
        ss_ >> value;
        std::string line_;
        while (std::getline(ss_, line_, ' ')) {
            try {
                if (!line_.empty()) {
                    PLIs.value_to_rows[column_n][value].push_back(stoi(line_)+start);
                    if ( stoi(line_)+start > max_row) {
                        max_row = stoi(line_)+start;
                    }
                }
            } catch (...) {
            }
        }
    }
    PLIs.nr_rows = max_row+1;
    return 0;
}

int *putPLI(const std::vector<std::vector<unsigned>> &pli_, const int &nr_rows, int buf_size)
{
    int pos = 0;
    int *buf = new int[pli_.size() * nr_rows];
    for (auto &cluster : pli_) {
        for (auto &row_id : cluster) {
            buf[pos] =row_id;
            pos ++;


        }
        buf[pos] = END_CLUSTER;
        pos ++;
    }
    buf[pos] = END_PLI; //конец
    return buf;
  //  char *buf = new char[content_size];

 //   content += std::to_string(col_id) + '\n'; //column
 //   for (auto const &pair: pli_) {
    //    content += pair.first; //value
    //    for (auto val : pair.second) {
     //       content += " " + std::to_string(val);   //row_id
      //  }
      //  content += '\n';
   // }
}

std::vector<std::vector<unsigned>> getPLI(int *buf, int buf_size)
{
    int pos = 0;
    std::vector<std::vector<unsigned>> pli_;
    std::vector<unsigned> cluster;
    for (int pos=0; pos<buf_size; pos++) {
        if (buf[pos]<0) {
            if (cluster.size() > 0) {
                pli_.push_back(cluster);
            }
            if (buf[pos] == END_PLI) {
                return pli_;
            }
            cluster.clear();
        }
        else {
            cluster.push_back(buf[pos]);
        }
    }
    return pli_;


}

bool *putHypergraph(const Hypergraph &hg, int &content_size)
{
    content_size = hg.numEdges()*hg.numVertices();
    bool *buf = new bool[content_size];
    int pos = 0;
    for (const edge& e : hg) {
        for (bool  v : e) {
             buf[pos] = v;
             pos++;
        }
    }
    return buf;

}


void takeHypergraph(Hypergraph &hg, bool *buf, int buf_size, int edge_size)
{
    hg.removeLastEdge();
    edge new_edge;

    int v_num = 0;
    for (int pos = 0; pos < buf_size; pos++) {
       // printf("%d ", buf[pos]);
        if (v_num >= hg.numVertices()) {
           // hg.addEdge(new_edge);
            hg.addEdgeAndMinimizeInclusion(new_edge);

            new_edge.clear();
            v_num = 0;

        }
        new_edge.push_back(buf[pos]);
        v_num++;
    }

}

