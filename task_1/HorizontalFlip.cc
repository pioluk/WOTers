#include "HorizontalFlip.h"

void HorizontalFlip::transform(Image &image)
{
  // iterate through the lines of image
  for (int j = 0; j < image.get_surface()->h; ++j)
  {
    for (int i = 0; i < image.get_surface()->w/2; ++i)
    {
      // assign the values of last pixels in the line of image
      // to the first pixel values of temp
      uint32_t temp = image.get_pixel(i, j);
      image.set_pixel(i, j, image.get_pixel(image.get_surface()->w - 1 - i, j));
      image.set_pixel(image.get_surface()->w - 1 - i, j, temp);
    }
  }
}
