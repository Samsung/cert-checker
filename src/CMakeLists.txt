PKG_CHECK_MODULES(CERT_CHECKER_DEP
    REQUIRED
    dbus-1
    dbus-glib-1
    db-util
    glib-2.0
    gio-2.0
    icu-i18n
    capi-appfw-package-manager
    notification
    libsystemd-journal
    sqlite3
    )

SET(CERT_CHECKER_SRC_PATH ${PROJECT_SOURCE_DIR}/src)

SET(CERT_CHECKER_SOURCES
    ${CERT_CHECKER_SRC_PATH}/cert-checker.cpp
    ${CERT_CHECKER_SRC_PATH}/app.cpp
    ${CERT_CHECKER_SRC_PATH}/logic.cpp
    # logs
    ${CERT_CHECKER_SRC_PATH}/log/log.cpp
    # dpl
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/assert.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/char_traits.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/errno_string.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/exception.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/noncopyable.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/core/src/string.cpp
    # dpl DB
    ${CERT_CHECKER_SRC_PATH}/dpl/db/src/sql_connection.cpp
    ${CERT_CHECKER_SRC_PATH}/dpl/db/src/naive_synchronization_object.cpp
    )

INCLUDE_DIRECTORIES(SYSTEM
    ${CERT_CHECKER_DEP_INCLUDE_DIRS}
    ${CERT_CHECKER_SRC_PATH}/include/
    ${CERT_CHECKER_SRC_PATH}/log/
    ${CERT_CHECKER_SRC_PATH}/dpl/core/include/
    ${CERT_CHECKER_SRC_PATH}/dpl/db/include/
    )

ADD_EXECUTABLE(${TARGET_CERT_CHECKER} ${CERT_CHECKER_SOURCES})

TARGET_LINK_LIBRARIES(${TARGET_CERT_CHECKER}
    ${CERT_CHECKER_DEP_LIBRARIES}
    )

INSTALL(TARGETS ${TARGET_CERT_CHECKER} DESTINATION ${BINDIR})
