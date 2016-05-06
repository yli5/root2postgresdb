# Unit tests
BINARIES := example_usage tuplereader_ex1

# additional include and library search paths
ROOT2POSTGRES_ROOT = ../
ROOT2POSTGRES_LIBDIR = $(ROOT2POSTGRES_ROOT)/lib
INCFLAGS += $(addprefix -I, $(ROOT2POSTGRES_ROOT)/include)
LDFLAGS += -L$(ROOT2POSTGRES_LIBDIR) -Wl,-rpath,$(ROOT2POSTGRES_LIBDIR) -lroot2postgres

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib
BOOST_LIBS = -lboost_program_options -lboost_regex
INCFLAGS += -I$(BOOST_ROOT)
LDFLAGS += -L$(BOOST_LIBDIR) -Wl,-rpath,$(BOOST_LIBDIR) $(BOOST_LIBS)

CERNROOT_ROOT = $(ROOTSYS)
INCFLAGS += -I$(shell $(CERNROOT_ROOT)/bin/root-config --incdir)
LDFLAGS += $(shell $(CERNROOT_ROOT)/bin/root-config --libs)

LIBPQ_ROOT = /usr/pgsql-9.4
INCFLAGS += -I$(LIBPQ_ROOT)/include
LDFLAGS += -L$(LIBPQ_ROOT)/lib -Wl,-rpath,$(LIBPQ_ROOT)/lib -lpq

# host compiler
CXX ?= g++
CXXFLAGS = -Wall -Werror -pedantic -pthread -std=c++11 -O2

DDIR := .d
$(shell mkdir -p $(DDIR) > /dev/null)
CXXDEPFLAGS = -MT $@ -MMD -MP -MF $(DDIR)/$*.Td
CXXPOSTCOMPILE = @mv -f $(DDIR)/$*.Td $(DDIR)/$*.d
NVCCPOSTCOMPILE = @$(NVCC) -M -MT $@ $(NVCCFLAGS) $(INCFLAGS) $< -o $(DDIR)/$@.d

.PHONY : all clean cleanall

all : $(BINARIES)

% : %.cc
	$(CXX) $(CXXDEPFLAGS) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) $< -o $@
	$(CXXPOSTCOMPILE)

$(DDIR)/%.d : ;

include $(patsubst %,$(DDIR)/%.d,$(BINARIES))

clean:
	@rm -rf *~ *.o $(BINARIES)

cleanall: clean
	@rm $(DDIR)/*.d
