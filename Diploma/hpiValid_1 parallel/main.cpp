#include "messageService.h"
#include <thread>
#include <iostream>
#include "/usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h"
#include <algorythm.h>
#include <pthread.h>
//clock_t stopTime = clock ();



int main(int argc, char **argv)
{
  //  std::string tableName;

   //std::cout << "Введите название таблицы: ";
   // std::cin >> tableName;
   // std::cout << "\nНазвание таблицы: "<< tableName;

    MPI_Init(&argc, &argv);
    //std::cout << "\nНазвание таблицы: "<< tableName;
    init_semaphore();

    ProcInfo info;

    std::thread msg_thread = std::thread(start_messageservice, std::ref(info));
    std::thread alg_thread = std::thread(run, std::ref(info));
    alg_thread.join();
    msg_thread.join();

    MPI_Finalize();

   return 0;
}
