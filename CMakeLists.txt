# Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#
# @file        CMakeLists.txt
# @author      Janusz Kozerski <j.kozerski@samsung.com>
# @brief
#

############################# Check minimum CMake version #####################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT("cert-checker")

############################# cmake packages ##################################

INCLUDE(FindPkgConfig)

#############################     defines    ##################################

SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(BINDIR "${PREFIX}/bin")
SET(RESDIR "${PREFIX}/res")
SET(LOCALEDIR "${RESDIR}/locale")

############################# compiler flags ##################################

SET(CMAKE_CXX_FLAGS_PROFILING  "-g -std=c++0x -O0 -pg -Wp,-U_FORTIFY_SOURCE")
SET(CMAKE_C_FLAGS_DEBUG        "-g -O0 -ggdb -Wp,-U_FORTIFY_SOURCE")
SET(CMAKE_CXX_FLAGS_DEBUG      "-g -std=c++0x -O0 -ggdb -Wp,-U_FORTIFY_SOURCE")
SET(CMAKE_C_FLAGS_RELEASE      "-g -O2")
SET(CMAKE_CXX_FLAGS_RELEASE    "-g -std=c++0x -O2")
SET(CMAKE_CXX_FLAGS_CCOV       "-g -std=c++0x -O2 --coverage")

# Set compiler warning flags
ADD_DEFINITIONS("-Werror")                      # Make all warnings into errors.
ADD_DEFINITIONS("-Wall")                        # Generate all warnings
ADD_DEFINITIONS("-Wextra")                      # Generate even more extra warnings
ADD_DEFINITIONS("-fvisibility=hidden -fPIE")    # Hide symbols by default

# Pass project name to sources
ADD_DEFINITIONS("-DPROJECT_NAME=\"${PROJECT_NAME}\"")

IF (CMAKE_BUILD_TYPE MATCHES "DEBUG")
    ADD_DEFINITIONS("-DBUILD_TYPE_DEBUG")
ENDIF (CMAKE_BUILD_TYPE MATCHES "DEBUG")

SET(TARGET_CERT_CHECKER "cert-checker")

ADD_SUBDIRECTORY(src)
