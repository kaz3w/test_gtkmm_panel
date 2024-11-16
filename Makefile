TARGET = panel
CXX = g++
CXXFLAGS = -I/usr/include/gtk-3.0 -Wall -g `pkg-config --cflags --libs gtk+-3.0 sigc++-2.0 gtkmm-3.0 glibmm-2.4 glib-2.0`

SRCS = button_exit.cpp  button_stub.cpp  button_widget.cpp  button_wifi.cpp button_main.cpp \
	main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

