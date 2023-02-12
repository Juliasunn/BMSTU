#ifndef REQ_EXCEPTIONS_H
#define REQ_EXCEPTIONS_H
#include <exception>
#include <string>

class req_exception : public std::exception
{
    public:
    req_exception()=default;
    explicit req_exception(std::string &message):err_info(message){};

    const char *what() const noexcept override
    {
        return "invalid request";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
protected:
    std::string err_info;
};


class invalid_params : public req_exception
{
 public:// 400
    invalid_params()=default;
    explicit invalid_params(std::string &message):req_exception(message){};

    const char *what() const noexcept override
    {
        return "invalid request params";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class auth_exception : public req_exception
{
 public: //401
    auth_exception()=default;
    explicit auth_exception(std::string &message):req_exception(message){};

    const char *what() const noexcept override
    {
        return "invalid autorization token";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class res_not_found_exception : public req_exception
{
 public: //404
    res_not_found_exception()=default;
    explicit res_not_found_exception(std::string &message):req_exception(message){};

    const char *what() const noexcept override
    {
        return "No resource found";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class no_priveledges_exception : public req_exception
{
 public: //403
    no_priveledges_exception()=default;
    explicit no_priveledges_exception(std::string &message):req_exception(message){};

    const char *what() const noexcept override
    {
        return "User have no priveledges for this action";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class req_conflict_exception : public req_exception
{
 public: //409
    req_conflict_exception()=default;
    explicit req_conflict_exception(std::string &message):req_exception(message){};

    const char *what() const noexcept override
    {
        return "Request caused conflict";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

#endif // REQ_EXCEPTIONS_H
