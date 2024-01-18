#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <ctime>

std::queue<int> dataQueue;
std::mutex mutexForQueue;
std::condition_variable cv;

static int rangeMax = 100;

// 生产者线程
void producerThread()
{
    while (true) {
        // 产生一个随机数字
        int randomNumber = std::rand() % rangeMax;

        {
            std::lock_guard<std::mutex> lock(mutexForQueue);
            // 将数字放入队列
            dataQueue.push(randomNumber);
            std::cout << "Produced: " << randomNumber << std::endl;
        }

        // 通知消费者线程有新数据
        cv.notify_one();

        // 休眠一段时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// 消费者线程
void consumerThread()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mutexForQueue);

        // 等待有数据可消费
        cv.wait(lock, []{ return !dataQueue.empty(); });

        // 取出队列中的数字
        int data = dataQueue.front();
        dataQueue.pop();

        std::cout << "Consumed: " << data << std::endl;

        // 释放锁，允许生产者线程继续生产
        lock.unlock();

        // 休眠一段时间
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        rangeMax = std::stoi(argv[1]);
    }
    
    // 设置随机数种子
    std::srand(std::time(0));

    // 启动生产者线程和消费者线程
    std::thread producer(producerThread);
    std::thread consumer(consumerThread);

    // 等待线程结束
    producer.join();
    consumer.join();

    return 0;
}
