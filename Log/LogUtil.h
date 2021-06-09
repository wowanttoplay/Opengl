//
// Created by virgil on 2021/5/28.
//

#pragma once

enum class LogLevel{
    LogLevel_None,
    LogLevel_Info,
    LogLevel_Warning,
    LogLevel_Error
};
extern LogLevel log_level;


#define __FILENAME__ (strrchr(__FILE__, '/') + 1) // 文件名

//#define logE(format, ...) if (log_level < LogLevel::LogLevel_Error) printf("[%s][%s][%s]: " format "\n",__FILE_NAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define logE(format, ...) log(LogLevel::LogLevel_Error, format, ##__VA_ARGS__)
#define logW(format, ...) log(LogLevel::LogLevel_Warning, format, ##__VA_ARGS__)
#define logI(format, ...) log(LogLevel::LogLevel_Info, format, ##__VA_ARGS__)

#define log(level, format, ...) if (level <= log_level) printf("[%s][%s][%d]: " format "\n",__FILE_NAME__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

static void SetLogLevel(const LogLevel& level) {
    log_level = level;
}

