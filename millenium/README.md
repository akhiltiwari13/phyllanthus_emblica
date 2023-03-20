# millenium notes:
Also, good news, Millennium wants you to take their C++ test, here is the link https://hr.gs/mlpbesdev


=========================================================
Market data related problem
There is stream of data is coming and we need to process the market data and build the book
Parsing of the stream
Need to read that data chunk by chunk and process it. Two types of messages are there one type has to ignored and one you need to process.
Only minor caveat the integers are in big Indian format. 
One integer is 64 but (8/8) in big Indian you wrote lower bytes first and higher bytes are stored afterwards. It is reverse in little Indian.
Bswap- need to use this function to read the integer properly .
Need to use pragmapack so read about it.

========================================================
Market data parser 
Stream of trade data and quote data
We need to parse the data by bytes and print with the format they have specified.
Ignore all trade data
Bswap64 bswap32 functions and pragma pack is required

========================================================