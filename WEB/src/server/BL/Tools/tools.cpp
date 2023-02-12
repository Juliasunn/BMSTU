#include "tools.h"
#include "iostream"

std::vector<std::string> Tools::split_string(const std::string &str, const char delimiter)
{
    std::vector<std::string> result;

    auto pre_pos = str.begin();
    auto pos = std::find(str.begin(), str.end(), delimiter);

    while (pre_pos <= str.end())
    {
        result.push_back(str.substr(pre_pos-str.begin(), pos-str.begin()));
        pre_pos = pos+1;
        pos = std::find(pos+1, str.end(), delimiter);
    }
    return result;
}

std::string Tools::extract_string(const boost::json::value &val)
{
    std::string str = serialize(val);

    auto pos = std::find(str.begin(), str.end(), '"');

    while (pos != str.end())
    {
        str.erase(pos);
        pos = std::find(str.begin(), str.end(), '"');
    }
    return str;
}

int HTTPTools::parse_path(std::string &path_action, std::vector<std::string> &path_params,
                          const std::map<std::string, int> &requests_map)
{

    std::string params_str;
    auto it = requests_map.find(path_action);
    while (it == requests_map.end()){
        int pos = path_action.find_last_of('/');

        if (pos == -1) {
                return EMPTY_ACTION;
        }

        params_str = path_action.substr(pos+1, path_action.size());
        std::string path = path_action.substr(0, pos+1);
        path_action = path_action.substr(0, pos);
        std::cout << "ACTION =" <<" "<< path_action << " " << path<<std::endl;

        it = requests_map.find(path);
    }
    path_params = Tools::split_string(params_str, '/');
    int req_id = (*it).second;
    return req_id;

}

