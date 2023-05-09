#include "messageService.h"
#define END_CLUSTER -1
#define END_PLI -2

std::mutex send_mutex, rec_pli_mutex, rec_edge_mutex, rec_cmd_mutex;
sem_t pli_to_read, edge_to_read, cmd_to_read;

volatile bool stop_flag = false;
void set_stop_flag() {
    //printf("\n[!!!] Set stop flag[!!!]\n");
    stop_flag = true;
}
bool get_stop_flag() {
    return stop_flag;
}

void init_semaphore() {
    sem_init(&pli_to_read, 0, 0);
    sem_init(&edge_to_read, 0, 0);
    sem_init(&cmd_to_read, 0, 0);
}


void push_to_send(ProcInfo& info, Message *message) { //планируем отправить
    const std::lock_guard<std::mutex> lock(send_mutex);
    info.sendMessages().push(message);
    printf("\n Push to send - OK");
}

//void push_to_rec(ProcInfo& info, Message *message) { //получили но еще не прочитали
//    const std::lock_guard<std::mutex> lock(rec_mutex);
//    info.recMessages().push(message);
//}

Message *pop_from_send(ProcInfo& info) { // отправили
    const std::lock_guard<std::mutex> lock(send_mutex);
    Message *msg = info.sendMessages().front();
    info.sendMessages().pop();
    return msg;
}

Message *pop_from_rec(ProcInfo& info, int tag) { // готовы прочитать
    Message *msg;
    if (tag ==  TAG_STOP_COMMAND) {
        sem_wait(&cmd_to_read);
        const std::lock_guard<std::mutex> lock_cmd(rec_cmd_mutex);
        msg = info.recCMD().front();
        info.recCMD().pop();
    }
    else if (tag == TAG_PLI){
        sem_wait(&pli_to_read);
        const std::lock_guard<std::mutex> lock_pli(rec_pli_mutex);
        msg = info.recPLI().front();
        info.recPLI().pop();
    }
    else {
        sem_wait(&edge_to_read);
        const std::lock_guard<std::mutex> lock_edge(rec_edge_mutex);
        msg = info.recEdges().front();
        info.recEdges().pop();
    }

    //printf("\nProcess %d  - Wait, Sem value: %d", info.this_rank(), has_msg_to_read);
  //  sem_wait(&has_msg_to_read);
    //printf("\nProcess %d - Stop wait, Sem value: %d", info.this_rank(),  has_msg_to_read);

   // const std::lock_guard<std::mutex> lock(rec_mutex);
   // Message *msg = info.recMessages().front();
   // info.recMessages().pop();
    return msg;
}




void receive_Msg( Message *msg, MPI_Status &stats, ProcInfo& info) { //получить и добавить в очередь для чтения
    msg->receive(info, stats);
   // push_to_rec(info, msg);
   //sem_post(&has_msg_to_read);
    return;

  //  char *char_buf;
  // bool *buf;
  // int cnt;
  // int command;
  // MPI_Status stats;
 //  printf("\n [!] try Recv [!]");

//   switch (recMsg.tag) {
 //      case TAG_STOP_COMMAND:
          //  printf("\n [!] try Recv stop command[!]");
    //       MPI_Recv(&command, 1, MPI_INT, MPI_ANY_SOURCE, TAG_STOP_COMMAND, MPI_COMM_WORLD, &stats);
          // receive_Msg(new_msg, info);
           //printf("\n [!] Received stop message [!]");
       //    break;
      // case TAG_HYPERGRAPH:
     //      printf("!!!");
         //  MPI_Get_count(&stats, MPI_LOGICAL, &cnt);
         //  try {
           //    buf = new bool[cnt+1];

         // } catch (const std::bad_alloc& e) {
          //     std::cout << "Allocation failed: " << e.what() << cnt <<'\n';
         //}

          // MPI_Recv(buf, cnt,  MPI_LOGICAL,  MPI_ANY_SOURCE, TAG_HYPERGRAPH, MPI_COMM_WORLD, &stats);
          // recMsg = Message(TAG_HYPERGRAPH, buf, cnt);
          // break;
     //  default:
        //    MPI_Get_count(&stats, MPI_CHAR, &cnt);

          //  try {
          //      char_buf = new char[cnt+1];

          // } catch (const std::bad_alloc& e) {
           //     std::cout << "Allocation failed: " << e.what() << cnt <<'\n';
           //     return;
          // }

           // MPI_Recv(char_buf, cnt, MPI_CHAR,  MPI_ANY_SOURCE, recMsg.tag, MPI_COMM_WORLD, &stats);
           // recMsg.content = std::string(char_buf);
     //  break;
 //  }
   // push_to_rec(info, recMsg);
  // sem_post(&has_msg_to_read);
   // printf("\n Result of Sem post: %d Sem value after post %d: ", sem_post(&has_msg_to_read), has_msg_to_read);
    //printf("\n - Process %d received message with tag: %d\n", info.this_rank(), recMsg.tag);
}

