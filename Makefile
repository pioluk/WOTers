CXX?=g++
CXXFLAGS=-g -O2 -march=native -std=c++11 -Wall -Wextra -pedantic -fopenmp
MAIN_CFLAGS=
LDFLAGS=-fopenmp
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image
BOOST_LDFLAGS=-lboost_program_options
OBJECTS= \
	main.o \
	Parser.o \
	Histogram.o \
	Image.o \
	Operation.o \
	BrightnessAdjustment.o \
	ContrastAdjustment.o \
	DiagonalFlip.o \
	VerticalFlip.o \
	HorizontalFlip.o \
	Negative.o \
	Resize.o \
	AlphaTrimmedMeanFilter.o \
	ContraharmonicMeanFilter.o \
	MeanSquareError.o \
	PeakMeanSquareError.o \
	SignalToNoiseRatio.o \
	PeakSignalToNoiseRatio.o \
	MaxDifference.o \
	RaleighFPDF.o \
	RosenfeldOperator.o \
	LowPassFilter.o \
	ConvertToGrayscale.o \
	Binarize.o \
	Erosion.o \
	Dilation.o \
	Opening.o \
	Closing.o \
	HMT.o \
	Thinning.o \
	RegionGrowing.o \
	Pruning.o \
	ComplexImage.o \
	DFT.o \
	FFT.o \
	FFT1D.o \
	FreqDomain.o
EXECUTABLE=imgproc

all: $(OBJECTS) $(EXECUTABLE)

speed_test: MAIN_CFLAGS+= -D_SPEED_TEST
speed_test: EXECUTABLE=program2_st
speed_test: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) -o $(EXECUTABLE) $(OBJECTS) $(SDL_CFLAGS) $(LDFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

main.o : src/main.cc
	$(CXX) $(CXXFLAGS) $(MAIN_CFLAGS) -c src/main.cc $(SDL_CFLAGS) $(SDL_LDFLAGS) $(BOOST_LDFLAGS)

Parser.o : src/Parser.h src/Parser.cc
	$(CXX) $(CXXFLAGS) -c src/Parser.cc $(BOOST_LDFLAGS)

Histogram.o: src/Histogram.cc src/Histogram.h
	$(CXX) $(CXXFLAGS) -c src/Histogram.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Image.o : src/Image.cc src/Image.h
	$(CXX) $(CXXFLAGS) -c src/Image.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Operation.o : src/Operation.cc src/Operation.h
	$(CXX) $(CXXFLAGS) -c src/Operation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

BrightnessAdjustment.o : src/BrightnessAdjustment.cc src/BrightnessAdjustment.h
	$(CXX) $(CXXFLAGS) -c src/BrightnessAdjustment.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Negative.o : src/Negative.cc src/Negative.h
	$(CXX) $(CXXFLAGS) -c src/Negative.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContrastAdjustment.o : src/ContrastAdjustment.cc src/ContrastAdjustment.h
	$(CXX) $(CXXFLAGS) -c src/ContrastAdjustment.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

VerticalFlip.o : src/VerticalFlip.cc src/VerticalFlip.h
	$(CXX) $(CXXFLAGS) -c src/VerticalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

HorizontalFlip.o : src/HorizontalFlip.cc src/HorizontalFlip.h
	$(CXX) $(CXXFLAGS) -c src/HorizontalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

DiagonalFlip.o: src/DiagonalFlip.cc src/DiagonalFlip.h
	$(CXX) $(CXXFLAGS) -c src/DiagonalFlip.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Resize.o : src/Resize.cc src/Resize.h
	$(CXX) $(CXXFLAGS) -c src/Resize.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ContraharmonicMeanFilter.o : src/ContraharmonicMeanFilter.cc src/ContraharmonicMeanFilter.h
	$(CXX) $(CXXFLAGS) -c src/ContraharmonicMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

AlphaTrimmedMeanFilter.o : src/AlphaTrimmedMeanFilter.cc src/AlphaTrimmedMeanFilter.h
	$(CXX) $(CXXFLAGS) -c src/AlphaTrimmedMeanFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

MeanSquareError.o : src/MeanSquareError.cc src/MeanSquareError.h
	$(CXX) $(CXXFLAGS) -c src/MeanSquareError.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

PeakMeanSquareError.o : src/PeakMeanSquareError.cc src/PeakMeanSquareError.h
	$(CXX) $(CXXFLAGS) -c src/PeakMeanSquareError.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

SignalToNoiseRatio.o : src/SignalToNoiseRatio.cc src/SignalToNoiseRatio.h
	$(CXX) $(CXXFLAGS) -c src/SignalToNoiseRatio.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

PeakSignalToNoiseRatio.o : src/PeakSignalToNoiseRatio.cc src/PeakSignalToNoiseRatio.h
	$(CXX) $(CXXFLAGS) -c src/PeakSignalToNoiseRatio.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

MaxDifference.o : src/MaxDifference.cc src/MaxDifference.h
	$(CXX) $(CXXFLAGS) -c src/MaxDifference.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

RaleighFPDF.o : src/RaleighFPDF.cc src/RaleighFPDF.h
	$(CXX) $(CXXFLAGS) -c src/RaleighFPDF.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

RosenfeldOperator.o : src/RosenfeldOperator.cc src/RosenfeldOperator.h
	$(CXX) $(CXXFLAGS) -c src/RosenfeldOperator.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

LowPassFilter.o : src/LowPassFilter.cc src/LowPassFilter.h
	$(CXX) $(CXXFLAGS) -c src/LowPassFilter.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ConvertToGrayscale.o : src/ConvertToGrayscale.cc src/ConvertToGrayscale.h
	$(CXX) $(CXXFLAGS) -c src/ConvertToGrayscale.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Binarize.o : src/Binarize.cc src/Binarize.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Binarize.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Erosion.o : src/Erosion.cc src/Erosion.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Erosion.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Dilation.o : src/Dilation.cc src/Dilation.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Dilation.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Opening.o : src/Opening.cc src/Opening.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Opening.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Closing.o : src/Closing.cc src/Closing.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Closing.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

HMT.o : src/HMT.cc src/HMT.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/HMT.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Thinning.o : src/Thinning.cc src/Thinning.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Thinning.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

Pruning.o : src/Pruning.cc src/Pruning.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/Pruning.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

RegionGrowing.o : src/RegionGrowing.cc src/RegionGrowing.h src/StructuralElements.h
	$(CXX) $(CXXFLAGS) -c src/RegionGrowing.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

ComplexImage.o : src/ComplexImage.cc src/ComplexImage.h
	$(CXX) $(CXXFLAGS) -c src/ComplexImage.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

DFT.o : src/DFT.cc src/DFT.h
	$(CXX) $(CXXFLAGS) -c src/DFT.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

FFT.o : src/FFT.cc src/FreqDomain.h
	$(CXX) $(CXXFLAGS) -c src/FFT.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

FFT1D.o : src/FFT1D.cc src/FreqDomain.h
	$(CXX) $(CXXFLAGS) -c src/FFT1D.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

FreqDomain.o : src/FreqDomain.cc src/FreqDomain.h
	$(CXX) $(CXXFLAGS) -c src/FreqDomain.cc $(SDL_CFLAGS) $(SDL_LDFLAGS)

.PHONY : clean
clean:
	rm $(EXECUTABLE) $(OBJECTS)

.PHONY : clean_compilation_type
clean_compilation_type :
	rm main.o
# vim: set tw=0:
