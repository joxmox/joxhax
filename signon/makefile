cc = g++
cf =  -g3 -c -std=c++14 -fmax-errors=1 -I$(src)
compile = mkdir -p $(obj) ; $(cc) $(cf) $< -o $@
link = mkdir -p $(bin) ; g++ $+ -o $@ $(libs)
run = $<
lf =
libs = -lldap

src = src/
bin = bin/
obj = obj/
tst = $(src)tst/

ldaptest : $(bin)ldaptest
	$(run)
	
orig : $(bin)orig
	$(run)
	
apa : $(bin)apa
	$(run)

clean :
	rm -r $(obj)
	rm -r $(bin)
	

$(bin)ldaptest : $(obj)ldaptest.o
	$(link)
	
$(bin)apa : $(obj)apa.o $(obj)LdapConn.o
	$(link)
	
$(obj)ldaptest.o : $(src)ldaptest.cpp
	$(compile)
	
$(bin)orig : $(obj)orig.o
	$(link)
	
$(obj)orig.o : $(src)orig.cpp
	$(compile)
	
$(obj)LdapConn.o : $(src)LdapConn.cpp $(src)LdapConn.hpp
	$(compile)
	
$(obj)apa.o : $(src)apa.cpp $(src)LdapConn.hpp
	$(compile)
	

	