void send_Msg(ProcInfo& info) {
    printf("\n - Messageservice send message");
    MPI_Request reqs;

    Message *msg = pop_from_send(info);

    msg->send(info);
    return;


   // int send_rank = (info.this_rank() == 0) ? 1 : 0;

   // if (msg.tag == TAG_STOP_COMMAND) {
     //   int stop;
     //   MPI_Isend(&stop, 1, MPI_INT, send_rank, TAG_STOP_COMMAND, MPI_COMM_WORLD, &reqs);
       // printf("\n - Send STOP msg to : %d\n", send_rank);
  //  }
   // else if (msg.tag == TAG_HYPERGRAPH) {
     //   printf("!!!");
      //  MPI_Isend(msg.bool_content, msg.content_size, MPI_LOGICAL, send_rank, TAG_HYPERGRAPH, MPI_COMM_WORLD, &reqs);
        //printf("\n - Send STOP msg to : %d\n", send_rank);
   // }
   // else {
    //    const char *char_msg = msg.content.c_str();
    //    MPI_Isend(char_msg, msg.content.length(), MPI_CHAR, send_rank, msg.tag , MPI_COMM_WORLD, &reqs);
       // printf("\n - Send message: %s queue size: %d\n", char_msg, info.sendMessages().empty());
   // }

}

void start_messageservice(ProcInfo& info) {


    while (!(get_stop_flag()) || !(info.sendMessages().empty())) {
         MPI_Status stats;
        int rec_flag =0;
         MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &rec_flag, &stats);


        if (rec_flag) {
            printf("\nReceived!!");
            Message *msg;
            switch (stats.MPI_TAG) {
            case TAG_STOP_COMMAND:
                 msg = new STOPMessage();
                 msg->receive(info, stats);
                break;
            case TAG_PLI:

                  msg = new PLIMessage();
                  msg->receive(info, stats);
                  break;
            default:
                 printf("\n Received EDGE");
                  msg = new EDGEMessage();
                  msg->receive(info, stats);
                  break;
            }

           // Message new_msg(stats.MPI_TAG);
          //  receive_Msg(msg, stats, info);
        }

        if (!(info.sendMessages().empty())) {
            printf("\n - Queue = %d", info.sendMessages().size());
            send_Msg(info);
        }
    }
}


int ProcInfo::num_process() const
{
    return m_num_process;
}

//std::queue<Message *> &ProcInfo::recMessages()
//{
//    return m_recMessages;
//}

std::queue<Message *> &ProcInfo::sendMessages()
{
    return m_sendMessages;
}

std::vector<std::set<int> > ProcInfo::distribute(int n_owners, int n_assigned)
{
    std::vector<std::set<int>> distributed(n_owners); //набор ветвей распределенных для данного процесса

    int n_to_assign = n_assigned / n_owners;
    //последние ветви мб не распределены если не делится нацело
    for (int o_idx = 0; o_idx < n_owners; o_idx ++) {

        for (int a_idx = o_idx*n_to_assign; a_idx < (o_idx+1)*n_to_assign; a_idx ++) {
            distributed[o_idx].insert(a_idx);
        }
     }

    for  (int a_idx = (n_to_assign*n_owners), o_idx = 0;
                          a_idx < n_assigned; a_idx++, o_idx++) {
        printf("\n a_idx: %d, o_idx: %d", a_idx, o_idx);
        distributed[o_idx].insert(a_idx);
     }
    return distributed;
}

std::queue<Message *> &ProcInfo::recPLI()
{
    return m_recPLI;
}



std::queue<Message *> &ProcInfo::recEdges()
{
    return m_recEdgess;
}

std::queue<Message *> &ProcInfo::recCMD()
{
    return m_recCMD;
}

int ProcInfo::this_rank() const
{
    return m_this_rank;
}

void PLIMessage::send(const ProcInfo &info)
{
    MPI_Request reqs;

    for (int rank = 0; rank < info.num_process(); rank++) {
        if (rank != info.this_rank()) {
            MPI_Isend(m_buf, m_size, MPI_INT, rank, TAG_PLI , MPI_COMM_WORLD, &reqs);
        }
    }
}

void PLIMessage::receive(ProcInfo &info, MPI_Status &stats)
{

    MPI_Get_count(&stats, MPI_LOGICAL, &m_size);
    try {
        m_buf = new int[m_size];

   } catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << m_size <<'\n';
   }

    MPI_Recv(m_buf, m_size,  MPI_INT,  MPI_ANY_SOURCE, TAG_PLI, MPI_COMM_WORLD, &stats);
    sender_rank = stats.MPI_SOURCE;

    const std::lock_guard<std::mutex> lock(rec_pli_mutex);
    info.recPLI().push(this);
    sem_post(&pli_to_read);
}

