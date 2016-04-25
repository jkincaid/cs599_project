#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "trie.h"

using namespace std;

// Returns time in seconds.
std::chrono::duration<double> benchmark(unsigned long query_size, unsigned long subject_size);
std::string random_sequence(unsigned long size, std::mt19937_64 rand_gen);

std::chrono::duration<double> benchmark(unsigned long query_count, unsigned long subject_size)
{
    std::mt19937_64 rand_gen;
    const int ITER_COUNT = 100;
    const int MER_LEN = 50;

    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
    start_time = std::chrono::high_resolution_clock::now();
    for(int iter = 0; iter < ITER_COUNT; iter++)
    {
        Trie* trie = new Trie();
        for(int i = 0; i < query_count; i++)
        {
            trie->addQuery(random_sequence(MER_LEN, rand_gen));
        }
        std::string subject = random_sequence(subject_size, rand_gen);
        trie->searchTrieRecursively(trie->getRoot(), subject, 1);

        delete trie;
    }
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> exec_duration = end_time - start_time;
    // Account for the average duration.
    exec_duration /= ITER_COUNT;

    return exec_duration;
}

std::string random_sequence(unsigned long size, std::mt19937_64 rand_gen)
{
    std::uniform_int_distribution<unsigned long long> dist(0,3);
    unsigned char table[4] = {'A', 'C', 'G', 'T'};

    std::string sequence;
    sequence.reserve(size);

    for(unsigned long i = 0; i < size; i++)
    {
        sequence[i] = table[dist(rand_gen)];
    }

    return sequence;
}

// Test program
int main()
{
    // Benchmark construction, search, and destruction.
    unsigned int query_counts[4] = {100, 1000, 10000, 100000};
    for(unsigned int count : query_counts)
    {
        std::cout << "Benchmarking query count of " << count << "..." << std::endl;
        std::chrono::duration<double> exec_duration = benchmark(count, 1000000);
        std::cout << "Done." << std::endl << "Time: " << exec_duration.count() << " s" << std::endl;
    }

    std::cout << std::endl;
    unsigned int subj_sizes[4] = {10000, 100000, 1000000, 10000000};
    for(unsigned int size : subj_sizes)
    {
        std::cout << "Benchmarking subject size " << size << "..." << std::endl;
        std::chrono::duration<double> exec_duration = benchmark(50, size);
        std::cout << "Done." << std::endl << "Time: " << exec_duration.count() << " s" << std::endl;
    }



	// Create trie
    Trie* trie = new Trie;

    // Add queries
    trie->addQuery("ATTGGTACACATTGGTACACATTGGTACACATTGGTACACATTGGTACAC");
    trie->addQuery("ACGGTGCGGCTTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");
    trie->addQuery("ATAACCCATATTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");
    trie->addQuery("CAAACCCCTTTTATTGGTACACATTGGTACACATTGGTACACATTGGTAC");

	// Search for subject
    string subject = "ACGGTGCGGCTTATTGGTACACATTGGTACACACTGGTACACATTGGTAC";
    trie->searchTrieRecursively(trie->getRoot(), subject, 1);

    cout << "Found " << subject << " at: " << trie->getIndex() << " with: " << trie->getMismatch() << " mismatches."  << endl;
    // TODO Create local variable that keeps track of best mismatches and index.

    // Free memory because we are good people
    delete trie;

    //input from file testing and tree building
    int* listSize = new int[5] {100,1000,10000,50000,100000};
    std::string fileName = "dengV2_";
    int listIndex = 0;

    //create new tree
    Trie* listTest = new Trie;

    //prefix of name of the test files
    std::string tmpFileName = fileName;

    //append the length of the list to the name of the file
    tmpFileName += to_string(listSize[listIndex]);

    //add mime type because cxx hates you
    tmpFileName += ".txt";

    //open the file
    ifstream file(tmpFileName);

    //debug
    //ofstream wfile("dengV2_index11.txt");

    //temp string to store references
    std::string* strTemp = new std::string[5];

    if (file.is_open()) {

        printf("\nfile was opened\n");

        int count = 0;

        for (string line; getline(file, line);) {

            //if(count %10 == 0)
            //   printf("Str count %d : %s\n",(int) line.length(), line.c_str());
            listTest->addQuery(line);

            if(count<5){

                strTemp[count++] = line;
            }

        }
    }else {
        printf("failed to open file");
        return 0;
    }

    //display tree info
    printf("\n%s %6d %s %6d %s\n","Trie was created with list of size ", listSize[listIndex],
           " the size of the trie is ", listTest->getSize(),"# of nodes");

    //test to see if known strings are in tree
    for(int j = 0; j < 5; j++) {

        listTest->searchTrieRecursively(listTest->getRoot(),strTemp[j],1);

        if(listTest->getMismatch() != 99999999) {
            printf("%s %s %s %d %s %d\n", "found the word", strTemp[j].c_str(),
                   "with #", listTest->getMismatch(), " mismatches at index ",
                   listTest->getIndex());
        }else{

            printf("\nDidn't find it recursively lets check our search function!\nBecause it should be in the list\n");

            if(listTest->strictSearch(strTemp[j])){

                printf("\nfound the word %s\n", strTemp[j].c_str());
            }else{

                printf("\nsearch didn't find the word, our trie might be broken\nor most likely both");
            }



        }
    }

    delete listTest;
    file.close();



    // Success
    return 0;
}

