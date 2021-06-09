//
// Created by virgil on 2021/5/26.
//

#pragma once

#include <memory>
#include <list>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <thread>
#include <functional>
#include <string>

class Task;


class ThreadPool : public std::enable_shared_from_this<ThreadPool> {
public:
    ThreadPool(uint32_t thread_num, const std::string& pool_name);
    virtual ~ThreadPool() { Terminate(); }
    void Commit(std::shared_ptr<Task> task);
    void Terminate();
    inline uint32_t RestThreadNum() { return rest_thread_num_.load(); }
    bool CancleTask(uint32_t task_id);
    void RunTask(std::shared_ptr<Task> task);
    inline std::string GetName() { return name_; }
    inline uint32_t GetThreadSize() { return thread_list_.size(); }
    inline uint32_t GetTaskSize() { return task_list_.size(); }

private:
    std::list<std::thread> thread_list_;
    std::list<std::shared_ptr<Task>> task_list_;
    std::mutex mu_;
    std::condition_variable cv_task_; // 任务数量锁
    std::atomic<bool> stoped_ = false; // 是否关闭提交
    std::atomic<uint32_t> rest_thread_num_;
    std::atomic<bool> paused_ = false;
    std::condition_variable cv_paused_;   // 是否在后台
    std::string name_;
};


