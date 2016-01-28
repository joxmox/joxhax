cc = g++
cf =  -g3 -c -std=c++14 -fmax-errors=1 -I$(src)
compile = mkdir -p $(obj) ; $(cc) $(cf) $< -o $@
link = mkdir -p $(bin) ; g++ $+ -o $@ $(libs)
run = $<
lf =
libs = -lm

src = src/
bin = bin/
obj = obj/
tst = $(src)tst/

test :
	ls $(tst)

clean :
	rm -r $(obj)
	rm -r $(bin)
	
testExpression : $(bin)testExpression
	$(run)

$(bin)testExpression : $(obj)testExpression.o $(obj)Expression.o $(obj)tokenize.o
	$(link)
	
$(obj)testExpression.o : $(tst)testExpression.cpp $(src)Expression.hpp
	$(compile)
	
$(obj)Expression.o : $(src)Expression.cpp $(src)Expression.hpp $(src)tokenize.hpp
	$(compile)
	
$(obj)tokenize.o : $(src)tokenize.cpp $(src)tokenize.hpp
	$(compile)
	
$(obj)strings.o : $(src)strings.cpp $(src)strings.hpp
	$(compile)

	


