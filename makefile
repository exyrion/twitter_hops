hops: twitter_hops.o
	g++ twitter_hops.o -o hops
twitter_hops.o: twitter_hops.cpp
	g++ twitter_hops.cpp -c