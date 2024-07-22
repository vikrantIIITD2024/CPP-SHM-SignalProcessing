#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <ctime>
using namespace std;
//storing data in a structure
struct SharedData
{
    double myCounter;
    struct timeval myTimestamp;
    double thetaValue;
    double sineValue;
};

//storing the time in a char array
char formattedTime[100];

void setFreq(struct timespec &sleepTime)
{
    sleepTime.tv_sec = 0;
    sleepTime.tv_nsec = 6666667; // -----freq = 1/t => (1/150)*1000000000 => 66 milliseconds(approx.)---
}

int main()
{
    //an object of SharedData structure
    SharedData *sharedData;

    //---------------------sharing of data between scripts------------------------------------
    int sharedMemoryFd = shm_open("/shared_memory", O_RDWR, 0666);
    sharedData = static_cast<SharedData *>(mmap(nullptr, sizeof(SharedData), PROT_READ, MAP_SHARED, sharedMemoryFd, 0));

    struct timespec sleepTime;

    setFreq(sleepTime); // Set the frequency

    while (true)
    {
        // Format the timestamp
        time_t currTime = sharedData->myTimestamp.tv_sec;
        tm *timeInfo = localtime(&currTime);

        strftime(formattedTime, sizeof(formattedTime), "%a %b %d %T %Y", timeInfo);

        // Printing the shared values by Script A and Script B
        cout << "Counter: " << sharedData->myCounter << endl;
        cout << "Corresponding Timestamp: " << formattedTime << endl;
        cout << "Theta Value: " << sharedData->thetaValue << endl;
        cout << "Sine Value: " << sharedData->sineValue << endl;

        nanosleep(&sleepTime, NULL); // Sleep for approximately 150 Hz
    }

    //sharing data
    munmap(sharedData, sizeof(SharedData));
    close(sharedMemoryFd);

    return 0;
}
