cc = g++
cf =  -g3 -c -std=c++14 -fmax-errors=1
compile = mkdir -p $(obj) ; $(cc) $(cf) $< -o $@
link = mkdir -p $(bin) ; g++ $+ -o $@ $(libs)
lf =
libs = -lm

src = src/
bin = bin/
obj = obj/


#all : $(bin)dmpfil
#
#test3 : $(bin)test3
#
#condtest : $(bin)condtest
#	$(bin)condtest
#
#$(bin)condtest : $(obj)condtest.o $(obj)Condition.o
#	$(link)
#	
#$(obj)condtest.o : $(src)condtest.cpp $(src)Condition.hpp
#	$(compile)
#	
#$(obj)Condition.o : $(src)Condition.cpp $(src)Condition.hpp
#	$(compile)
#
#
#$(bin)dmpfil : $(obj)dmpfil.o $(obj)dfloat.o 
#	$(link)
#	
#$(obj)dmpfil.o : $(src)dmpfil.cpp $(src)dfloat.hpp $(src)MapFile.hpp $(src)strings.hpp
#	$(compile)
#
#$(obj)dfloat.o : $(src)dfloat.cpp $(src)dfloat.hpp
#	$(compile)
#	
#$(obj)strings.o : $(src)strings.cpp
#	$(compile)
#	
#$(bin)test3 : $(obj)test3.o $(obj)Condition.o $(obj)strings.o
#	$(link)
#	
#$(obj)test3.o : $(src)test3.cpp $
#	$(compile)

clean :
	rm -r $(obj)
	rm -r $(bin)

test : $(bin)test
	$(bin)test
	
test4 : $(bin)test4
	$(bin)test4

$(bin)test : $(obj)test.o $(obj)strings.o $(obj)Condition.o
	$(link)
	
test2 : $(bin)test2
	$(bin)test2

$(bin)test2 : $(obj)test2.o 
	$(link)
	
test4 : $(bin)test4
	$(bin)test4

$(bin)test3 : $(obj)test3.o 
	$(link)
	
$(obj)%.o : $(src)%.cpp
	$(compile)
	
$(bin)% : $(obj)%.o
	$(link)


