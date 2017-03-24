CXX = g++ 

LDFLAGS  = -L/usr/local/lib/ -lGroundBase -lGroundBase-cpp
CXXFLAGS = -std=c++11 -I/usr/local/include/GroundBase/ -ICore/ -IGX/ -IDisplay/

CXXFLAGS+= -DTARGET_RASPBERRY_PI -DHAVE_EGL -I/opt/vc/include/
LDFLAGS+= -L/opt/vc/lib/ -lOpenVG  -lGLESv2 -lEGL -lbcm_host


CORE_SRC    = $(wildcard Core/*.cpp)
GX_SRC      = $(wildcard GX/*.cpp)
DISPLAY_SRC = $(wildcard Display/*.cpp) $(wildcard Display/*/*.cpp) 

src = $(CORE_SRC) $(GX_SRC) $(DISPLAY_SRC) CoreTest/GXTestMain.cpp
obj = $(src:.cpp=.o)


EXECUTABLE= TestCelesta

$(EXECUTABLE): $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

.PHONY: clean
clean:
	rm -f $(obj) myprog

