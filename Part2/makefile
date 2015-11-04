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
	
Acctest : $(bin)Acctest
	$(run)
	
Exchange : $(bin)Exchange
	$(run)
	
ShapeTest : $(bin)ShapeTest

clean :
	rm -rf build
	
$(bin)ShapeTest : $(obj)ShapeTest.o
	$(link)

$(obj)ShapeTest.o : $(app)ShapeTest.cpp $(lib)Shapes.hpp
	$(compile)
	
$(bin)Exchange : $(obj)Exchange.o
	$(link)
	
$(obj)Exchange.o : $(app)Exchange.cpp $(lib)Currency.hpp $(lib)Money.hpp
	$(compile)
	
$(bin)Acctest : $(obj)Acctest.o
	$(link)

$(obj)Acctest.o : $(app)Acctest.cpp $(lib)Acc.hpp
	$(compile)

$(bin)upg1 : $(obj)upg1.o
	$(link)

$(obj)upg1.o : $(app)upg1.cpp $(lib)Acc.hpp
	$(compile)
	
$(bin)upg2 : $(obj)upg2.o
	$(link)

$(obj)upg2.o : $(app)upg2.cpp $(lib)Trace.hpp
	$(compile)	
	

	

	


