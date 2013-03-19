noinst_PROGRAMS = randomtraders

randomtraders_SOURCES = \
	randomtraders.cpp \
	Application.h \
	Application.cpp \
	Strategy.h \
	Strategy.cpp \
	../utils/SimpleOrder.h \
	../utils/SimpleOrder.cpp \
	../utils/AgentControl.h \
	../utils/AgentControl.cpp

randomtraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I.. -I../utils

all-local:
	rm -f ../../bin/randomtraders
