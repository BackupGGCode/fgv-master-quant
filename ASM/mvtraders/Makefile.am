noinst_PROGRAMS = mvtraders

mvtraders_SOURCES = \
	mvtraders.cpp \
	Application.h \
	Application.cpp \
	Strategy.h \
	Strategy.cpp \
	SimpleOrder.h \
	SimpleOrder.cpp \
	../utils/AgentControl.h \
	../utils/AgentControl.cpp

mvtraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I.. 

all-local:
	rm -f ../../bin/mvtraders

