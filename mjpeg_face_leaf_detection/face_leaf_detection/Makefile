CPP=g++
CFLAGS += `pkg-config --cflags opencv`
TAILFLAGS += -mfloat-abi=hard -mfpu=vfp
LFLAGS += `pkg-config --cflags --libs opencv`

facedetection:facedetection.o leafRecognition.o LeafClassifier.o calculate.o calculatorORleaf.o hullDetector.o v4l2lib.o
	$(CPP) -o $@ $^ $(LFLAGS)
facedetection.o:facedetection.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
leafRecognition.o:leafRecognition.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
LeafClassifier.o:LeafClassifier.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
calculate.o:calculate.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
calculatorORleaf.o:calculatorORleaf.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
hullDetector.o:hullDetector.cpp
	$(CPP) $(CFLAGS) -O2 -c $^ $(TAILFLAGS)
v4l2lib.o:v4l2lib.c v4l2lib.h
	$(CPP) -O2 -c $<

.PHONY: clean
clean:
	rm *.o facedetection *~ 
