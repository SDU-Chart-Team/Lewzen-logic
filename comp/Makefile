cc = g++
flags = -w
src := $(wildcard ./*.cpp)
ifneq ($(cc), em++)
src := $(filter-out $(wildcard ./*_scriptable.cpp), $(src))
endif
obj := $(patsubst ./%.cpp,./%.o,$(src))

all: $(obj)

%.o: %.cpp %.h
	$(cc) $(flags) -c $< -o $@