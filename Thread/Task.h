//
// Created by virgil on 2021/5/26.
//

#include <string>
#include <functional>

using NormalFunc = std::function<void()>;

class Task {
public:
    Task(const NormalFunc& func) {
        func_ = func;
    }
    virtual ~Task() = default;
    void Run(){ func_(); }
    void SetPriority(uint32_t priorirty) { priority_ = priorirty; }
    inline uint32_t GetPriority() const { return priority_; }
    inline uint32_t GetId() {return task_id_; }
private:
    uint32_t task_id_ = 0;
    uint32_t priority_ = 0;
    NormalFunc func_;
};
