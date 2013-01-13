noinst_PROGRAMS = feeder

feeder_SOURCES = \
	feeder.cpp \
	Application.h \
	Application.cpp

feeder_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I..

all-local:
	rm -f ../../bin/feeder
	ln -s ../examples/ordermatch/feeder ../../bin/feeder
