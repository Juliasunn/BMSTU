#include "include/accessordb.h"


void AccessorDB::setCon(const std::shared_ptr<Connector> &value)
{
    Logger::DebugMsg("AccessorDB::setCon");
    con = value;
    try {
        con->openConnection();
    } catch (db_exception &e) {
        Logger::ErrorMsg(e.what());
    }
}

void AccessorDB::setQCreator(const std::shared_ptr<QueryCreator> &value)
{
    qCreator = value;
}

User AccessorDB::getUser(int id)
{
    std::vector<QueryParam> params;
    params.push_back(QueryParam(U_ID, id));

    std::vector<Column> vals = {U_ID, U_LOGIN, U_PASSWORD, U_LEVEL};

    std::string queryText = qCreator->createSelectQuery(USER_T, vals, params);
    Logger::DebugMsg(queryText.c_str());
    User u;
    try {
       u = (con->execSelectUsers(queryText)).at(0);
    } catch (db_exception &e) {
        Logger::ErrorMsg(e.what());
    }
    return u;
}

User AccessorDB::getUser(const std::string &login, const std::string &password)
{
    pChecker->checkParams(std::vector<std::string>{login, password});

    if (!checkUserExists(login, password))
        throw user_not_exists_exception();

    std::vector<QueryParam> params;
    params.push_back(QueryParam(U_LOGIN, login));
    params.push_back(QueryParam(U_PASSWORD, password));

    std::vector<Column> vals = {U_ID, U_LOGIN, U_PASSWORD, U_LEVEL};

    std::string queryText = qCreator->createSelectQuery(USER_T, vals, params);
    Logger::DebugMsg(queryText.c_str());
    User u;
    try {
       u = (con->execSelectUsers(queryText)).at(0);
    } catch (db_exception &e) {
        Logger::ErrorMsg(e.what());
    }
    return u;
}

bool AccessorDB::addUser(const std::string &login, const std::string &password)
{
    pChecker->checkParams(std::vector<std::string>{login, password});

    if (checkUserExists(login, password))
        throw user_already_exists_exception();

    std::vector<QueryParam> params;
    params.push_back(QueryParam(U_LOGIN, login));
    params.push_back(QueryParam(U_PASSWORD, password));
    params.push_back(QueryParam(U_LEVEL, 1));

    std::string queryText = qCreator->createInsertQuery(USER_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
       con->execNoReturnQuery(queryText);

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
       return false;
    }
    return true;
}

