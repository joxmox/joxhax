src = Source/
bin = Binaries/
obj = Objects/

inc = -I$(src)

cpp = g++ -c
lnk = g++
cf  = -std=c++14 -g -Wall -Wno-sign-compare -DDBG=1 -fmax-errors=1 $(inc)
lf  =
lib = -lncurses

compile = mkdir -p $(obj) && $(cpp) $(cf) $< -o $@
link    = mkdir -p $(bin) && $(lnk) $(lf) $+ -o $@ $(lib)


all : adam eve eve2

eve : $(bin)eve

eve2 : $(bin)eve2

adam : $(bin)adam

$(bin)adam : $(obj)Adam.o $(obj)Buffer.o $(obj)Position.o $(obj)tty.o ($obj)Screen.o
	$(link)
	
$(obj)main.o : $(src)main.cpp $(src)Adam.hpp
	$(compile)
	
$(obj)Adam.o : $(src)Adam.cpp $(src)Adam.hpp $(src)tty.hpp $(src)Buffer.hpp $(src)Position.hpp $(src)Screen.hpp
	$(compile)
	
$(obj)Buffer.o : $(src)Buffer.cpp $(src)Buffer.hpp $(src)Position.hpp $(src)tty.hpp
	$(compile)
	
$(obj)Position.o : $(src)Position.cpp $(src)Position.hpp
	$(compile)
	
$(obj)Screen.o : $(src)Screen.cpp $(src)Screen.hpp $(src)Position.hpp
	$(compile)
	
$(obj)tty.o : $(src)tty.cpp $(src)tty.hpp
	$(compile)
	
$(obj)parse.o : $(src)parse.cpp $(src)parse.hpp
	$(compile)

$(bin)eve : $(obj)eve.o $(obj)tty.o $(obj)parse.o
	$(link)

$(bin)eve2 : $(obj)eve2.o $(obj)tty.o $(obj)parse.o
	$(link)
	
$(obj)eve.o : $(src)eve.cpp $(src)tty.hpp
	$(compile)	
	
$(obj)eve2.o : $(src)eve2.cpp $(src)tty.hpp
	$(compile)
	
clean :
	rm -rf Objects Binaries
