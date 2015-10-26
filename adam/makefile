src = Source/
obj = Objects/
bin = Binaries/

inc = -I$(src)

cpp = g++
cfl = -std=c++14 -g -c -Wall -fmax-errors=1 -Wno-sign-compare $(inc) -DDBG=1
lnk = g++
lfl =
lib = -lncurses

compile = mkdir -p $(obj); $(cpp) $(cfl) $< -o $@
link =    mkdir -p $(bin); $(lnk) $(lfl) $+ -o $@ $(lib)

all : $(bin)eve

$(bin)eve : $(obj)eve.o $(obj)tty.o $(obj)parse.o
	$(link)

$(obj)eve.o : $(src)eve.cpp $(src)tty.hpp
	$(compile)
	
$(obj)tty.o : $(src)tty.cpp $(src)tty.hpp
	$(compile)
		
$(obj)parse.o : $(src)parse.cpp $(src)parse.hpp
	$(compile)
	
clean :
	rm -rf Objects Binaries
