noinst_PROGRAMS = beartraders

beartraders_SOURCES = \
	beartraders.cpp \
	Application.h \
	Application.cpp

beartraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I..

all-local:
	rm -f ../../bin/beartraders
	ln -s ../examples/ordermatch/beartraders ../../bin/beartraders
