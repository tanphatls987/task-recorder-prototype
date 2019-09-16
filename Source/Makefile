.PHONY = all clean print run

CC = g++ 
CFLAGS = -Wall -std=c++11 -g `wx-config --cxxflags --libs` 

LINKERFLAG = -lm

SRCS := $(wildcard *.cc)
BINS := $(patsubst %.cc, %.o, ${SRCS})

all: TaskRecorder

${BINS} : %.o : %.cc %.h
	${CC} -c $^ ${CFLAGS}

clean: 
	@echo "Cleaning object file"
	rm -rvf *.o ${BINS}
TaskRecorder: TaskButtonDropDown.o TRTask.o TaskPanel.o TaskListToolPanel.o TaskListPanel.o TaskFileHandler.o TaskHandler.o  BuildTaskValidator.o BuildTaskPanel.o BuildTaskDialog.o TaskRecorderMainFrame.o TaskRecorderApp.o
	${CC} -o TaskRecorder $^ ${CFLAGS} 

