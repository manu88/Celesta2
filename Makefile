CXX = g++ 

LDFLAGS  = -L/usr/local/lib/ -lGroundBase -lGroundBase-cpp
CXXFLAGS = -std=c++11 -I/usr/local/include/GroundBase/ -ICore/ -IGX/ -IDisplay/

CXXFLAGS+= -DTARGET_RASPBERRY_PI -DHAVE_EGL -I/opt/vc/include/
LDFLAGS+= -L/opt/vc/lib/ -lOpenVG  -lGLESv2 -lEGL -lbcm_host


CORE_SRC    = $(wildcard Core/*.cpp)
GX_SRC      = $(wildcard GX/*.cpp)
DISPLAY_SRC = $(wildcard Display/*.cpp) $(wildcard Display/*/*.cpp) 

Base_src = $(CORE_SRC) $(GX_SRC) $(DISPLAY_SRC)

GX_src =  CoreTest/GXTestMain.cpp
Selector_TEST =  CoreTest/TestSelector.cpp

GX_obj = $(Base_src:.cpp=.o) $(GX_src:.cpp=.o)
SEL_obj = $(Base_src:.cpp=.o) $(Selector_TEST:.cpp=.o)



TEST_GX= GXTest
TEST_SEL = Selector



all: $(TEST_GX) $(TEST_SEL)

$(TEST_GX): $(GX_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

$(TEST_SEL): $(SEL_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(GX_obj) $(TEST_GX)
	rm -f $(GX_obj) $(TEST_SEL)
