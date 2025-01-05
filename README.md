# AdvancedAlgoBot
A C++ stock market algorithmic trading bot

Calculates Technical indicators from stock market, will eventually make automatic buy/sell/hold decisions.

Libcurl: https://curl.haxx.se/docs/install.html

Jsoncpp: https://github.com/open-source-parsers/jsoncpp

(To run this on your machine.)

To compile and run:

Put all the files from this repo into one folder, and have the above mentioned dependencies installed.

Next, run this in your terminal:

g++ *.cpp -std=c++11 -ljsoncpp -lcurl -o exa.out && ./exa.out -I/usr/local/Cellar/boost/1.67.0_1/include/boost/
