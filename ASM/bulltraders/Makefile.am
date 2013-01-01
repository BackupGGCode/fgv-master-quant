noinst_PROGRAMS = bulltraders

bulltraders_SOURCES = \
	bulltraders.cpp \
	Application.h \
	Application.cpp

bulltraders_LDADD = $(top_builddir)/src/C++/libquickfix.la 

INCLUDES = -I$(top_builddir)/include -I..

all-local:
	rm -f ../../bin/bulltraders
	ln -s ../examples/ordermatch/bulltraders ../../bin/bulltraders
