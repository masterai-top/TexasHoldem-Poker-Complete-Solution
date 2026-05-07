#ifndef __ORDER_CREATE_H__
#define __ORDER_CREATE_H__
#include "../DBOperator.h"
#include "../GMServer.h"
#include <stdint.h>

class OrderCreateRequest
{
    friend class OrderCreateResponse;
public:
    OrderCreateRequest(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, orderType);
        SERIALIZE_MEMBER(writer, outOrderID);
        SERIALIZE_MEMBER(writer, amount);
        SERIALIZE_MEMBER(writer, fromAddr);
        SERIALIZE_MEMBER(writer, toAddr);
        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        try
        {
            Document d;
            if (d.Parse(json.c_str()).HasParseError())
            {
                throw logic_error("parse json error. raw data : " + json);
            }
            SET_DOC_MEMBER(d, orderType);
            SET_DOC_MEMBER(d, outOrderID);
            SET_DOC_MEMBER(d, amount);
            SET_DOC_MEMBER(d, fromAddr);
            SET_DOC_MEMBER(d, toAddr);
        }
        catch (const std::exception &e)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":OrderCreateRequest decode error!");
            throw logic_error(errInfo);
        }
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        return 0;
    }

    std::map<string, string> getMapInfo()
    {
        std::map<string, string> mInfo;
        mInfo.insert(std::make_pair("orderType", _orderType.toString()));
        mInfo.insert(std::make_pair("outOrderID", _outOrderID.toString()));
        mInfo.insert(std::make_pair("amount", _amount.toString()));
        mInfo.insert(std::make_pair("fromAddr", _fromAddr.toString()));
        mInfo.insert(std::make_pair("toAddr", _toAddr.toString()));
        return mInfo;
    }

private:
    CInteger       _orderType;
	CString        _outOrderID;
	CString        _amount;
	CString        _fromAddr;
	CString        _toAddr;
};

class OrderCreateResponse
{
public:
    OrderCreateResponse() {}
    OrderCreateResponse(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        writer.EndObject();
    }

    void toString(std::string &json)
    {
        StringBuffer sb;
        Writer<StringBuffer> writer(sb);
        Serialize(writer);
        json = sb.GetString();
    }

    void Deserialize(const string &json)
    {
        Document d;
        if (d.Parse(json.c_str()).HasParseError())
        {
            throw logic_error("parse json error. raw data : " + json);
        }
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        ROLLLOG_DEBUG << "reqBuf size: "<< reqBuf.size() << endl;
        string postData(reqBuf.begin(), reqBuf.end());

        GMRequest req;
        req.Deserialize(postData);

        std::string param = req.getParams();
        OrderCreateRequest request(param);

        std::map<string, string> mapOrderInfo = request.getMapInfo();

        // 返回结果是数组 == 业务处理,然后返回JSON
        int iRet = g_app.getOuterFactoryPtr()->getOrderServerPrx(0)->createOrder(mapOrderInfo);
        if(iRet != 0)
        {
            ROLLLOG_ERROR << "create order err. iRet :"<< iRet << endl;
            return -2;
        }

        encode(0, rspBuf);
        return 0;
    }

private:

    static void encode(int64_t resultCode, vector<tars::Char> &rspBuf)
    {
        // resultData是数组
        std::string resultData = "";
        int64_t totalItems = 1;  //总条数
        int64_t totalPages = 1;  //总页数
        GMResponse rsp(resultCode, "", resultData, totalItems, totalPages);
        std::string resultJson;
        rsp.toString(resultJson);
        rspBuf.assign(resultJson.begin(), resultJson.end());
    }
};
#endif
