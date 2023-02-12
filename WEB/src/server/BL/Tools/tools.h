#ifndef TOOLS_H
#define TOOLS_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include <string_view>
#include <string>
#include </home/julia/boost/boost/json.hpp>

#define EMPTY_INT -1
#define EMPTY_STRING ""
#define EMPTY_ACTION -1

class HTTPTools
{
public:
    static int parse_path(std::string &path_action, std::vector<std::string> &path_params,
                          const std::map<std::string, int> &requests_map);
    HTTPTools() = default;
};


class Tools
{
public:
    static std::vector<std::string> split_string(const std::string &str, const char delimiter);

    static std::string extract_string(const boost::json::value &val);

    template<typename T1>
    static T1 get_key(const std::map<T1, std::string> &map_, std::string val_)
    {
        T1 key;
        for (auto pair : map_) {
            if ((pair).second == val_) {
                return (pair).first;
            }
        }
        return key;
    }

    template<typename T1>
    static std::string get_string(const std::map<T1, std::string> &map_, T1 key_)
    {
        auto it = map_.find(key_);
        if (it == map_.end())
            return EMPTY_STRING;
        std::string value_ = (*it).second;

        return value_;
    };

    template<typename T1>
    static int get_int(const std::map<T1, std::string> &map_, T1 key_)
    {
        std::string value_ = get_string<T1>(map_, key_);
        if (value_ == EMPTY_STRING)
            return EMPTY_INT;

        return atoi((value_.c_str()));
    };
    Tools() = delete;
};

#endif // TOOLS_H
