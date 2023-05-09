#include "dbmanager.h"
#include <iostream>
#include <stdlib.h>


int main(int argc, char **argv)
{
    DBmanager db;
    auto names  = db.get_col_names();
    for (auto name: names) {
        std::cout << name << std::endl;

    }
    db.selectColumn("vehicle", names[0]);

    //db.selectColumn("vehicle", const std::string &column)

   return 0;
}
