#include "dbmanager.h"


DBmanager::DBmanager(const std::string &table) : m_table(table)
{
    conn = PQsetdbLogin("127.0.0.1", "5432", nullptr, nullptr,  "diploma", "julia", "201228");

    printf("\nSTATUS %d", PQstatus( conn));
    std::string query = "select * from " + m_table + " limit 1;";
    PGresult *res = PQexec(conn, query.c_str());
    int nr_cols =  PQnfields(res);


    for (int col = 0; col< nr_cols; col++) {
        col_names.push_back(PQfname(res, col));
    }

    printf("\n\n COLUMNS: %d", nr_cols);

  //  if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
  //  {
  //     throw std::runtime_error( PQerrorMessage( m_connection.get() ) );
   // }
}



std::shared_ptr<PGconn> DBmanager::connection() const
{
    return m_connection;
}

std::vector<std::string> DBmanager::selectColumn(const std::string &column) const
{
    std::vector<std::string> result;
    printf("%d", PQstatus( conn));
    std::string query = "select " + column + " from " + m_table + " limit 10;";
    PGresult *res = PQexec(conn, query.c_str());


    int nr_rows = PQntuples(res), nr_cols =  PQnfields(res);

  //  for (int col = 0; col< nr_cols; col++) {
   //     printf("\n");
        for (int row = 0; row < nr_rows; row++) {
            char *value = PQgetvalue(res, row, 0);
            result.push_back(value);
          //  printf("%s, ", value);
        }
  //  }
    return result;
}

std::vector<std::string> DBmanager::get_col_names() const
{
    return col_names;
}
