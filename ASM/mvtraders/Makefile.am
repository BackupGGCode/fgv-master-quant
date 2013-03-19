noinst_PROGRAMS = mvtraders

mvtraders_SOURCES = \
	mvtraders.cpp \
	Application.h \
	Application.cpp \
	Strategy.h \
	Strategy.cpp \
	../utils/SimpleOrder.h \
	../utils/SimpleOrder.cpp \
	../utils/AgentControl.h \
	../utils/AgentControl.cpp

mvtraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I.. -I../utils

all-local:
	rm -f ../../bin/mvtraders

