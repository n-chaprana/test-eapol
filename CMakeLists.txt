CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(connection_test_eapol C CXX)

SET(GTEST_TEST "connection_test_eapol")
ADD_DEFINITIONS("-DUSE_DLOG")

SET(dependents "capi-base-common capi-network-connection glib-2.0 gio-2.0 gmock dlog")
SET(pc_dependents "capi-base-common")

INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(GTEST_TEST_PKG REQUIRED ${dependents})

FOREACH(flag ${GTEST_TEST_PKG_CFLAGS})
	SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} -Wall -fPIE")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -pie")

FILE(GLOB GTEST_TEST_SRCS *.cpp)
SET(GTEST_TEST_SRCS ${GTEST_TEST_SRCS})

ADD_EXECUTABLE(${GTEST_TEST} ${GTEST_TEST_SRCS})
TARGET_LINK_LIBRARIES(${GTEST_TEST} ${GTEST_TEST_LDFLAGS} ${GTEST_TEST_PKG_LDFLAGS} -ldl -lgcov)

INSTALL(TARGETS ${GTEST_TEST} RUNTIME DESTINATION /usr/bin)
