#pragma once
#include "messageService.h"
#include <filesystem>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stdio.h>
#include "tools.hpp"
#include "DAL/dbmanager.h"

void load(const std::vector<std::string> &col_names, const DBmanager &db, ETable &res);
ETable load_essential_table(const std::string& input_file, ProcInfo& info);
void merge(ETable &tbl, ProcInfo& info);
