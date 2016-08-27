#include "LogManager.h"
#include "Uuid.h"
#include "NetWork.h"

namespace engine::tools{

    string LogManager::_levelName[]  = {
            "DEBUG",
            "INFO",
            "NOTICE",
            "WARN",
            "ERR",
            "CRIT",
            "ALERT",
            "EMERG"
        };

    map<string, string> LogManager::escapes;

    mutex LogManager::mtx;

    const bool LogManager::init(void)
    {
        if(!Object::init()){
            return false;
        }

        //初始化输出介质
        netOutPut = &UdpClient::create("192.168.1.255", 5432);
        netOutPut->retain();

        if(!netOutPut){
            Log.error("UdpClient Init Error");
        }
        return true;
    }

    void LogManager::setFilterLevel(const level _level)
    {
        _filter = _level;
    }

    void LogManager::_log(const level _level, const string & str) const
    {
        //输出打印信息
        printLog(_level, str);
    }

    bool LogManager::_format_D(stringstream & strs, const string & format, const string & source) const
    {
        static regex format_D("^[dD](\\d*)$");
        auto matchBegin = sregex_iterator(format.begin(), format.end(), format_D);
        auto matchEnd = sregex_iterator();
        if(matchBegin == matchEnd){
            return false;
        }
        
        int minCount = atoi(matchBegin->str(1).c_str());

        static regex checkNumber("^[+-]?(\\d+(\\.\\d+)?)(e\\+\\d+)?$|^[+-]?\\d{1,3}(,\\d{3})*(\\.(\\d{3},)*\\d{1,3})?(e\\+\\d+)?$");
        matchBegin = sregex_iterator(source.begin(), source.end(), checkNumber);

        if(matchBegin == matchEnd){
            error("格式化数据不匹配");
            strs << format;
            return true;
        }
        
        string sourceData = matchBegin->str();
        int convertData;
        
        for(auto index = sourceData.find(','); index != string::npos; index = sourceData.find(',')){
            sourceData.replace(sourceData.begin() + index, sourceData.begin() + index + 1, "");
        }

        if(sourceData.find('.') != string::npos){
            convertData = (int)roundf(atof(sourceData.c_str()));
        }else{
            convertData = atoi(sourceData.c_str());
        }

        stringstream tempSStr;
        tempSStr << convertData;

        for(int i = tempSStr.str().length(); i < minCount; ++i){
            strs << "0";
        }
        strs << convertData;

        return true;
    }

    bool LogManager::_format_C(stringstream & strs, const string & format, const string & source) const
    {
        static regex format_D("^[cC](\\d*)$");
        auto matchBegin = sregex_iterator(format.begin(), format.end(), format_D);
        auto matchEnd = sregex_iterator();
        if(matchBegin == matchEnd){
            return false;
        }

        int decimalDigits = 2;
        if(matchBegin->str(1).length() > 0){
            decimalDigits = atoi(matchBegin->str(1).c_str());
        }

        static regex checkNumber("^([^-+]?)([+-]?\\d+(\\.\\d+)?(e\\+\\d+)?)$|^([^-+]?)([+-]?\\d{1,3}(,\\d{3})*(\\.(\\d{3},)*\\d{1,3})?(e\\+\\d+)?)$");
        matchBegin = sregex_iterator(source.begin(), source.end(), checkNumber);

        if(matchBegin == matchEnd){
            error("尝试格式化失败");
            strs << format;
            return true;
        }

        string unit = matchBegin->str(1).length() > 0 ? matchBegin->str(1) : "￥";

        string sourceData = matchBegin->str(2);

        for(auto index = sourceData.find(','); index != string::npos; index = sourceData.find(',')){
            sourceData.replace(sourceData.begin() + index, sourceData.begin() + index + 1, "");
        }

        float convertData = roundf(atof(sourceData.c_str()) * pow(10, decimalDigits)) / pow(10, decimalDigits);

        stringstream tempSStr;
        tempSStr << convertData;

        //科学计数法转换
        string tempStr = scientificToDefault(tempSStr.str());
        strs << unit << tempStr;

        auto dotIndex = tempStr.find('.');
        if(dotIndex == string::npos){
            strs << ".";
            dotIndex = tempStr.length() - 1;
        }

        for(int i = tempStr.length() - dotIndex - 1; i < decimalDigits; ++i){
            strs << "0";
        }
                    
        return true;
    }

