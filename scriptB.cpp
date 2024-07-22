#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <cmath>
using namespace std;
//using oops concept of storing data in a structure
//Here we are storing sineValue and thetaValue in a double
struct SharedData
{
    double thetaValue;
    double sineValue
};

//setting frequency 50Hz
void setFreq(struct timespec &sleepTime)
{

    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = 20000000; // -----freq = 1/t => 1/50 => 0.02s => 20 milliseconds---
}

int main()
{

    //an object of SharedData structure
    SharedData *sharedData;

    //---------------------sharing of data between scripts------------------------------------
    int sharedMemoryFd = shm_open("/shared_memory", O_RDWR, 0666);
    sharedData = static_cast<SharedData *>(mmap(nullptr, sizeof(SharedData), PROT_READ, MAP_SHARED, sharedMemoryFd, 0));

    struct timespec sleepTime;
    setFreq(sleepTime); // Setting the frequency to 50Hz

    while (sharedData->thetaValue <= 1000000)
    {
        double thetaValueExtracted = sharedData->thetaValue;
        double sineWaveValue = sin(thetaValueExtracted); //calculating sin

        //--------------------Printing the theta Value and sine wave-----------------------
        cout << "Theta Value: " << thetaValueExtracted << endl;
        cout << "Sine Value: " << sineWaveValue << endl;

        // -----freq = 1/t => 1/50 => 0.02s => 20 milliseconds---
        nanosleep(&sleepTime, NULL); //  50Hz --> 20ms
    }

    munmap(sharedData, sizeof(SharedData));
    close(sharedMemoryFd);

    return 0;
}
