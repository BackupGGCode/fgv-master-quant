noinst_PROGRAMS = bbandtraders

bbandtraders_SOURCES = \
	bbandtraders.cpp \
	Application.h \
	Application.cpp \
	Strategy.h \
	Strategy.cpp \
	../utils/SimpleOrder.h \
	../utils/SimpleOrder.cpp \
	../utils/AgentControl.h \
	../utils/AgentControl.cpp

bbandtraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I.. -I../utils

all-local:
	rm -f ../../bin/bbandtraders

