all: sample

sample: sample.cpp
	g++ -o $@ $<  -lleveldb -lpthread -lsnappy   -L/home/ro/Downloads/lsm_nvm-master/out-shared -I/home/ro/Downloads/lsm_nvm-master/include 
clean:
	rm -f sample
