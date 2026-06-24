#include "DBOperator.h"
#include "globe.h"
#include "LogComm.h"

//
using namespace std;

/**
 *
*/
CDBOperator::CDBOperator()
{

}

/**
 *
*/
CDBOperator::~CDBOperator()
{

}

//初始化
int CDBOperator::init()
{
    FUNC_ENTRY("");

    readDBConfig(); //数据源配置

    int iRet = 0;
    try
    {
        map<string, string> mpParam;
        mpParam["dbhost"] = dbConf.Host;
        mpParam["dbuser"] = dbConf.user;
        mpParam["dbpass"] = dbConf.password;
        mpParam["dbname"] = dbConf.dbname;
        mpParam["charset"] = dbConf.charset;
        mpParam["dbport"] = dbConf.port;

        TC_DBConf dbConf;
        dbConf.loadFromMap(mpParam);

        //初始化数据库连接
        m_mysqlObj.init(dbConf);
    }
    catch (exception &e)
    {
        iRet = -1;
        ROLLLOG_ERROR << "Catch exception: " << e.what() << endl;
    }
    catch (...)
    {
        iRet = -2;
        ROLLLOG_ERROR << "Catch unknown exception." << endl;
    }

    FUNC_EXIT("", iRet);
    return iRet;
}

int CDBOperator::init(const std::string &dbhost, const std::string &dbuser, const std::string &dbpass, const std::string &dbname, const std::string &charset, const std::string &dbport)
{
    return 0;
}

//数据源配置
void CDBOperator::readDBConfig()
{
    FUNC_ENTRY("");

    try
    {
        //本地配置文件
        _pFileConf = new tars::TC_Config();
        if (!_pFileConf)
        {
            ROLLLOG_ERROR << "create config parser fail, ptr null." << endl;
            terminate();
        }

        //
        _pFileConf->parseFile(ServerConfig::BasePath + ServerConfig::ServerName + ".conf");
        LOG_DEBUG << "init config file succ, base path: " << ServerConfig::BasePath + ServerConfig::ServerName + ".conf" << endl;

        //
        dbConf.Domain = (*_pFileConf).get("/Main/db<domain>", "");
        dbConf.Host = (*_pFileConf).get("/Main/db<host>", "0");
        dbConf.port = (*_pFileConf).get("/Main/db<port>", "0");
        dbConf.user = (*_pFileConf).get("/Main/db<user>", "0");
        dbConf.password = (*_pFileConf).get("/Main/db<password>", "0");
        dbConf.charset = (*_pFileConf).get("/Main/db<charset>", "0");
        dbConf.dbname = (*_pFileConf).get("/Main/db<dbname>", "0");
        if (dbConf.Domain.length() > 0)
        {
            string szHost = getIpStr(dbConf.Domain);
            if (szHost.length() > 0)
            {
                dbConf.Host = szHost;
                ROLLLOG_DEBUG << "get host by domain, Domain: " << dbConf.Domain << ", szHost: " << szHost << endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        EXPLOG(string("catch std exception: ") + e.what());
    }

    delete _pFileConf;

    _pFileConf = nullptr;

    FUNC_EXIT("", 0);
}

//查询数据库
std::vector<std::map<std::string, std::string>> CDBOperator::query(const std::string &strSQL)
{
    FUNC_ENTRY("");
    vector<map<string, string>> result;

    try
    {
        ROLLLOG_DEBUG << "sql: " << strSQL << endl;

        TC_Mysql::MysqlData res = m_mysqlObj.queryRecord(strSQL);
        ROLLLOG_DEBUG << "Execute SQL: [" << strSQL << "], return " << res.size() << " records." << endl;
        if (res.size() <= 0)
        {
            ROLLLOG_WARN << " no data." << endl;
            return result;
        }

        result = res.data();
    }
    catch (const std::exception &e)
    {
        EXPLOG(string("catch std exception: ") + e.what());
    }

    FUNC_EXIT("", 0);
    return result;
}