std::vector<std::vector<unsigned> > PLIMessage::getPLI()
{
    int pos = 0;
    std::vector<std::vector<unsigned>> pli_;
    std::vector<unsigned> cluster;
    for (int pos=0; pos<m_size; pos++) {
        printf("%d,", m_buf[pos]);
        if (m_buf[pos] == END_PLI || m_buf[pos] == END_CLUSTER) {
            if (cluster.size() > 0) {
                pli_.push_back(cluster);
                cluster.clear();
            }
            if (m_buf[pos] == END_PLI) {
                return pli_;
            }

        }
        else {
            cluster.push_back(m_buf[pos]);
        }
    }
    return pli_;

}

void PLIMessage::putPLI(const std::vector<std::vector<unsigned> > &pli_, const int &nr_rows)
{
   int pos = 0;
   /* На значаие цифры (инлексы строк в кластерах) +
    *  на разделители между кластерами (по кол-ву кластеров) + на окончание*/
   m_size = pli_.size() * nr_rows+(pli_.size())+1;
   m_buf = new int[m_size];
    for (auto &cluster : pli_) {
        for (auto &row_id : cluster) {
           m_buf[pos] =row_id;
           pos ++;
         }
         m_buf[pos] = END_CLUSTER;
         pos ++;
    }
    m_buf[pos] = END_PLI; //конец

}


void STOPMessage::send(const ProcInfo &info)
{
   // printf("\n - STOPMessage::send %d %d", info.num_process(), info.this_rank());
    int stop;
    MPI_Request reqs;
    for (int rank = 0; rank < info.num_process(); rank++) {
      //  printf ("\n - rank = %d", rank);
        if (rank != info.this_rank()) {
           MPI_Isend(&stop, 1, MPI_INT, rank, TAG_STOP_COMMAND, MPI_COMM_WORLD, &reqs);
          // printf("\n - send msg");
        }

    }
}


void STOPMessage::receive(ProcInfo &info, MPI_Status &stats)
{
   // printf("\n - STOPMessage::receive");
    int command;
    MPI_Recv(&command, 1, MPI_INT, MPI_ANY_SOURCE, TAG_STOP_COMMAND, MPI_COMM_WORLD, &stats);
    sender_rank = stats.MPI_SOURCE;

    const std::lock_guard<std::mutex> lock(rec_cmd_mutex);
    info.recCMD().push(this);
    sem_post(&cmd_to_read);
}

void EDGEMessage::send(const ProcInfo &info)
{
    printf(" - EDGEMessage::send");
    MPI_Request reqs;
   // return;
    for (int rank = 0; rank < info.num_process(); rank++) {
        if (rank != info.this_rank()) {
           MPI_Isend(m_buf, m_size, MPI_LOGICAL, rank, TAG_HYPERGRAPH, MPI_COMM_WORLD, &reqs);
        }
    }
}

void EDGEMessage::receive(ProcInfo &info, MPI_Status &stats)
{
  //  return;

    MPI_Get_count(&stats, MPI_LOGICAL, &m_size);
    printf(" - EDGEMessage::receive m_size = %d", m_size);
    try {
        m_buf = new bool[m_size*4];

   } catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << m_size <<'\n';
   }

    MPI_Recv(m_buf, m_size*4,  MPI_LOGICAL,  MPI_ANY_SOURCE, TAG_HYPERGRAPH, MPI_COMM_WORLD, &stats);
    sender_rank = stats.MPI_SOURCE;

    const std::lock_guard<std::mutex> lock(rec_edge_mutex);
    info.recEdges().push(this);
    sem_post(&edge_to_read);
}

void EDGEMessage::putEdges(const Hypergraph &hg)
{
     printf(" - EDGEMessage::putEdges");
    m_size = hg.numEdges()*hg.numVertices();
    m_buf = new bool[m_size];
    int pos = 0;
    for (const edge& e : hg) {
        for (bool  v : e) {
             m_buf[pos] = v;
             pos++;
        }
    }
}

void EDGEMessage::takeEdges(Hypergraph &hg, int edge_size)
{
    hg.removeLastEdge();
    edge new_edge;

    int v_num = 0;
    for (int pos = 0; pos < m_size; pos++) {
       // printf("%d ", buf[pos]);
        if (v_num >= hg.numVertices()) {
           // hg.addEdge(new_edge);
            hg.addEdgeAndMinimizeInclusion(new_edge);

            new_edge.clear();
            v_num = 0;

        }
        new_edge.push_back(m_buf[pos]);
        v_num++;
    }
}
