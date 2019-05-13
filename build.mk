ROOT := $(strip ${ROOT})/..
DIRNAME := ut

STATIC_MODULES += ut

DIR_MODULE := ut
include $(strip ${BLDFILES})/header.mk

DIR_OBJS := testcase
DIR_OBJS += testsuite
DIR_OBJS += testrunner
DIR_OBJS += stdoutlogger

DIR_EXPORT_HEADERS := testcase
DIR_EXPORT_HEADERS += testlogger
DIR_EXPORT_HEADERS += assertionfailed
DIR_EXPORT_HEADERS += testrunner
DIR_EXPORT_HEADERS += stdoutlogger
DIR_EXPORT_HEADERS += unittests

include $(strip ${BLDFILES})/footer.mk

# vim: set noexpandtab :

