#ifndef __PARSER_H
#define __PARSER_H

#include <boost/program_options.hpp>
#include <utility>
#include <tuple>
#include <vector>

namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

namespace po = boost::program_options;

class Parser{
    public:
        Parser(int &argc, char** argv);

    private:
        po::options_description desc;
        po::variables_map vm;

    public:

        std::string getFilename();
        std::string getOutFilename();
        bool setBrightness();
        double getBrightnessValue();
        bool setContrast();
        double getContrastValue();
        bool setNegative();

        bool setHflip();
        bool setVflip();
        bool setDflip();
        bool setResize();
        std::tuple<double, int, int> getResizeValue();

        bool setAlpha();
        int getAlphaValue();
        bool setCmean();
        double getCmeanValue();

        bool setLowPass();
        bool setRosenfeld();
        int getRosenfeldP();

        bool setMse();
        std::string getMseFilename();
        bool setPmse();
        std::string getPmseFilename();
        bool setSnr();
        std::string getSnrFilename();
        bool setPsnr();
        std::string getPsnrFilename();
        bool setMd();
        std::string getMdFilename();

        bool setRaleigh();
        std::pair<int, int> getRaleighMinMax();

        bool setChannel();
        int getChannel();

        bool setCmeanh();
        bool setCvariance();
        bool setCstdev();
        bool setCvarcoi();
        bool setCvarcoii();
        bool setCasyco();
        bool setCflatco();
        bool setCentropy();

        bool setErosion();
        bool setDilation();
        bool setOpening();
        bool setClosing();
        bool setHMT();
        int getMask();
        bool setThinning();
        bool setPruning();
        int getPruningValue();

        bool setHistogram();
        std::string getHistogramFilename();

        bool setRegionGrowing();
        int getRegionValue();
        bool setThreshold();
        int getTrescholdValue();

        bool useFreqDomain();
        bool setDFT();
        bool setFFT();

        bool setFDLowPass();
        double getFDLowPass();
        bool setFDHighPass();
        double getFDHighPass();
        bool setFDBandPass();
        std::pair<double, double> getFDBandPass();
        bool setFDBandCut();
        std::pair<double, double> getFDBandCut();
        bool setFDDirected();
        std::pair<double, double> getFDDirected();
        bool setFDPhaseModify();
        std::pair<int, int> getFDPhaseModify();

};

#endif
