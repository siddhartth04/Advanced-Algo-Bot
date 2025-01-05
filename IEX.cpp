#include "IEX.h"

void IEX::parseSymbolData(const Json::Value &IEXdata, std::vector<std::string> &symbolVec)
{
    int i = 0;

    while(i < IEXdata.size()) {
        symbolVec.push_back(IEXdata[i]["symbol"].asString());
        i++;
    }
}

std::vector<std::string> IEX::getSymbolList()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    std::vector<std::string> symbolList;
    url += "/ref-data/symbols";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    parseSymbolData(jsonData, symbolList);
    return symbolList;

}

bool IEX::isValidSymbol(const std::string &symbol)
{
    std::vector<std::string> symbolList = getSymbolList();
    std::string symbolCopy = symbol;
    boost::to_upper(symbolCopy);
    if (std::find(symbolList.begin(), symbolList.end(), symbolCopy) != symbolList.end())
        return true;

    return false;
}
std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out)
{
    const std::size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}

void IEX::sendGetRequest(Json::Value &jsonData, const std::string url)
{
    CURL* curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    long int httpCode(0); 
    std::unique_ptr<std::string> httpData(new std::string());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    Json::Reader jsonReader;
    jsonReader.parse(*httpData, jsonData); //TODO error handle
}
Json::Value IEX::stocks::batch(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/batch";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::book(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/book";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::chart(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url+="/stock/"+symbol+"/chart";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::chartRange(const std::string &symbol, const std::string &range)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d") {
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/chart/"+range;
        IEX::sendGetRequest(jsonData, url);
    }
    else{
        std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
        exit(1);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::chartDate(const std::string &symbol, const std::string &date)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    if(date.size() == 8) {
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/chart/date/"+date;
        IEX::sendGetRequest(jsonData, url);

    }
    else{
        std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
        exit(1);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::chartDynamic(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/chart/dynamic";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}
Json::Value IEX::stocks::company(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/company";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::delayedQuote(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/delayed-quote";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::dividends(const std::string &symbol, const std::string &range)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m") {
        std::string url(IEX_ENDPOINT);
        url+="/stock/"+symbol+"/dividends/"+range;
        IEX::sendGetRequest(jsonData, url);
    }
    else{
        std::cout << std::endl << "Incorrect 'range' input in function dividends. Exiting." << std::endl;
        exit(1);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::earnings(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/earnings";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::effectiveSpread(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/effective-spread";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::financials(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/financials";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::stats(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/stats";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::largestTrades(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/largest-trades";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}
Json::Value IEX::stocks::list(const std::string &listType)
{
    Json::Value jsonData;
    if(listType == "mostactive" || listType == "gainers" || listType == "losers" || listType == "iexvolume" || listType == "iexmarketpercent") {
        std::string url(IEX_ENDPOINT);
        url+="/stock/market/list/"+listType;
        IEX::sendGetRequest(jsonData, url);
    }
    else{
        std::cout << std::endl << "Incorrect 'listType' input in function list(). I am returning an uninitialized JSON object!" << std::endl;
        return jsonData;
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::logo(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/logo";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::news(const std::string &symbol, int last)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    last == 0 ? url += "/stock/"+symbol+"/news" : url += "/stock/"+symbol+"/news/last/"+std::to_string(last);
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::OHLC(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/ohlc";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::peers(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/peers";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::previous(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/previous";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::price(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/price";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::quote(const std::string &symbol, bool displayPercent)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    displayPercent ? url += "/stock/"+symbol+"/quote?displayPercent=true" : url += "/stock/"+symbol+"/quote";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::relevant(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/relevant";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::sectorPerformance()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stock/market/sector-performance";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::splits(const std::string &symbol, const std::string &range)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);

    if(range == "5y" || range == "2y" || range == "1y" || range == "ytd" || range == "6m" || range == "3m" || range == "1m" || range == "1d") {
        url += "/stock/"+symbol+"/splits/"+range;
        IEX::sendGetRequest(jsonData, url);
    }
    else{
        std::cout << std::endl << "Incorrect 'range' input in function chartRange. Exiting." << std::endl;
        exit(1);
    }

    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stocks::timeSeries(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/time-series";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}
Json::Value IEX::stocks::VolumeByVenue(const std::string &symbol)
{
    Json::Value jsonData;

    if(!isValidSymbol(symbol)){
        std::cout << "Invalid Symbol! I am returning an uninitialized JSON object!";
        return jsonData;
    }

    std::string url(IEX_ENDPOINT);
    url += "/stock/"+symbol+"/volume-by-venue";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::refData::symbols()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/ref-data/symbols";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::refData::corporateActions(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);

    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/ref-data/daily-list/corporate-actions/"+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/ref-data/daily-list/corporate-actions";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::refData::dividends(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/ref-data/daily-list/dividends/"+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/ref-data/daily-list/dividends";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::refData::nextDayExDate(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/ref-data/daily-list/next-day-ex-date/"+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/ref-data/daily-list/next-day-ex-date";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::refData::symbolDirectory(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/ref-data/daily-list/symbol-directory/"+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/ref-data/daily-list/symbol-directory";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}
Json::Value IEX::stats::intraday()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stats/intraday";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

Json::Value IEX::stats::recent()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stats/recent";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /stats/records
 {
 "volume": {
 "recordValue": 233000477,
 "recordDate": "2016-01-20",
 "previousDayValue": 99594714,
 "avg30Value": 138634204.5
 },
 "symbolsTraded": {
 "recordValue": 6046,
 "recordDate": "2016-11-10",
 "previousDayValue": 5500,
 "avg30Value": 5617
 },
 "routedVolume": {
 "recordValue": 74855222,
 "recordDate": "2016-11-10",
 "previousDayValue": 29746476,
 "avg30Value": 44520084
 },
 "notional": {
 "recordValue": 9887832327.8355,
 "recordDate": "2016-11-10",
 "previousDayValue": 4175710684.3897,
 "avg30Value": 5771412969.2662
 }
 }*/
Json::Value IEX::stats::records()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stats/records";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /stats/historical?date=201605
 [
 {
 "averageDailyVolume": 112247378.5,
 "averageDailyRoutedVolume": 34282226.24,
 "averageMarketShare": 0,
 "averageOrderSize": 493,
 "averageFillSize": 287,
 "bin100Percent": 0.61559,
 "bin101Percent": 0.61559,
 "bin200Percent": 0.61559,
 "bin300Percent": 0.61559,
 "bin400Percent": 0.61559,
 "bin500Percent": 0.61559,
 "bin1000Percent": 0.61559,
 "bin5000Percent": 0.61559,
 "bin10000Percent": 0.61559,
 "bin10000Trades": 4666,
 "bin20000Trades": 1568,
 "bin50000Trades": 231,
 "uniqueSymbolsTraded": 7419,
 "blockPercent": 0.08159,
 "selfCrossPercent": 0.02993,
 "etfPercent": 0.12646,
 "largeCapPercent": 0.40685,
 "midCapPercent": 0.2806,
 "smallCapPercent": 0.18609,
 "venueARCXFirstWaveWeight": 0.22063,
 "venueBATSFirstWaveWeight": 0.06249,
 "venueBATYFirstWaveWeight": 0.07361,
 "venueEDGAFirstWaveWeight": 0.01083,
 "venueEDGXFirstWaveWeight": 0.0869,
 "venueOverallFirstWaveWeight": 1,
 "venueXASEFirstWaveWeight": 0.00321,
 "venueXBOSFirstWaveWeight": 0.02935,
 "venueXCHIFirstWaveWeight": 0.00108,
 "venueXCISFirstWaveWeight": 0.00008,
 "venueXNGSFirstWaveWeight": 0.20358,
 "venueXNYSFirstWaveWeight": 0.29313,
 "venueXPHLFirstWaveWeight": 0.01511,
 "venueARCXFirstWaveRate": 0.97737,
 "venueBATSFirstWaveRate": 0.99357,
 "venueBATYFirstWaveRate": 0.99189,
 "venueEDGAFirstWaveRate": 0.98314,
 "venueEDGXFirstWaveRate": 0.99334,
 "venueOverallFirstWaveRate": 0.98171,
 "venueXASEFirstWaveRate": 0.94479,
 "venueXBOSFirstWaveRate": 0.97829,
 "venueXCHIFirstWaveRate": 0.65811,
 "venueXCISFirstWaveRate": 0.9468,
 "venueXNGSFirstWaveRate": 0.98174,
 "venueXNYSFirstWaveRate": 0.98068,
 "venueXPHLFirstWaveRate": 0.93629
 }
 ]*/
Json::Value IEX::stats::historical(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/stats/historical/"+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/stats/historical/";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /stats/historical/daily?last=5
 [
 {
 "date": "2017-05-09",
 "volume": 152907569,
 "routedVolume": 46943802,
 "marketShare": 0.02246,
 "isHalfday": 0,
 "litVolume": 35426666
 },
 {
 "date": "2017-05-08",
 "volume": 142923030,
 "routedVolume": 39507295,
 "marketShare": 0.02254,
 "isHalfday": 0,
 "litVolume": 32404585
 },
 {
 "date": "2017-05-05",
 "volume": 155118117,
 "routedVolume": 39974788,
 "marketShare": 0.02358,
 "isHalfday": 0,
 "litVolume": 35124994
 },
 {
 "date": "2017-05-04",
 "volume": 185715463,
 "routedVolume": 56264408,
 "marketShare": 0.02352,
 "isHalfday": 0,
 "litVolume": 40634976
 },
 {
 "date": "2017-05-03",
 "volume": 183103198,
 "routedVolume": 50953175,
 "marketShare": 0.025009999999999998,
 "isHalfday": 0,
 "litVolume": 40296158
 }
 ]
 EITHER TAKES JUST A SYMBOL, OR SYMBOL AND DATE, OR SYMBOL AND LAST X (UP TO 90)*/
Json::Value IEX::stats::historicalDaily(std::string date)
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    std::locale loc; //For isdigit
    if(!date.empty()) {
        if(date.size() == 8) {
            url += "/stats/historical/daily?date="+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else if(isdigit(date[0],loc)) {
            url += "/stats/historical/daily?last="+date;
            IEX::sendGetRequest(jsonData, url);
        }
        else{
            std::cout << std::endl << "Incorrect 'date' input in function chartDate. Exiting." << std::endl;
            exit(1);
        }
    }

    else{
        url += "/stats/historical/daily";
        IEX::sendGetRequest(jsonData, url);
    }
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /market
 [
 {
 "mic": "TRF",
 "tapeId": "-",
 "venueName": "TRF Volume",
 "volume": 589171705,
 "tapeA": 305187928,
 "tapeB": 119650027,
 "tapeC": 164333750,
 "marketPercent": 0.37027,
 "lastUpdated": 1480433817317
 },
 {
 "mic": "XNGS",
 "tapeId": "Q",
 "venueName": "NASDAQ",
 "volume": 213908393,
 "tapeA": 90791123,
 "tapeB": 30731818,
 "tapeC": 92385452,
 "marketPercent": 0.13443,
 "lastUpdated": 1480433817311
 },
 {
 "mic": "XNYS",
 "tapeId": "N",
 "venueName": "NYSE",
 "volume": 204280163,
 "tapeA": 204280163,
 "tapeB": 0,
 "tapeC": 0,
 "marketPercent": 0.12838,
 "lastUpdated": 1480433817336
 },
 {
 "mic": "ARCX",
 "tapeId": "P",
 "venueName": "NYSE Arca",
 "volume": 180301371,
 "tapeA": 64642458,
 "tapeB": 78727208,
 "tapeC": 36931705,
 "marketPercent": 0.11331,
 "lastUpdated": 1480433817305
 },
 {
 "mic": "EDGX",
 "tapeId": "K",
 "venueName": "EDGX",
 "volume": 137022822,
 "tapeA": 58735505,
 "tapeB": 32753903,
 "tapeC": 45533414,
 "marketPercent": 0.08611,
 "lastUpdated": 1480433817310
 },
 {
 "mic": "BATS",
 "tapeId": "Z",
 "venueName": "BATS BZX",
 "volume": 100403461,
 "tapeA": 52509859,
 "tapeB": 25798360,
 "tapeC": 22095242,
 "marketPercent": 0.0631,
 "lastUpdated": 1480433817311
 },
 {
 "mic": "BATY",
 "tapeId": "Y",
 "venueName": "BATS BYX",
 "volume": 54413196,
 "tapeA": 28539960,
 "tapeB": 13638779,
 "tapeC": 12234457,
 "marketPercent": 0.03419,
 "lastUpdated": 1480433817310
 },
 {
 "mic": "XBOS",
 "tapeId": "B",
 "venueName": "NASDAQ BX",
 "volume": 31417461,
 "tapeA": 16673166,
 "tapeB": 5875538,
 "tapeC": 8868757,
 "marketPercent": 0.01974,
 "lastUpdated": 1480433817311
 },
 {
 "mic": "EDGA",
 "tapeId": "J",
 "venueName": "EDGA",
 "volume": 30670687,
 "tapeA": 15223428,
 "tapeB": 8276375,
 "tapeC": 7170884,
 "marketPercent": 0.01927,
 "lastUpdated": 1480433817311
 },
 {
 "mic": "IEXG",
 "tapeId": "V",
 "venueName": "IEX",
 "volume": 26907838,
 "tapeA": 16578501,
 "tapeB": 3889245,
 "tapeC": 6440092,
 "marketPercent": 0.01691,
 "lastUpdated": 1480433817235
 },
 {
 "mic": "XPHL",
 "tapeId": "X",
 "venueName": "NASDAQ PSX",
 "volume": 13334403,
 "tapeA": 5802294,
 "tapeB": 4239741,
 "tapeC": 3292368,
 "marketPercent": 0.00838,
 "lastUpdated": 1480433817071
 },
 {
 "mic": "XCHI",
 "tapeId": "M",
 "venueName": "CHX",
 "volume": 4719854,
 "tapeA": 834762,
 "tapeB": 3168434,
 "tapeC": 716658,
 "marketPercent": 0.00296,
 "lastUpdated": 1480433814711
 },
 {
 "mic": "XASE",
 "tapeId": "A",
 "venueName": "NYSE MKT",
 "volume": 4419196,
 "tapeA": 0,
 "tapeB": 4419196,
 "tapeC": 0,
 "marketPercent": 0.00277,
 "lastUpdated": 1480433816276
 },
 {
 "mic": "XCIS",
 "tapeId": "C",
 "venueName": "NSX",
 "volume": 187785,
 "tapeA": 39923,
 "tapeB": 62191,
 "tapeC": 85671,
 "marketPercent": 0.00011,
 "lastUpdated": 1480433816141
 }
 ]*/
Json::Value IEX::markets::market()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/market";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

//GET /stock/market/crypto
Json::Value IEX::stocks::crypto()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stock/market/crypto";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /stock/market/today-earnings
 {
 "bto": [
 {
 "actualEPS": 2.1,
 "consensusEPS": 2.02,
 "estimatedEPS": 2.02,
 "announceTime": "BTO",
 "numberOfEstimates": 14,
 "EPSSurpriseDollar": 0.08,
 "EPSReportDate": "2017-05-02",
 "fiscalPeriod": "Q2 2017",
 "fiscalEndDate": "2017-03-31",
 "yearAgo": 1.67,
 "yearAgoChangePercent": .30,
 "estimatedChangePercent": .28,
 "symbolId": 11,
 "symbol": "AAPL",
 "quote": {
 ...
 },
 "headline": ""
 },
 ...
 ],
 "amc": [
 {
 "actualEPS": 3.36,
 "consensusEPS": 3.22,
 "estimatedEPS": 3.22,
 "announceTime": "AMC",
 "numberOfEstimates": 15,
 "EPSSurpriseDollar": 0.14,
 "EPSReportDate": "2017-05-02",
 "fiscalPeriod": "Q2 2017",
 "fiscalEndDate": "2017-03-31",
 "yearAgo": 1.67,
 "yearAgoChangePercent": .30,
 "estimatedChangePercent": .28,
 "symbolId": 1,
 "symbol": "A",
 "quote": {
 ...
 },
 "headline": ""
 },
 ...
 ]
 }*/
Json::Value IEX::stocks::earningsToday()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stock/market/today-earnings";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}

/*
 GET /stock/market/upcoming-ipos
 The above example will return JSON with the following keys
 {
 "rawData": [
 {
 "symbol": "VCNX",
 "companyName": "VACCINEX, INC.",
 "expectedDate": "2018-08-09",
 "leadUnderwriters": [
 "BTIG, LLC",
 "Oppenheimer & Co. Inc."
 ],
 "underwriters": [
 "Ladenburg Thalmann & Co. Inc."
 ],
 "companyCounsel": [
 "Hogan Lovells US LLP and Harter Secrest & Emery LLP"
 ],
 "underwriterCounsel": [
 "Mintz, Levin, Cohn, Ferris, Glovsky and Popeo, P.C."
 ],
 "auditor": "Computershare Trust Company, N.A",
 "market": "NASDAQ Global",
 "cik": "0001205922",
 "address": "1895 MOUNT HOPE AVE",
 "city": "ROCHESTER",
 "state": "NY",
 "zip": "14620",
 "phone": "585-271-2700",
 "ceo": "Maurice Zauderer",
 "employees": 44,
 "url": "www.vaccinex.com",
 "status": "Filed",
 "sharesOffered": 3333000,
 "priceLow": 12,
 "priceHigh": 15,
 "offerAmount": null,
 "totalExpenses": 2400000,
 "sharesOverAlloted": 499950,
 "shareholderShares": null,
 "sharesOutstanding": 11474715,
 "lockupPeriodExpiration": "",
 "quietPeriodExpiration": "",
 "revenue": 206000,
 "netIncome": -7862000,
 "totalAssets": 4946000,
 "totalLiabilities": 6544000,
 "stockholderEquity": -133279000,
 "companyDescription": "",
 "businessDescription": "",
 "useOfProceeds": "",
 "competition": "",
 "amount": 44995500,
 "percentOffered": "29.05"
 },
 ...
 ],
 "viewData": [
 {
 "Company": "VACCINEX, INC.",
 "Symbol": "VCNX",
 "Price": "$12.00 - 15.00",
 "Shares": "3,333,000",
 "Amount": "44,995,500",
 "Float": "11,474,715",
 "Percent": "29.05%",
 "Market": "NASDAQ Global",
 "Expected": "2018-08-09"
 },
 ...
 ]
 }*/
Json::Value IEX::stocks::upcomingIPOS()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stock/market/upcoming-ipos";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}


/*
 GET /stock/market/today-ipos
 The above example will return JSON with the following keys
 {
 "rawData": [
 {
 "symbol": "VCNX",
 "companyName": "VACCINEX, INC.",
 "expectedDate": "2018-08-09",
 "leadUnderwriters": [
 "BTIG, LLC",
 "Oppenheimer & Co. Inc."
 ],
 "underwriters": [
 "Ladenburg Thalmann & Co. Inc."
 ],
 "companyCounsel": [
 "Hogan Lovells US LLP and Harter Secrest & Emery LLP"
 ],
 "underwriterCounsel": [
 "Mintz, Levin, Cohn, Ferris, Glovsky and Popeo, P.C."
 ],
 "auditor": "Computershare Trust Company, N.A",
 "market": "NASDAQ Global",
 "cik": "0001205922",
 "address": "1895 MOUNT HOPE AVE",
 "city": "ROCHESTER",
 "state": "NY",
 "zip": "14620",
 "phone": "585-271-2700",
 "ceo": "Maurice Zauderer",
 "employees": 44,
 "url": "www.vaccinex.com",
 "status": "Filed",
 "sharesOffered": 3333000,
 "priceLow": 12,
 "priceHigh": 15,
 "offerAmount": null,
 "totalExpenses": 2400000,
 "sharesOverAlloted": 499950,
 "shareholderShares": null,
 "sharesOutstanding": 11474715,
 "lockupPeriodExpiration": "",
 "quietPeriodExpiration": "",
 "revenue": 206000,
 "netIncome": -7862000,
 "totalAssets": 4946000,
 "totalLiabilities": 6544000,
 "stockholderEquity": -133279000,
 "companyDescription": "",
 "businessDescription": "",
 "useOfProceeds": "",
 "competition": "",
 "amount": 44995500,
 "percentOffered": "29.05"
 },
 ...
 ],
 "viewData": [
 {
 "Company": "VACCINEX, INC.",
 "Symbol": "VCNX",
 "Price": "$12.00 - 15.00",
 "Shares": "3,333,000",
 "Amount": "44,995,500",
 "Float": "11,474,715",
 "Percent": "29.05%",
 "Market": "NASDAQ Global",
 "Expected": "2018-08-09"
 },
 ...
 ]
 }*/
Json::Value IEX::stocks::todayIPOS()
{
    Json::Value jsonData;
    std::string url(IEX_ENDPOINT);
    url += "/stock/market/today-ipos";
    IEX::sendGetRequest(jsonData, url);
    assert(jsonData.isArray()); //Crash if not an array
    return jsonData;
}
