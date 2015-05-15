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
 * @file        log.cpp
 * @author      Janusz Kozerski <j.kozerski@samsung.com>
 * @brief       This file declares class for ask user window
 */

#include <stdexcept>
#include <systemd/sd-journal.h>

void JournalLog(int logLevel,
                const char *message,
                const char *fileName,
                int line,
                const char *function)
{
    try {
        sd_journal_send("PRIORITY=%d", logLevel,
                "CODE_FILE=%s", fileName,
                "CODE_FUNC=%s", function,
                "CODE_LINE=%d", line,
                // add file, line & function info to log message
                "MESSAGE=[%s:%d] %s(): %s", fileName, line, function, message,
                NULL);
    } catch (const std::out_of_range&) {
        sd_journal_send(
                "PRIORITY=%d", LOG_ERR,
                "CODE_FILE=%s", fileName,
                "CODE_FUNC=%s", function,
                "CODE_LINE=%d", line,
                // add file, line & function info to log message
                "MESSAGE=[%s:%d] %s(): Unsupported log level %d", fileName, line, function, logLevel,
                NULL);
    }
}
