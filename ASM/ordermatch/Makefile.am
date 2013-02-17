#SUBDIRS = test

noinst_PROGRAMS = ordermatch

ordermatch_SOURCES = \
	ordermatch.cpp \
	Application.h \
	Application.cpp \
	IDGenerator.h \
	Market.h \
	Market.cpp \
	Order.h \
	OrderMatcher.h \
	../utils/AgentControl.h \
	../utils/AgentControl.cpp

ordermatch_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I../utils

all-local:
	rm -f ../../bin/ordermatch
