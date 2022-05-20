cc = g++
flags = -w
src := $(wildcard ./*.cpp)
obj := $(patsubst ./%.cpp,./%.o,$(src))

main.exe: $(obj)

%.o: %.cpp
	$(cc) $(flags) -c $< -o $@

clean:
	rm *.o  