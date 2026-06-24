#ifndef _DB_OPERATOR_H_
#define _DB_OPERATOR_H_

#include <util/tc_mysql.h>
#include <util/tc_singleton.h>
#include <util/tc_config.h>
#include <string>
#include <map>

//数据源配置
typedef struct _TDBConf
{
    string Domain;        //域名
    string Host;          //主机
    string port;          //端口
    string user;          //用户名
    string password;      //密码
    string charset;       //编码格式
    string dbname;        //数据库
} DBConf;


class CDBOperator
{
public:
    /**
    *
    */
    CDBOperator();

    /**
    *
    */
    ~CDBOperator();

public:
    /**
    * 初始化
    */
    int init(const std::string &dbhost, const std::string &dbuser, const std::string &dbpass,
             const std::string &dbname, const std::string &charset, const std::string &dbport);

    /**
     * [init description]
     * @return [description]
     */
    int init();

public:
    /**
     * 数据源配置
     */
    void readDBConfig();

    /**
     *  查询数据库
     */
    std::vector<std::map<std::string, std::string>> query(const std::string &strSQL);

private:
    //mysql操作对象
    tars::TC_Mysql m_mysqlObj;
    //数据源配置
    DBConf dbConf;
    //服务配置
    tars::TC_Config *_pFileConf;
};

//singleton
typedef tars::TC_Singleton<CDBOperator, tars::CreateStatic, tars::DefaultLifetime> DBOperatorSingleton;

#endif
