noinst_PROGRAMS = randomtraders

randomtraders_SOURCES = \
	randomtraders.cpp \
	Application.h \
	Application.cpp \
	Strategy.h \
	Strategy.cpp \
	SimpleOrder.h \
	SimpleOrder.cpp \
	AgentControl.h \
	AgentControl.cpp

randomtraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I.. 

all-local:
	rm -f ../../bin/randomtraders
	ln -s ../examples/ordermatch/randomtraders ../../bin/randomtraders
