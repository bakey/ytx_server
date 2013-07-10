EXECUTABLE := main_exe 
TOOLS := tools/regex_check
LIBS := pthread  z tinyxml2 xml2 log4cpp md5 pcre mysqlclient dl rt uldict crypto uconv ullib
DEPEND := ../../depend/
MYINC := $(DEPEND)/ullib/output/include $(DEPEND)/dict/output/include/ $(DEPEND)/uconv/output/include $(DEPEND)/ullib/output/include/comlog
MYLIB := -L$(DEPEND)/ullib/output/lib/ -L$(DEPEND)/dict/output/lib/ -L$(DEPEND)/uconv/output/
INCS := ./ ../include $(MYINC)
USER_MARCOS := 
LIBPATHS := ../lib/ $(MYLIB)
CFLAGS = -g -Wall -Wno-deprecated -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -Wno-write-strings $(INCLUDE)
CC = g++

DIRS:=.  
SOURCE := $(foreach DIRS,$(DIRS),$(wildcard $(DIRS)/*.cpp)) 
OBJS := $(patsubst %.cpp,%.o,$(SOURCE))
TOOLS_OBJS := $(patsubst tools/%.cpp,tools/%.o,$(wildcard tools/*.cpp))

%.o:%.cpp
	$(CC) $(CFLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I,$(INCS)) -c $< -o $@
tools/%.o:tools/%.cpp
	$(CC) $(CFLAGS) $(addprefix -D,$(USER_MARCOS)) $(addprefix -I,$(INCS)) -c $< -o $@
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o  $(EXECUTABLE) $(OBJS)  -L $(LIBPATHS) $(addprefix -l,$(LIBS))

mytool : $(TOOLS_OBJS)
	$(CC) $(CFLAGS) -o mytool $(TOOLS_OBJS)  regular.o html_class.o -L $(LIBPATHS) $(addprefix -l,$(LIBS))
#	rm $(OBJS)
#	cp -v ./$(EXECUTABLE) ../../bin/$(EXECUTABLE)

clean:  
	rm -rf *~?? core* *.d *.o *.lo *.bak $(EXECUTABLE)
	
     
realclean: clean
	rm -rf *.o *.d *.lo  $(EXECUTABLE)  

DEPEND= makedepend $(addprefix -D,$(USER_MARCOS)) $(addprefix -I,$(INCS))
depend:$(SOURCE)
	$(DEPEND) $(SOURCE)
