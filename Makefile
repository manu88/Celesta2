CXX = g++ 

LDFLAGS  = -L/usr/local/lib/ -lGroundBase -lGroundBase-cpp
CXXFLAGS = -std=c++11 -I/usr/local/include/GroundBase/ -ICore/

CORE_SRC = Core/CLApplication.cpp \
		Core/CLApplicationDelegate.cpp \
		Core/FileSystem.cpp \
		Core/StringOperations.cpp \

src = $(CORE_SRC) CoreTest/main.cpp
obj = $(src:.cpp=.o)


EXECUTABLE= TestCelesta

$(EXECUTABLE): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

.PHONY: clean
clean:
	rm -f $(obj) myprog

