//
// Created by virgil on 2021/5/28.
//
#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <iomanip>

namespace tool {
    /**
     * 用于打印数组,尤其适用于打印渲染数据，打印规则可以用于分隔 顶点数据---颜色--向量
     * @tparam T 数组中元素类型
     * @param vec 传入的数组
     * @param num 传入数组的大小
     * @param rule_size 打印规则的数量
     * @param ... 具体的打印规则
     * 例子：-----
     * vec[] = {1,2,3,4,5, 6,7,8,9,10}
     * num : 10
     * rule size : 2
     * ... : 2,3
     * 输出结果
     * 1 2 --- 3 4 5
     * 6 7 --- 8 9 10
     */
    template<typename T>
    static void PrintVec(T vec[], uint32_t num, uint32_t rule_size, ...) {
        va_list args;
        // read rule
        std::vector<uint32_t> rule(rule_size, 0);
        va_start(args, rule_size);
        for (int i = 0; i < rule_size; ++i) {
            rule.at(i) = va_arg(args, uint32_t);
        }
        va_end(args);

        // print
        uint32_t count = 0, rule_index = 0;
        for (int i = 0; i < num; ++i) {
            if (count >= rule.at(rule_index)) {
                count = 0;
                rule_index += 1;
                printf("----");
            }
            if (rule_index >= rule_size) {
                rule_index = 0;
                printf("\n");
            }
            std::cout << std::setw(5) << std::right << vec[i] << "\t";
            ++count;
        }
    }


}


