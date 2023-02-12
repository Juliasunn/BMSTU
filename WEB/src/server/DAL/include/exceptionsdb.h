#ifndef EXCEPTIONSDB_H
#define EXCEPTIONSDB_H
#include <exception>
#include <string>
#include "DAL_global.h"

class base_exception : public std::exception
{
    public:
    base_exception()=default;
    explicit base_exception(std::string &message):err_info(message){};

    const char *what() const noexcept override
    {
        return "runtume error";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
protected:
    std::string err_info;
};


class confile_exception : public base_exception
{
 public:
    confile_exception()=default;
    explicit confile_exception(std::string &message):base_exception(message){};

    const char *what() const noexcept override
    {
        return "invalid config file";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class db_exception : public base_exception
{
 public:
    db_exception()=default;
    explicit db_exception(std::string &message):base_exception(message){};

    const char *what() const noexcept override
    {
        return "database exception";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class db_not_open_exception : public db_exception
{
 public:
    db_not_open_exception()=default;
    explicit db_not_open_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "Database is not open";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class invalid_query_exception : public db_exception
{
 public:
    invalid_query_exception()=default;
    explicit invalid_query_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "Invalid query";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class user_already_exists_exception : public db_exception
{
 public:
    user_already_exists_exception()=default;
    explicit user_already_exists_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "User already exists";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class user_not_exists_exception : public db_exception
{
 public:
    user_not_exists_exception()=default;
    explicit user_not_exists_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "User do not exists";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class no_result_exception : public db_exception
{
 public:
    no_result_exception()=default;
    explicit no_result_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "Database return no result";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

class DAL_EXPORT forbidden_symb_exception : public db_exception
{
 public:
    forbidden_symb_exception()=default;
    explicit forbidden_symb_exception(std::string &message):db_exception(message){};

    const char *what() const noexcept override
    {
        return "Param contains not allowed symbol";
    }
    const std::string &get_info() const noexcept
    {
        return err_info;
    }
};

#endif // EXCEPTIONSDB_H
