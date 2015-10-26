<<<<<<< HEAD
<<<<<<< HEAD
src=Source/
bin=Binaries/
obj=Objects/

cpp=g++ -c
lnk=g++
cf=-std=c++14 -g -Wall -Wno-sign-compare -DDBG=1 -fmax-errors=1
lf=
lib=-lncurses

compile=$(cpp) $(cf) $< -o $@
link=$(lnk) $(lf) $+ -o $@ $(lib)


all : adam eve

eve : $(bin)eve

adam : $(bin)adam

$(bin)adam : $(obj)main.o $(obj)Adam.o $(obj)Buffer.o $(obj)Position.o $(obj)tty.o 
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

$(bin)eve : $(obj)eve.o $(obj)tty.o $(obj)parse.o
	$(link)
	
=======
=======
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
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

all : eve eve2

eve : $(bin)eve

eve2 : $(bin)eve2

$(bin)eve : $(obj)eve.o $(obj)tty.o $(obj)parse.o
	$(link)

<<<<<<< HEAD
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
=======
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
$(obj)eve.o : $(src)eve.cpp $(src)tty.hpp
	$(compile)
	
$(obj)tty.o : $(src)tty.cpp $(src)tty.hpp
	$(compile)
		
$(obj)parse.o : $(src)parse.cpp $(src)parse.hpp
	$(compile)
	
<<<<<<< HEAD
<<<<<<< HEAD
clean :
	rm -f $(obj)*.o $(bin)eve
=======
=======
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
$(bin)eve2 : $(obj)eve2.o $(obj)tty.o $(obj)parse.o
	$(link)
	
$(obj)eve2.o : $(src)eve2.cpp $(src)tty.hpp
	$(compile)
	
clean :
	rm -rf Objects Binaries
<<<<<<< HEAD
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
=======
>>>>>>> 6feec5f3b0332c5a334af3467111ad3190c93976
