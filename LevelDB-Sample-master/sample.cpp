#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "leveldb/db.h"

using namespace std;

int main(int argc, char** argv)
{
    // Set up database connection information and open database
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    //Array of Skip Lists
    vector<vector<vector<std::string>>> skipArray;

    leveldb::Status status = leveldb::DB::Open(options,"./test3db", "file1",&db);

    if (false == status.ok())
    {
        cerr << "Unable to open/create test database './test3db'" << endl;
        cerr << status.ToString() << endl;
        return -1;
    }
    


    // Add 256 values to the database
    leveldb::WriteOptions writeOptions;
    /*
    for (unsigned int i = 0; i < 4; ++i)
    {
        ostringstream keyStream;
        keyStream << "Key" << i;
        
        ostringstream valueStream;
        valueStream << "Test data value: " << i;
        
        db->Put(writeOptions, keyStream.str(), valueStream.str());
    }
     */
    std::string keyStream;
    std::string valueStream;
    //Array of Key & Value Pairs for 1 SKip List
    vector<vector<std::string>> skipList;
    //Array of 1 Key & Value Pair
    vector<std::string> skipPair;
    cout << "creating skip list array" << endl;
    for (unsigned int i = 0; i < 1; ++i)
        {
    	//cout << "i=" << i <<endl;
    	for (int j = 0; j<100; ++j)
    		{

    					//cout << "jKey=" << j <<endl;
    					keyStream = "Key" +  std::to_string(j);
    					//cout << keyStream << endl;
    					skipPair.push_back(keyStream);

    					//cout << "jValue=" << j <<endl;
						valueStream = "Test data value: " +  std::to_string(j);
    					//cout <<  valueStream << endl;
    					skipPair.push_back(valueStream);

    					//cout << "skipPair size = " << skipPair.size() << endl;
    					skipList.push_back(skipPair);
    					skipPair.clear();

    		}
    		cout << "skipList size = " << skipList.size() << endl;
    		skipArray.push_back(skipList);
    		cout << "skipArray size = " << skipArray.size() << endl;

    		skipList.clear();
        }
    cout << "Start: Inserting skip list array to database" << endl;

    db->PutSkipArray(writeOptions, skipArray);

    cout << "End: Inserting skip list array to database" << endl;

    
    // Iterate over each item in the database and print them
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    
    cout << "Reading database now" << endl;

    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        cout << it->key().ToString() << " : " << it->value().ToString() << endl;
    }
    
    if (false == it->status().ok())
    {
        cerr << "An error was found during the scan" << endl;
        cerr << it->status().ToString() << endl; 
    }
    
    delete it;
    
    // Close the database
    delete db;
}

