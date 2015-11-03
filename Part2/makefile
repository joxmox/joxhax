app = src/app/
lib = src/lib/
obj = build/objs/
bin = build/bin/
tst = src/tst/

inc = -I$(lib)

cpp = g++
cfl = -std=c++14 -g -c -Wall -fmax-errors=1 -Wno-sign-compare $(inc)
lnk = g++
lfl =

compile = mkdir -p $(obj); $(cpp) $(cfl) $< -o $@
link =    mkdir -p $(bin); $(lnk) $(lfl) $+ -o $@
run =     $<

all : upg1 upg2

upg1 : $(bin)upg1
	$(run)
	
upg2 : $(bin)upg2
	$(run)

clean :
	rm -rf build

$(bin)upg1 : $(obj)upg1.o
	$(link)

$(obj)upg1.o : $(app)upg1.cpp $(lib)Acc.hpp
	$(compile)
	
$(bin)upg2 : $(obj)upg2.o
	$(link)

$(obj)upg2.o : $(app)upg2.cpp $(lib)Trace.hpp
	$(compile)	
	

	

	


