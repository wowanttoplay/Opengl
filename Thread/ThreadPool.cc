//
// Created by virgil on 2021/5/26.
//

#include "ThreadPool.h"
#include "Task.h"
using namespace std;

ThreadPool::ThreadPool(uint32_t thread_num, const std::string &pool_name) {
    if (thread_num < 1) thread_num = 1;
    rest_thread_num_.store(thread_num);
    name_ = pool_name;
    // create thread
    for (int i = 0; i < thread_num; ++i) {
        printf("create a new thread\n");
        thread_list_.emplace_back([this]()-> void {
            // thread task
            while (!this->stoped_.load()) {
                unique_lock<mutex> lc(this->mu_);
                // wait for not in paused
                this->cv_paused_.wait(lc, [this]()->bool {
                    return this->stoped_.load() || !this->paused_.load();
                });
                // wait for task num > 0
                this->cv_task_.wait(lc, [this]()->bool {
                    return this->stoped_.load() || !this->task_list_.empty();
                });
                // run task
                if (this->stoped_.load()) return;
                auto task = std::move(task_list_.front());
                task_list_.pop_front();

                --rest_thread_num_;
                printf("执行任务");
                RunTask(task);
                ++rest_thread_num_;
            }

        });
    }
}

void ThreadPool::Commit(std::shared_ptr<Task> task) {
    if (task == nullptr) return;
    if (stoped_.load()) {
        throw runtime_error("commit is invalid, the thread pool is terminate");
    }
    unique_lock<mutex> lc(mu_);
    task_list_.emplace_back(task);
    task_list_.sort([](const shared_ptr<Task> left, const shared_ptr<Task> right){
        return left->GetPriority() > right->GetPriority();
    });
    cv_task_.notify_one();
    printf("commit task\n");
}

void ThreadPool::Terminate() {
    stoped_.store(true);
    cv_task_.notify_all();
    // wait for all thread is run finished
    for (auto& thread : thread_list_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::RunTask(std::shared_ptr<Task> task) {
    if (task == nullptr) return;
    task->Run();
}

bool ThreadPool::CancleTask(uint32_t task_id) {
    if (stoped_.load()) {
        throw std::runtime_error("cancle is valid, thread pool is stoped");
    }

    unique_lock<mutex> lc(mu_);
    for (auto beg = std::begin(task_list_); beg != end(task_list_); ++beg) {
        if ((*beg)->GetId() == task_id) {
            task_list_.erase(beg);
            return true;
        }
    }
    return false;
}



