CXX = g++ 

LDFLAGS  = -L/usr/local/lib/ -lGroundBase -lGroundBase-cpp
CXXFLAGS = -g -std=c++11 -I/usr/local/include/GroundBase/ -I/usr/include/freetype2/ -ICore/ -IGX/ -IDisplay/ -IData -IFonts -IUI

CXXFLAGS+= -DDEBUG -DTARGET_RASPBERRY_PI -DHAVE_EGL -I/opt/vc/include/
LDFLAGS+= -L/opt/vc/lib/ -lOpenVG  -lGLESv2 -lEGL -lbcm_host -lfreetype


CORE_SRC    = $(wildcard Core/*.cpp)
GX_SRC      = $(wildcard GX/*.cpp)
FONT_SRC    = $(wildcard Fonts/*.cpp)
DISPLAY_SRC = $(wildcard Display/*.cpp) $(wildcard Display/*/*.cpp) 
DRIVERS_SRC = $(wildcard Drivers/*.cpp)
UI_SRC      = $(wildcard UI/*.cpp)
Base_src = $(CORE_SRC) $(GX_SRC) $(DISPLAY_SRC) $(FONT_SRC) $(DRIVERS_SRC) $(UI_SRC)

GX_src =  CoreTest/GXTestMain.cpp
Selector_TEST =  CoreTest/TestSelector.cpp
Font_src = CoreTest/TestFonts.cpp
UI_TEST = CoreTest/UITestMain.cpp CoreTest/UITerm.cpp CoreTest/UIWinManager.cpp

GX_obj = $(Base_src:.cpp=.o) $(GX_src:.cpp=.o)
SEL_obj = $(Base_src:.cpp=.o) $(Selector_TEST:.cpp=.o)
FONT_obj = $(Base_src:.cpp=.o) $(Font_src:.cpp=.o)
UI_obj = $(Base_src:.cpp=.o) $(UI_TEST:.cpp=.o)

TEST_GX= GXTest
TEST_SEL = Selector
TEST_FONT = FontTest
TEST_UI = UITest

all: $(TEST_GX) $(TEST_SEL) $(TEST_FONT) $(TEST_UI)

$(TEST_UI): $(UI_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_GX): $(GX_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) 

$(TEST_SEL): $(SEL_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_FONT): $(FONT_obj)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(GX_obj) $(TEST_GX)
	rm -f $(GX_obj) $(TEST_SEL)
	rm -f CoreTest/*.o
