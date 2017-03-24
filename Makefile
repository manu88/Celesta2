CXX = g++ 

LDFLAGS  = -L/usr/local/lib/ -lGroundBase -lGroundBase-cpp
CXXFLAGS = -std=c++11 -I/usr/local/include/GroundBase/ -ICore/ -IGX/

CXXFLAGS+= -DTARGET_RASPBERRY_PI -I/opt/vc/include/
LDFLAGS+= -L/opt/vc/lib/ -lOpenVG  -lGLESv2 
#-lEGL


CORE_SRC = $(wildcard Core/*.cpp)

GX_SRC =  $(wildcard GX/*.cpp)


src = $(CORE_SRC) $(GX_SRC) CoreTest/GXTestMain.cpp
obj = $(src:.cpp=.o)


EXECUTABLE= TestCelesta

$(EXECUTABLE): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

.PHONY: clean
clean:
	rm -f $(obj) myprog

