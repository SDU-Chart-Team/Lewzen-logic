cc = g++
flags = -w
lib = release/lewzen-core.lib
objs = register.o \
	canvas.o \
	comp_factory.o \
	comp.o \
	comp_module.o \
	utils.o

wasm: sub_all $(objs)
	em++ $(flags) --bind -O3 -o wasm.js wasm.cpp $(shell dir . /S /b | findstr /i ".*\.o$") $(lib)

test: sub_all $(objs)
	$(cc) $(flags) -o test.exe test.cpp $(shell dir . /S /b | findstr /i ".*\.o$") $(lib)

sub_all: $(objects)
	cd comp && make
	cd comp_module && make
	cd comp_custom && make
	cd utils && make
register.o: register.h register.cpp
	$(cc) $(flags) -c register.cpp
canvas.o: canvas.h canvas.cpp
	$(cc) $(flags) -c canvas.cpp
comp_factory.o: comp_factory.h comp_factory.cpp
	$(cc) $(flags) -c comp_factory.cpp
comp.o: comp.h comp.cpp
	$(cc) $(flags) -c comp.cpp
comp_module.o: comp_module.h comp_module.cpp
	$(cc) $(flags) -c comp_module.cpp
utils.o: utils.h utils.cpp
	$(cc) $(flags) -c utils.cpp

clean:
	del /S *.o
	del test.exe
	del wasm.js
	del wasm.wasm