    bool LogManager::_format_F(stringstream & strs, const string & format, const string & source) const
    {
        static regex format_D("^[fF](\\d*)$");
        auto matchBegin = sregex_iterator(format.begin(), format.end(), format_D);
        auto matchEnd = sregex_iterator();
        if(matchBegin == matchEnd){
            return false;
        }

        int decimalDigits = 2;
        if(matchBegin->str(1).length() > 0){
            decimalDigits = atoi(matchBegin->str(1).c_str());
        }

        static regex checkNumber("^([+-]?\\d+(\\.\\d+)?)(e[\\+-]\\d+)?$|^[+-]?\\d{1,3}(,\\d{3})*(\\.(\\d{3},)*\\d{1,3})?(e[\\+-]\\d+)?$");
        matchBegin = sregex_iterator(source.begin(), source.end(), checkNumber);
        if(matchBegin == matchEnd){
            error("尝试格式化失败");
            strs << format;
            return true;
        }

        string sourceData = matchBegin->str();

        for(auto index = sourceData.find(','); index != string::npos; index = sourceData.find(',')){
            sourceData.replace(sourceData.begin() + index, sourceData.begin() + index + 1, "");
        }

        double convertData = round(atof(sourceData.c_str()) * pow(10, decimalDigits)) / pow(10, decimalDigits);

        stringstream tempSStr;
        tempSStr << convertData;

        //科学计数法转换
        string tempStr = scientificToDefault(tempSStr.str());
        strs << tempStr;

        auto dotIndex = tempStr.find('.');
        if(dotIndex == string::npos){
            strs << ".";
            dotIndex = tempStr.length() - 1;
        }

        for(int i = tempStr.length() - dotIndex - 1; i < decimalDigits; ++i){
            strs << "0";
        }
        return true;
    }

    bool LogManager::_format_aline(stringstream & strs, const string & format, const string & source) const
    {
        static regex format_D("^([-]?)(\\d*)$");
        auto matchBegin = sregex_iterator(format.begin(), format.end(), format_D);
        auto matchEnd = sregex_iterator();
        if(matchBegin == matchEnd){
            return false;
        }

        int minCount = atoi(matchBegin->str(2).c_str());

        if(matchBegin->str(1).c_str() == string("-")){
            for(int i = getStringLength(source); i < minCount; ++i){
                strs << " ";
            }
        }

        strs << source;

        if(matchBegin->str(1).c_str() != string("-")){
            for(int i = getStringLength(source); i < minCount; ++i){
                strs << " ";
            }
        }

        return true;
    }


    void LogManager::printLog(const level _level, const string & log) const
    {
        stringstream sstr;
        sstr << "[" << _levelName[_level] << "] " << log;
        //加线程锁锁
        unique_lock<mutex> lck(mtx, defer_lock);
        lck.lock();

        //有严重问题 暂时关闭网络发送功能
        // //输出到网络流
        // if(netOutPut){
        //     netOutPut->send(sstr.str());
        // }

        //输出到终端
        cout << sstr.str() << endl;
        lck.unlock();
    }

    string LogManager::scientificToDefault(const string & source) const
    {
        string result = source;
        //处理科学计数法
        auto scientificIndex = result.find("e+");
        if(scientificIndex != string::npos)
        {
            string baseNumber = result.substr(0, scientificIndex);
            int exponential = atoi(result.substr(scientificIndex + 2).c_str());
            auto dotIndex = baseNumber.find('.');
            baseNumber.replace(dotIndex, dotIndex + 1, "");
            while(baseNumber.length() < exponential + dotIndex){
                baseNumber += "0";
            }
            result = baseNumber;
        }

        scientificIndex = result.find("e-");
        if(scientificIndex != string::npos)
        {
            string baseNumber = result.substr(0, scientificIndex);
            int exponential = atoi(result.substr(scientificIndex + 2).c_str());
            auto dotIndex = baseNumber.find('.');
            baseNumber.replace(dotIndex, dotIndex + 1, "");

            string tempHead = "";
            while((int)tempHead.length() + 1 < exponential){
                tempHead += "0";
            }
            result = "0." + tempHead + baseNumber;
        }
        return result;
    }

    LogManager & Log = LogManager::create();
}
