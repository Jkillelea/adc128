CXX      = g++
CFLAGS   = -I../..
LFLAGS   = -lwiringPi
LIB_OBJS = ../../adc128.o ../../i2cdevice.o

TARGETS = pi_example

.PHONY: all
all: $(TARGETS)

pi_example: pi_example.o $(LIB_OBJS)
	$(CXX) -o $@ $^ $(LFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

$(LIB_OBJS):
	make -C ../..

clean:
	rm -f *.o
	rm -f $(TARGETS)
	make -C ../.. clean

