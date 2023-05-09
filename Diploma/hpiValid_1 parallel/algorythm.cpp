#include <algorythm.h>
#include "messageService.h"
#include <tree_search.hpp>

#define FILE "/home/julia/Documents/8_SEM/DIPLOM/Letters_7.txt"


void run(ProcInfo& info)
{
    PLITable tab = preprocess(FILE, info);

    TreeSearch trS = TreeSearch(tab, info);
    trS.run();

  //  if (info.this_rank()==1) {
  //  std::string output;

  //  output+= "\n PROCESS " + std::to_string(info.this_rank()) + " FOUND UCCs: \n";
  //  for (auto S : trS.UCCs) {
    //    for (auto col_id = 0; col_id < S.size(); col_id++) {
     //       output+=  " " + std::to_string(S[col_id]);
     //   }
      //  output+='\n';
       // std::cout << " - precess: " << info.this_rank() << "\n";
    //}
   // std::cout<<output;
   // }

    std::cout<<"\nNumber UCCs found"<<trS.UCCs.size();
    printf("\nStart");
    Message *my_stop_msg = new STOPMessage();
    printf("\n   - Created msg");
    push_to_send(info, my_stop_msg);
    printf("\nSENDED");
   // return;

    pop_from_rec(info, TAG_STOP_COMMAND);
    set_stop_flag();

  //  while ( !get_stop_flag() ) {
    //    Message *msg =  pop_from_rec(info);
    //    if (msg->tag == TAG_STOP_COMMAND) {
     //       set_stop_flag();
            printf("\n Stop flag =  %d for process: %d", get_stop_flag(), info.this_rank());
           // return;
     //     }
    //}
    printf("\n [!!]Process %d Finish ALGORYTHM thread [!!]", info.this_rank());
}



