.SUFFIXES:	# Delete the default suffixes
.SUFFIXES:	.cc .hh
.PHONY:		all clean astyle 

TARGET		= main
CC_FILES	= $(wildcard *.cc)
HH_FILES	= $(wildcard *.hh)
O_FILES = 	$(CC_FILES:%.cc=%.o)

default: all

all: $(TARGET)

main.hh: ; touch main.hh

$(O_FILES): %.o: %.cc %.hh Makefile
	g++ -Wall $*.cc -c

$(TARGET): %: $(O_FILES) Makefile
	g++ -Wall $(O_FILES) -o $*

ASTYLE_OPTIONS = 	--style=attach --indent=spaces=2

astyle:
	astyle $(ASTYLE_OPTIONS) $(CC_FILES) $(HH_FILES)

clean:
	-rm -f $(O_FILES) $(TARGET) *.orig
	-rm -rf *.dSYM