bool AccessorDB::checkUserExists(const std::string &login, const std::string &password)
{
    pChecker->checkParams(std::vector<std::string>{login, password});

    std::vector<QueryParam> params, vals;
    params.push_back(QueryParam(U_LOGIN, login));
    params.push_back(QueryParam(U_PASSWORD, password));

    std::string queryText = qCreator->createCountQuery(USER_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
        if ((con->execCountQuery(queryText))>0)
            return true;

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return false;
}

bool AccessorDB::changeUserPassword(int id_user, const std::string &new_password)
{
    pChecker->checkParams(std::vector<std::string>{new_password});

    bool result;
    Logger::DebugMsg("AccessorDB::changeUserPassword()");

    std::vector<QueryParam> params, vals;
    params.push_back(QueryParam(U_ID, id_user));
    vals.push_back(QueryParam(U_PASSWORD, new_password));
    std::string queryText = qCreator->createUpdateQuery(USER_T, vals, params);

    Logger::DebugMsg(queryText.c_str());
    try {
       result = (con->execNoReturnQuery(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
       result = false;
    }
    return result;
}

bool AccessorDB::checkLoginFree(const std::string &login)
{
    pChecker->checkParams(std::vector<std::string>{login});

    std::vector<QueryParam> params, vals;
    params.push_back(QueryParam(U_LOGIN, login));

    std::string queryText = qCreator->createCountQuery(USER_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
        if ((con->execCountQuery(queryText))==0)
            return true;

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return false;
}

std::vector<Track> AccessorDB::getTracks()
{
    qDebug()<< "AccessorDB::getTracks()";
    Logger::DebugMsg("AccessorDB::getTracks()");
    std::vector<QueryParam> params;
    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};
    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params);
    Logger::DebugMsg(queryText.c_str());

    std::vector<Track> t;
    try {
       t = (con->execSelectTracks(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return t;
}

Track AccessorDB::getTrack(int id)
{

    std::vector<QueryParam> params;
    params.push_back(QueryParam(T_ID, id));

    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};

    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params);
    Logger::DebugMsg(queryText.c_str());

    Track t;
    try {
       t = (con->execSelectTracks(queryText)).at(0);
    } catch (...) {
        throw no_result_exception();
    }
    return t;
}

Track AccessorDB::getTrack(const std::string &uuid)
{
    pChecker->checkParams(std::vector<std::string>{uuid});

    std::vector<QueryParam> params;
    params.push_back(QueryParam(T_UUID, uuid));

    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};

    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params);
    Logger::DebugMsg(queryText.c_str());

    Track t;
    try {
       t = (con->execSelectTracks(queryText)).at(0);
    } catch (...) {
        throw no_result_exception();
    }
    return t;
}

std::vector<Track> AccessorDB::getTracks(const std::string name_tr)
{
    pChecker->checkParams(std::vector<std::string>{name_tr});

    std::vector<QueryParam> params;
    params.push_back(QueryParam(T_NAME, name_tr));

    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};

    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params);
    Logger::DebugMsg(queryText.c_str());

    std::vector<Track> t;
    try {
       t = (con->execSelectTracks(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return t;
}

std::vector<Track> AccessorDB::getSortedTracks(Column sort_field)
{
    std::vector<QueryParam> params;
    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};
    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params, sort_field);
    Logger::DebugMsg(queryText.c_str());

    std::vector<Track> t;
    try {
       t = (con->execSelectTracks(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return t;
}

std::vector<Track> AccessorDB::getFilteredTracks(Genre g)
{
    std::vector<QueryParam> params;
    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};

    params.push_back(QueryParam(T_GENRE, qCreator->getName(g)));

    std::string queryText = qCreator->createSelectQuery(TRACK_T, vals, params);
    Logger::DebugMsg(queryText.c_str());

    std::vector<Track> t;
    try {
       t = (con->execSelectTracks(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return t;
}

std::vector<Listening> AccessorDB::getListeningsTrack(int id_track)
{
    std::vector<QueryParam> params;
    std::vector<Column> vals = {L_ID, L_TRACK, L_USER};
    params.push_back(QueryParam(L_TRACK, id_track));

    std::string queryText = qCreator->createSelectQuery(LISTEN_T, vals, params);
    std::vector<Listening> l;

    try {
       l = (con->execSelectListenings(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }

    return l;
}

int AccessorDB::counListenings(int id_track)
{
    std::vector<QueryParam> params;
    params.push_back(QueryParam(L_TRACK, id_track));

    std::string queryText = qCreator->createCountQuery(LISTEN_T, params);
    int num=0;

    try {
       num = (con->execCountQuery(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return num;
}

std::vector<Listening> AccessorDB::getListeningsUser(int id_user)
{
    std::vector<QueryParam> params;
    std::vector<Column> vals = {L_ID, L_TRACK, L_USER};
    params.push_back(QueryParam(L_USER, id_user));

    std::string queryText = qCreator->createSelectQuery(LISTEN_T, vals, params);
    std::vector<Listening> l;

    try {
       l = (con->execSelectListenings(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }

    return l;
}

bool AccessorDB::addListening(int id_user, int id_track)
{
    std::vector<QueryParam> params;
    params.push_back(QueryParam(L_USER, std::to_string(id_user)));
    params.push_back(QueryParam(L_TRACK, std::to_string(id_track)));

    std::string queryText = qCreator->createInsertQuery(LISTEN_T, params);
    try {
       con->execNoReturnQuery(queryText);

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
       return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Track> AccessorDB::getUserTracks(int id_user)
{
    Logger::DebugMsg("AccessorDB::getAddedTracks()");

    std::vector<QueryParam> select_params;
    select_params.push_back(QueryParam(UT_USER, std::to_string(id_user)));

    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};
    std::vector<Column> join_vals = {UT_TRACK, T_ID}; //столбцы по которым соединяем

    std::vector<Table> tables = {UT_T, TRACK_T}; //таблицы которые соединяем

    std::string queryText = qCreator->createJoinQuery(tables, join_vals, vals, select_params);
    Logger::DebugMsg(queryText.c_str());

    std::vector<Track> t;
    try {
       t = (con->execSelectTracks(queryText));
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return t;
}

bool AccessorDB::addTrack(int id_track, int id_user)
{
    std::vector<QueryParam> params;
    params.push_back(QueryParam(UT_USER, std::to_string(id_user)));
    params.push_back(QueryParam(UT_TRACK, std::to_string(id_track)));

    std::string queryText = qCreator->createInsertQuery(UT_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
       con->execNoReturnQuery(queryText);

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
       return false;
    }


    return true;
}

bool AccessorDB::isTrackAdded(int id_track, int id_user)
{
    std::vector<QueryParam> params, vals;
    params.push_back(QueryParam(UT_USER, std::to_string(id_user)));
    params.push_back(QueryParam(UT_TRACK, std::to_string(id_track)));

    std::string queryText = qCreator->createCountQuery(UT_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
        if ((con->execCountQuery(queryText))>0)
            return true;

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    return false;
}

bool AccessorDB::deleteUserTrack(int id_track, int id_user)
{
    std::vector<QueryParam> params;
    params.push_back(QueryParam(UT_USER, std::to_string(id_user)));
    params.push_back(QueryParam(UT_TRACK, std::to_string(id_track)));

    std::string queryText = qCreator->createDeleteQuery(UT_T, params);
    Logger::DebugMsg(queryText.c_str());

    try {
       con->execNoReturnQuery(queryText);

    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
       return false;
    }
    return true;
}

Track AccessorDB::getUserTrack(const std::string &uuid, int id_user)
{
    pChecker->checkParams(std::vector<std::string>{uuid});
    Logger::DebugMsg("AccessorDB::getUserTrack()");


    std::vector<QueryParam> select_params;
    select_params.push_back(QueryParam(UT_USER, std::to_string(id_user)));
    select_params.push_back(QueryParam(T_UUID, uuid));

    std::vector<Table> tables = {UT_T, TRACK_T}; //таблицы которые соединяем
    std::vector<Column> join_vals = {UT_TRACK, T_ID}; //столбцы по которым соединяем

    std::vector<Column> vals = {T_ID, T_NAME, T_GENRE, T_ARTIST, T_FILE, T_UUID};

    std::string queryText = qCreator->createJoinQuery(tables, join_vals, vals, select_params);
    Logger::DebugMsg(queryText.c_str());

    Track t;
    try {
       t = (con->execSelectTracks(queryText)).at(0);
    } catch (db_exception &e) {
       Logger::ErrorMsg(e.what());
    }
    catch (...) {
        throw no_result_exception();
    }
    return t;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


std::shared_ptr<AccessorDB> AccessorDBCreator::get_accessor(std::string connect_cnf_file, std::string app_cnf_file)
{
    qDebug() << "SEEMS LIKE I AM INCLUDING ANOTHR PROJECT";
    if (db==nullptr)
    {
        try
        {
            ConnInfo conn_cnf = ConnInfo(connect_cnf_file);
            DalConfig app_cnf = DalConfig(app_cnf_file);

              std::shared_ptr<QueryCreator> qCreator;
              int subd = app_cnf.getSubd();

              switch (subd)
              {
              case(POSTGRES_SUBD):
                  qCreator = std::shared_ptr<QueryCreator>(new PostgreQueryCreator());
                  break;
              case(SQLITE_SUBD):
                 qCreator = std::shared_ptr<QueryCreator>(new SQLiteQueryCreator());
                   break;
              default:
                  Logger::ErrorMsg("no such SUBD type: "+std::to_string(app_cnf.getSubd()));
                  throw confile_exception();

              }
              std::shared_ptr<Connector> con;

              switch (app_cnf.getDbFramework())
              {
              case(FRAMEWORK_QT):
                  con = std::shared_ptr<Connector> (new QConnector(conn_cnf, subd));
                  break;
              default:
                  Logger::ErrorMsg("no such Framework type: "+std::to_string(app_cnf.getDbFramework()));
                  throw confile_exception();
                  break;
              }

              db = std::shared_ptr<AccessorDB>(new AccessorDB(con, qCreator, app_cnf.getChecker()));
        }
        catch(confile_exception &e)
       {
            Logger::ErrorMsg(e.what());
       }
    }
    return db;
}
