#include "include/querycreator.h"
#include "QDebug"

void PostgreQueryCreator::convert(std::string &query_text,
                                  std::string sep, std::vector<QueryParam> params) const
{
    int n = params.size();
    for (int i = 0; i< n-1; i++)
        query_text= query_text+params[i].getCondition(DBCols)+ " "+sep+" ";
    query_text= query_text+params.at(n-1).getCondition(DBCols);
}

std::string PostgreQueryCreator::createSelectQuery(Table tableName,
                         std::vector<Column> columns,
                          std::vector<QueryParam> params, Column sort_raw)
{
    int n = columns.size();

    std::string query_text = "select ";
    for (int i = 0; i< n-1; i++)
        query_text= query_text+DBCols[columns[i]]+", ";
    if (n==0)
        query_text= query_text+"*";
    else
        query_text= query_text+DBCols[columns.at(n-1)];

    query_text = query_text+" from " + DBTables[tableName] + " where ";

    if (params.size()==0)
        query_text+= " true ";
    else
        convert(query_text, "and", params);
    if (sort_raw!=EMPTY)
        query_text = query_text+"order by "+DBCols[sort_raw];
  //  qDebug() <<query_text.c_str();
    return query_text ;
}

std::string PostgreQueryCreator::createCountQuery(Table tableName, std::vector<QueryParam> params)
{
    std::string query_text = "select count (*) from " + DBTables[tableName] + " where ";

    convert(query_text, "and", params);
    return query_text;
}

std::string PostgreQueryCreator::createUpdateQuery(Table tableName,
            std::vector<QueryParam> vals, std::vector<QueryParam> conds)
{
    std::string query_text = "update " + DBTables[tableName] + " set ";
    convert(query_text, ",", vals);
    query_text += " where ";
    convert(query_text, "and", conds);
    return query_text;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string PostgreQueryCreator::createDeleteQuery(Table tableName, std::vector<QueryParam> conds)
{
    std::string query_text = "delete from " + DBTables[tableName];

    query_text += " where ";
    convert(query_text, "and", conds);
    return query_text;
}

std::string PostgreQueryCreator::createJoinQuery(std::vector<Table> tableName,
                                                 std::vector<Column> join_columns,
                                                 std::vector<Column> columns,
                                                 std::vector<QueryParam> params)
{
    int n = columns.size();

    std::string query_text = "select ";
    for (int i = 0; i< n-1; i++)
        query_text= query_text+DBCols[columns[i]]+", ";
    if (n==0)
        query_text= query_text+"*";
    else
        query_text= query_text+DBCols[columns.at(n-1)];

    query_text = query_text+" from " + this->createJoin(tableName, join_columns)
            + " where ";////сюда нужно объединение

    if (params.size()==0)
        query_text+= " true ";
    else
        convert(query_text, "and", params);

  //  qDebug() <<query_text.c_str();
    return query_text ;
}

std::string PostgreQueryCreator::createJoin(std::vector<Table> tableName, std::vector<Column> join_columns)
{
    int n = tableName.size(); //кол-во таблиу кторые обьединяем
    std::string joinTable = DBTables[tableName.at(0)]; //название первой таблицы

    for (int i = 1; i < n; i++)
    {
        joinTable += " join ";
        joinTable += DBTables[tableName.at(i)];
        joinTable += " on ";
        joinTable = joinTable + DBCols[join_columns.at(i-1)]+"="+DBCols[join_columns.at(i)];
    }
    return joinTable;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string PostgreQueryCreator::createInsertQuery(Table tableName,
                                 std::vector<QueryParam> params)
{
    int n = params.size();

    std::string query_text = "insert into " + DBTables[tableName] +
            " (id, ";
    for (int i = 0; i< n-1; i++)
        query_text= query_text+params[i].getColName(DBCols)+ ", ";
    query_text= query_text+params[n-1].getColName(DBCols)+")";
    query_text = query_text+ " values ("+
            "(select max(id)+1 from " + DBTables[tableName] +"), ";
   for (int i = 0; i< n-1; i++)
       query_text= query_text+params[i].getValue()+ ", ";
   query_text= query_text+params[n-1].getValue()+")";
   return query_text;
}



std::string QueryCreator::getName(Genre dbParam) const
{
    std::map<int, std::string> gn = GenreNames;
    return gn[dbParam];
}

