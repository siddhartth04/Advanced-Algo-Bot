#include "main.h"
int main()
{
        
        JSONdata minData, threadData, test;
        TechnicalAnalysis TIobj;

        Json::Value IEXdata = IEX::stocks::chartRange("aapl", "1d"); 
        minData.parseIEXdata(IEXdata); 

        while(1){
                
                std::thread t1(AcquireIEXdata, std::ref(threadData),std::move("aapl"), std::move("1d"));
                std::thread t2(&TechnicalAnalysis::calcRSI,TIobj,std::ref(minData));
                std::thread t3(&TechnicalAnalysis::calcFiftySMA,TIobj,std::ref(minData));
                std::thread t4(&TechnicalAnalysis::calcHundredSMA,TIobj,std::ref(minData));
                std::thread t5(&TechnicalAnalysis::calcHundFiftySMA,TIobj,std::ref(minData));
                std::thread t6(&TechnicalAnalysis::calcTwoHundSMA,TIobj,std::ref(minData));
                std::thread t7(&TechnicalAnalysis::calcFiftyEMA,TIobj,std::ref(minData));
                std::thread t8(&TechnicalAnalysis::calcHundredEMA,TIobj,std::ref(minData));
                std::thread t9(&TechnicalAnalysis::calcHundFiftyEMA,TIobj,std::ref(minData));
                std::thread t10(&TechnicalAnalysis::calcTwoHundEMA,TIobj,std::ref(minData));

                t1.join();
                t2.join(); 
                t3.join();
                t4.join();
                t5.join();
                t6.join();
                t7.join();
                t8.join();
                t9.join();
                t10.join();
                TIobj.clearTAobj();
                minData.clearJSONstruct();
                minData = threadData;
                test = threadData;
                threadData.clearJSONstruct();
        }

        return 0;
}

void AcquireIEXdata(JSONdata &dataToFormat, const std::string &stock, const std::string &range)
{
        assert(dataToFormat.isEmpty() && !range.empty() && !stock.empty());

        Json::Value IEXdata = IEX::stocks::chartRange(stock, range);
        dataToFormat.parseIEXdata(IEXdata);
}
