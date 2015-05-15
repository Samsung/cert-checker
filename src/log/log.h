/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/**
 * @file        log.h
 * @author      Janusz Kozerski <j.kozerski@samsung.com>
 * @brief       Project log framework - logs into journal
 */

#include <sstream>
#include <systemd/sd-journal.h>

#ifndef CERT_CHECKER_LOG_H
#define CERT_CHECKER_LOG_H

void JournalLog(int logLevel, const char *message, const char *fileName,
                int line, const char *function);

/*
 * Replacement low overhead null logging class
 */
class NullStream
{
    public:
        NullStream() {}

        template <typename T>
        NullStream& operator<<(const T&)
        {
            return *this;
        }
};

/* avoid warnings about unused variables */
#define DPL_MACRO_DUMMY_LOGGING(message, level) \
    do {                                        \
        NullStream ns;                          \
        ns << message;                          \
    } while (0)

#define CERT_CHECKER_LOG(message, level)         \
do                                               \
{                                                \
    std::ostringstream platformLog;              \
    platformLog << message;                      \
    JournalLog(level,                            \
               platformLog.str().c_str(),        \
               __FILE__,                         \
               __LINE__,                         \
               __FUNCTION__);                    \
} while (0)

/* Errors must be always logged. */
#define  LogError(message)          \
    CERT_CHECKER_LOG(message, LOG_ERR)

#ifdef BUILD_TYPE_DEBUG
    #define LogDebug(message)       \
        CERT_CHECKER_LOG(message, LOG_DEBUG)
    #define LogInfo(message)        \
        CERT_CHECKER_LOG(message, LOG_INFO)
    #define LogWarning(message)     \
        CERT_CHECKER_LOG(message, LOG_WARNING)
#else
    #define LogDebug(message)       \
        DPL_MACRO_DUMMY_LOGGING(message, LOG_DEBUG)
    #define LogInfo(message)        \
        DPL_MACRO_DUMMY_LOGGING(message, LOG_INFO)
    #define LogWarning(message)     \
        DPL_MACRO_DUMMY_LOGGING(message, LOG_WARNING)
#endif // BUILD_TYPE_DEBUG

#endif //CERT_CHECKER_LOG_H

