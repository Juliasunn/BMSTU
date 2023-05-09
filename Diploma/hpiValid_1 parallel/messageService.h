#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H
#include <thread>
#include <iostream>
#include <string>
#include "/usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h"
#include <stdlib.h>
#include <queue>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <pthread.h>
#include <map>
#include <set>
#include <memory>
#include <unordered_map>
#include "hypergraph.hpp"

#define TAG_STOP_COMMAND 1
#define TAG_DATA 2
#define TAG_PLI 3
#define TAG_HYPERGRAPH 4




class ProcInfo;
class Message {

//private:
    //std::vector<int> bc = std::vector<int>(2);
public:
    int tag;
    int sender_rank;


  //  std::string content;
   // bool *bool_content;

    virtual void send(const ProcInfo &info)  = 0;
    virtual void receive(ProcInfo &info, MPI_Status &stats) = 0;


    int content_size;

    ~Message() = default;
   // Message() = default;

    Message(int tag_) : tag(tag_) {};

  //  explicit Message(int tag_, bool *content_, int content_size_) :
   //     tag(tag_), bool_content(content_), content_size(content_size_) {printf("\nBOOL CONTRUCTOR CALLED\n");};

  //  explicit Message(int tag_, char *content_) : tag(tag_), content(content_) {};
   // explicit Message(int tag_, std::string content_) : tag(tag_), content(content_) {};


};

class PLIMessage : public Message {
private:
    int *m_buf;
    int m_size;



public:
    virtual void send(const ProcInfo &info) override;
    virtual void receive(ProcInfo &info, MPI_Status &stats) override;
    PLIMessage(int *buf, int size) : m_buf(buf), m_size(size), Message(TAG_PLI){};
    PLIMessage() :Message(TAG_PLI){};
    ~PLIMessage(){delete [] m_buf;};

    void putPLI(const std::vector<std::vector<unsigned> > &pli_, const int &nr_rows);
    std::vector<std::vector<unsigned>> getPLI();

};

class STOPMessage : public Message {

public:
    virtual void send(const ProcInfo &info) override;
    virtual void receive(ProcInfo &info, MPI_Status &stats) override;
    STOPMessage() : Message(TAG_STOP_COMMAND){ printf("\n - Create stop message");};
    ~STOPMessage()= default;

};

class EDGEMessage : public Message {
private:
    bool *m_buf;
    int m_size;


public:
    virtual void send(const ProcInfo &info) override;
    virtual void receive(ProcInfo &info, MPI_Status &stats) override;
     EDGEMessage() : Message(TAG_HYPERGRAPH){};
    ~EDGEMessage(){delete [] m_buf;};

    void putEdges(const Hypergraph &hg);

    void takeEdges(Hypergraph &hg, int edge_size);

};

class ProcInfo {
    int m_this_rank;
    int m_num_process;
   // std::queue<Message *> m_recMessages;

    std::queue<Message *> m_recPLI; /* */
    std::queue<Message *> m_recEdgess; /* */
    std::queue<Message *> m_recCMD;
    std::queue<Message *> m_sendMessages;

public:
    ProcInfo()
    {
        MPI_Comm_size(MPI_COMM_WORLD, &m_num_process);
        MPI_Comm_rank(MPI_COMM_WORLD, &m_this_rank);
    }

    int this_rank() const;
    int num_process() const;
  //  std::queue<Message *> &recMessages();
    std::queue<Message *> &sendMessages();
    static std::vector<std::set<int>> distribute(int n_owners,
                                                   int n_assigned);
    std::queue<Message *> &recPLI() ;
    std::queue<Message *> &recEdges() ;
    std::queue<Message *> &recCMD() ;
};

void init_semaphore();
void set_stop_flag();
bool get_stop_flag();

void push_to_send(ProcInfo& info, Message *message);  //планируем отправить
//void push_to_rec(ProcInfo& info, Message *message);  //получили но еще не прочитали
Message *pop_from_send(ProcInfo& info);
Message *pop_from_rec(ProcInfo& info, int tag);// готовы прочитать



void receive_Msg(char *msg, MPI_Status &stats, ProcInfo& info);

void start_messageservice(ProcInfo& info);
#endif // MESSAGESERVICE_H
