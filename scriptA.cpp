#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <ctime>
using namespace std;
//using oops concept of storing data in a structure
//Here we are storing counter as myCounter and timestamp in a structure
struct SharedData
{
    double myCounter;
    struct timeval myTimestamp;
};

//storing the time in a char array
char timeStampDayMonthDateTimeYear[100];

void setFreq(struct timespec &sleepTime)
{

    sleepTime.tv_sec = 0;

    //its in nano seconds 0.01*10^9 = 10000000
    sleepTime.tv_nsec = 10000000; // -----freq = 1/t => 1/50 => 0.02s => 20 milliseconds---
}

int main()
{

    //an object of SharedData structure
    SharedData *sharedData;

    //---------------------sharing of data between scripts------------------------------------
    int sharedMemoryFd = shm_open("/shared_memory", O_RDWR, 0666);
    sharedData = static_cast<SharedData *>(mmap(nullptr, sizeof(SharedData), PROT_READ, MAP_SHARED, sharedMemoryFd, 0));

    //we converted the frequency into time by using f = 1/t, so we would be using sleeptime to acheive the required frequency
    struct timespec sleepTime;
    setFreq(sleepTime); // Setting the frequency

    while (sharedData->myCounter <= 10000000)
    {

        gettimeofday(&sharedData->myTimestamp, NULL); //exracting time

        // Format the timestamp
        time_t currTime = sharedData->myTimestamp.tv_sec;
        tm *timeInfo = localtime(&currTime);

        strftime(timeStampDayMonthDateTimeYear, sizeof(timeStampDayMonthDateTimeYear), "%a %b %d %T %Y", timeInfo);

        // Printing Counter and formatted timestamp
        //printing counter
        cout << "Counter: " << sharedData->myCounter << endl;
        //printing Timestamp
        cout << "Corresponding Time Stamp: " << timeStampDayMonthDateTimeYear << endl;

        // -----freq = 1/t => 1/100 => 0.01s => 10 milliseconds---
        nanosleep(&sleepTime, NULL);
        sharedData->myCounter += 0.1; //incrementing the myCounter by 0.1 as per Question
    }

    //---------------------sharing of data between scripts------------------------------------
    munmap(sharedData, sizeof(SharedData));
    close(sharedMemoryFd);
    shm_unlink("/shared_memory");

    return 0;
}
