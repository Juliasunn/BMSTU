#ifndef DAL_GLOBAL_H
#define DAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DAL_LIBRARY)
#  define DAL_EXPORT Q_DECL_EXPORT
#else
#  define DAL_EXPORT Q_DECL_IMPORT
#endif

#define APP_CNF_PATH "../config/DAL_config"
#define DB_CNF_PATH "../config/conn_config_postgres"

#endif // DAL_GLOBAL_H
