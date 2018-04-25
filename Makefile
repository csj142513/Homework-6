#
# UTD CS3377.501 CDK Makefile
# CHRIS JOSEPH
# CSJ160130@utdallas.edu
#

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkfile

OBJS = cdkfile.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

