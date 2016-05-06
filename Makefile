# directory configuration
# -----------------------

# executables 
BINARIES = root2postgres

# objects to package into the shared library
OBJECTS = TupleReader.o ColumnConfigParser.o PostgresConnector.o

# local directory settings and library name
INCDIR = include
LIBDIR = lib
LIBNAME = libroot2postgres.so

INCFLAGS = -I$(INCDIR)
LDFLAGS = -L$(LIBDIR) -Wl,-rpath,$(LIBDIR) -lroot2postgres

# external dependencies
# ---------------------

BOOST_ROOT = /usr/local/boost_1_59_0
BOOST_LIBDIR = $(BOOST_ROOT)/stage/lib
BOOST_LIBS = -lboost_program_options -lboost_regex
INCFLAGS += -I$(BOOST_ROOT)
LDFLAGS += -L$(BOOST_LIBDIR) -Wl,-rpath,$(BOOST_LIBDIR) $(BOOST_LIBS)

CERNROOT_ROOT = $(ROOTSYS)
INCFLAGS += -I$(shell $(CERNROOT_ROOT)/bin/root-config --incdir)
LDFLAGS += $(shell $(CERNROOT_ROOT)/bin/root-config --libs)

INCFLAGS += -I/usr/pgsql-9.4/include
LDFLAGS += -L/usr/pgsql-9.4/lib -lpq

# build rules
# -----------

CXX := g++
CXXFLAGS = -Wall -Werror -fPIC -pedantic -pthread -std=c++11 -O2

SRCS = $(wildcard src/*.cc)
BUILDDIR = build

DEPDIR = .d
$(shell mkdir -p $(DEPDIR) > /dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

all : $(BINARIES) lib

root2postgres : $(BUILDDIR)/root2postgres.o lib
	$(CXX) $(LDFLAGS) $< -o $@

lib : $(addprefix $(BUILDDIR)/, $(OBJECTS))
	if [ "$(shell uname)" = "Darwin" ]; then \
    SHARED_LIB_FLAG="-dynamiclib -Wl,-install_name,@rpath/$(LIBNAME)"; \
  else \
    SHARED_LIB_FLAG="-shared -Wl,-soname,$(LIBNAME)"; \
  fi; \
	$(CXX) $${SHARED_LIB_FLAG} $^ -o $(addprefix $(LIBDIR)/, $(LIBNAME))

$(BUILDDIR)/%.o : src/%.cc
$(BUILDDIR)/%.o : src/%.cc $(DEPDIR)/%.d
	$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PRECIOUS: $(DEPDIR)/%.d

-include $(patsubst %,$(DEPDIR)/%.d,$(notdir $(basename $(SRCS))))

clean : 
	@rm -f *~ $(BINARIES) $(LIBDIR)/* $(BUILDDIR)/*

cleanall : clean
	@rm -f $(DEPDIR)/*
