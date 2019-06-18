#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include <vector>
#include <utility>
#include <deque>
#include <thread>
#include <functional>
#include <condition_variable>
#include <mutex>

class ThreadPool{
    public:
        typedef std::function<void()> TaskT;

        ThreadPool(int init_size = 3);
        ~ThreadPool();

        void Stop();
        void AddTask(const TaskT &);

    private:
        ThreadPool(const ThreadPool &);
        const ThreadPool operator=(const ThreadPool&);

        bool isStarted() {return mIsStarted;}
        void Start();

        void ThreadLoop();
        TaskT Take();

        typedef std::vector<std::thread*> ThreadsT;
        typedef std::deque<TaskT>* TasksT;

        int mInitThreadsSize;

        ThreadsT mThreads;
        TasksT mTasks;

        std::mutex mMutex;
        std::condition_variable mCond;

        bool mIsStarted;
};

#endif