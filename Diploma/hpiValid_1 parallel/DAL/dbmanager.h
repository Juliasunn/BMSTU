#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <memory>
#include <mutex>
#include <libpq-fe.h>
#include <vector>

class DBmanager
{
public:
    DBmanager(const std::string &table);

    std::shared_ptr<PGconn> connection() const;
    std::vector<std::string> selectColumn(const std::string &column) const;

    std::vector<std::string> get_col_names() const;

private:
    void establish_connection();
    PGconn *conn;
    std::vector<std::string> col_names;
    std::string m_table;
//    std::string m_dbhost = "localhost";
  //  std::string         m_dbport = "5432";
  //  std::string m_dbname = "diploma";
   // std::string m_dbuser = "julia";
   // std::string m_dbpass = "201228";

    std::shared_ptr<PGconn>  m_connection;

};


#endif // DBMANAGER_H
