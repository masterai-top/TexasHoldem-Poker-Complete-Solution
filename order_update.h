#ifndef __ORDER_UPDATE_H__
#define __ORDER_UPDATE_H__
#include "../DBOperator.h"
#include "../GMServer.h"
#include <stdint.h>

class OrderUpdateRequest
{
    friend class OrderUpdateResponse;
public:
    OrderUpdateRequest(const string &json)
    {
        this->Deserialize(json);
    }
    template <typename Writer>
    void Serialize(Writer &writer) const
    {
        writer.StartObject();
        SERIALIZE_MEMBER(writer, outOrderID);
        SERIALIZE_MEMBER(writer, updateInfo);
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

            SET_DOC_MEMBER(d, outOrderID);
            SET_DOC_MEMBER(d, updateInfo);
        }
        catch (const std::exception &e)
        {
            std::string errInfo = ::toString(__FILE__, ":", __LINE__, ":OrderUpdateRequest decode error!");
            throw logic_error(errInfo);
        }
    }

    static tars::Int32 handler(const vector<tars::Char> &reqBuf, const map<std::string, std::string> &extraInfo, vector<tars::Char> &rspBuf)
    {
        return 0;
    }

    std::map<string, string> getUpdateInfo()
    {
        std::map<string, string> mInfo;
        if (_updateInfo.isNull())
        {
            return mInfo;
        }
        std::vector<std::string> vecStr = split(_updateInfo.toString(), ";");
        for (auto &item : vecStr)
        {
            std::vector<std::string> infoTuple = split(item, ":");
            if(infoTuple.size() != 2)
            {
                continue;
            }
            mInfo.insert(std::make_pair(infoTuple[0], infoTuple[1]));
        }
        return mInfo;
    }

    std::map<string, string> getMapInfo()
    {
        std::map<string, string> mInfo;
        mInfo.insert(std::make_pair("outOrderID", _outOrderID.toString()));

        for(auto item : getUpdateInfo())
        {
            mInfo.insert(std::make_pair(item.first, item.second));
        }
        return mInfo;
    }

private:
    CString        _outOrderID;
    CString        _updateInfo;  //col:value;col:value
};

class OrderUpdateResponse
{
public:
    OrderUpdateResponse() {}
    OrderUpdateResponse(const string &json)
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
        OrderUpdateRequest request(param);

        std::map<string, string> mapOrderInfo = request.getMapInfo();

        // 返回结果是数组 == 业务处理,然后返回JSON
        int iRet = g_app.getOuterFactoryPtr()->getOrderServerPrx(0)->updateOrder(mapOrderInfo);
        if(iRet != 0)
        {
            ROLLLOG_ERROR << "update order err. iRet :"<< iRet << endl;
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
