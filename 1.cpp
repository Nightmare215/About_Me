#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

mutex mutex;
std::condition_variable cv;
bool s_Finished = false;

void DoWork()
{
    std::unique_lock<std::mutex> lock(mutex);
    while(!s_Finished)
    {
        std::cout << "Working... \n";
        cv.wait(lock);
    }
}

int main()
{
    std::thread worker(DoWork);

    std::cin.get();
    {
        std::lock_guard<std::mutex> lock(mutex);
        s_Finished = true;
    }
    cv.notify_one();

    worker.join();

    std::cin.get();
    return 0;
}