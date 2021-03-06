#include "Image.h"
#include "Parser.h"
#include "Operations.h"
#include "FreqDomain.h"
#include "Histogram.h"
#include <iostream>
#include <string>
#include <cassert>

#ifdef _SPEED_TEST
#include <sys/time.h>
#include <cstdint>
#include <iomanip>
static uint64_t now() {
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    abort();

  return tv.tv_sec * 1000000ULL + tv.tv_usec;
}
#endif

using namespace std;

int main(int argc, char** argv)
{

  bool imageChanged = true;

  using namespace std;

  Parser p(argc, argv);

  Image img(p.getFilename());
  Histogram hist(img);
  Histogram::Channel channel = Histogram::Channel::ALL;

  Operation *o = nullptr;

  if (p.setChannel()) {
    channel = (Histogram::Channel) p.getChannel();
  }
  else
  {
    channel = Histogram::Channel::ALL;
  }

  if (img.get_surface()->format->BitsPerPixel == 8) {
    channel = Histogram::Channel::R;
  }

  if (p.setBrightness()) {
    o = new BrightnessAdjustment(p.getBrightnessValue());
  }

  if (p.setResize()) {
    o = new Resize(p.getResizeValue());
  }

  if (p.setContrast()) {
    o = new ContrastAdjustment(p.getContrastValue());
  }

  if (p.setNegative()) {
    o = new Negative();
  }

  if (p.setHflip()) {
    o = new HorizontalFlip();
  }

  if (p.setVflip()) {
    o = new VerticalFlip();
  }

  if (p.setDflip()) {
    o = new DiagonalFlip();
  }

  if (p.setCmean()) {
    o = new ContraharmonicMeanFilter(p.getCmeanValue());
  }

  if (p.setAlpha()) {
    o = new AlphaTrimmedMeanFilter(p.getAlphaValue());
  }

  if (p.setCmean()) {
    o = new ContraharmonicMeanFilter(p.getCmeanValue());
  }

  if (p.setLowPass()) {
    o = new LowPassFilter();
  }

  if (p.setRosenfeld()) {
    o = new RosenfeldOperator(p.getRosenfeldP());
  }

  if (p.setErosion()) {
    o = new Erosion(p.getMask());
  }

  if (p.setDilation()) {
    o = new Dilation(p.getMask());
  }

  if (p.setOpening()) {
    o = new Opening(p.getMask());
  }

  if (p.setClosing()) {
    o = new Closing(p.getMask());
  }

  if (p.setHMT()) {
    o = new HMT(p.getMask());
  }

  if (p.setThinning()) {
    o = new Thinning();
  }

  if (p.setPruning()) {
    o = new Pruning(p.getPruningValue());
  }

  if (p.setRegionGrowing()) {
    int th = -1; // search for mean to calulate threshold value
    if (p.setThreshold()) {
      th = p.getTrescholdValue();
    }
    o = new RegionGrowing(p.getRegionValue(), th);

  }

  if (p.setRaleigh()) {
    // if (channel == Histogram::Channel::ALL && img.get_surface()->format->BitsPerPixel != 8)
    // {
    //   std::cerr << "You must specify channel (--channel)" << std::endl;
    //   exit(1);
    // }
    // else if (img.get_surface()->format->BitsPerPixel == 8)
    // {
    //   channel = Histogram::Channel::R;
    // }

    o = new RaleighFPDF(channel, p.getRaleighMinMax());
  }

  if (p.useFreqDomain()) {
    FreqDomain freqplane(&img);
    if (p.useFreqDomain()) {
      if (p.setDFT()) {
        freqplane.DFT();
      } else {
        freqplane.FFT();
      }
    }
    freqplane.save_magnitude_spectrum("mag.bmp");
    freqplane.save_phase_shift_spectrum("phase_shift.bmp");

    if (p.setFDHighPass()) {
    	freqplane.highPass(p.getFDHighPass());
  	}
	if (p.setFDLowPass()) {
    	freqplane.lowPass(p.getFDLowPass());
  	}
 	if (p.setFDBandPass()) {
    	freqplane.bandPass(p.getFDBandPass().first, p.getFDBandPass().second);
  	}
 	if (p.setFDBandCut()) {
    	freqplane.bandCut(p.getFDBandCut().first, p.getFDBandCut().second);
  	}
 	if (p.setFDDirected()) {
    	freqplane.directed(p.getFDDirected().first, p.getFDDirected().second);
  	}
 	if (p.setFDPhaseModify()) {
    	freqplane.phaseModify(p.getFDPhaseModify().first, p.getFDPhaseModify().second);
    }
    freqplane.save_magnitude_spectrum("mag_filtered.bmp");
    freqplane.save_phase_shift_spectrum("phase_shift_filtered.bmp");

    if (p.setDFT()) {
      freqplane.IDFT();
    } else {
      freqplane.IFFT();
    }
    img.save(p.getOutFilename());
    imageChanged = false;
  }

  double result = 0.0;

  if (p.setMse()) {
    imageChanged = false;
    Image filtered(p.getMseFilename());
    img.perform_operation(new MeanSquareError(&filtered, &result));
    cout << result << endl;
  }

  if (p.setPmse()) {
    imageChanged = false;
    Image filtered(p.getPmseFilename());
    img.perform_operation(new PeakMeanSquareError(&filtered, &result));
    cout << result << endl;
  }

  if (p.setSnr()) {
    imageChanged = false;
    Image filtered(p.getSnrFilename());
    img.perform_operation(new SignalToNoiseRatio(&filtered, &result));
    cout << result << endl;
  }
  if (p.setPsnr()) {
    imageChanged = false;
    Image filtered(p.getPsnrFilename());
    img.perform_operation(new PeakSignalToNoiseRatio(&filtered, &result));
    cout << result << endl;
  }

  if (p.setMd()) {
    imageChanged = false;
    Image filtered(p.getMdFilename());
    img.perform_operation(new MaxDifference(&filtered, &result));
    cout << result << endl;
  }

  if (p.setCmeanh()) {
    imageChanged = false;
    cout << hist.cmean(channel) << endl;
  }

  if (p.setCvariance()) {
    imageChanged = false;
    cout << hist.cvariance(channel) << endl;
  }

  if (p.setCstdev()) {
    imageChanged = false;
    cout << hist.cstdev(channel) << endl;
  }

  if (p.setCvarcoii()) {
    imageChanged = false;
    cout << hist.cvarcoii(channel) << endl;
  }

  if (p.setCvarcoi()) {
    imageChanged = false;
    cout << hist.cvarcoi(channel) << endl;
  }

  if (p.setCasyco()) {
    imageChanged = false;
    cout << hist.casyco(channel) << endl;
  }

  if (p.setCflatco()) {
    imageChanged = false;
    cout << hist.cflatco(channel) << endl;
  }

  if (p.setCentropy()) {
    imageChanged = false;
    cout << hist.centropy(channel) << endl;
  }

  if (p.setHistogram()) {
    // if (channel == Histogram::Channel::ALL && img.get_surface()->format->BitsPerPixel != 8)
    // {
    //   std::cerr << "You must specify channel (--channel)" << std::endl;
    //   exit(1);
    // }
    if (img.get_surface()->format->BitsPerPixel == 8) {
      channel = Histogram::Channel::R;
    }

    imageChanged = false;
    hist.save_as_image(channel, p.getHistogramFilename());
  }

  if (imageChanged) {
    assert(o != nullptr);
  }

#ifdef _SPEED_TEST
  uint64_t timer = now();
#endif
  if (imageChanged) {
    img.perform_operation(o);
  }

#ifdef _SPEED_TEST
  timer = now() - timer;
  printf("%gs\n", (double)timer/1e6);
#endif

#ifndef _SPEED_TEST // saving the file during speed test is just the waste of time
  if (imageChanged) {
    img.save(p.getOutFilename());
  }
#endif

  return 0;
}
