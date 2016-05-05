# directory configuration
# -----------------------

# executables 
BINARIES = test_root2postgres

# local directory settings and library name
INCDIR = ../include
LIBDIR = ../lib

# external dependencies
# ---------------------

# root2postgres
INCFLAGS += -I$(INCDIR)
LDFLAGS = -L$(LIBDIR) -Wl,-rpath,$(LIBDIR) -lroot2postgres

# Boost
BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib
BOOST_LIBS = -lboost_program_options -lboost_regex
INCFLAGS += -I$(BOOST_ROOT)
LDFLAGS += -L$(BOOST_LIBDIR) -Wl,-rpath,$(BOOST_LIBDIR) $(BOOST_LIBS)

# Postgre 
INCFLAGS += -I/usr/pgsql-9.4/include
LDFLAGS += -L/usr/pgsql-9.4/lib -lpq

# CERN ROOT
CERNROOT_ROOT = $(ROOTSYS)
INCFLAGS += -I$(shell $(CERNROOT_ROOT)/bin/root-config --incdir)
LDFLAGS += $(shell $(CERNROOT_ROOT)/bin/root-config --libs)

# build rules
# -----------

OBJS = $(patsubst %, %.o, $(BINARIES))
SRCS = $(patsubst %, %.cc, $(BINARIES))

CXX ?= g++
CXXFLAGS = -Wall -std=c++11 -fPIC

.PHONY: all clean

all : CXXFLAGS += -O3
all : $(BINARIES)

$(BINARIES) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCFLAGS) -Wl,-rpath,$(LIBDIR) $(OBJS) -o $@ 

$(OBJS) : $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $(SRCS) -o $@

clean:
	rm -f $(OBJS) $(BINARIES) 
