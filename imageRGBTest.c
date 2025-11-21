// imageRGBTest - A program that performs some operations on RGB images.
//
// This program is an example use of the imageRGB module,
// a programming project for the course AED, DETI / UA.PT
//
// You may freely use and modify this code, NO WARRANTY, blah blah,
// as long as you give proper credit to the original and subsequent authors.
//
// The AED Team <jmadeira@ua.pt, jmr@ua.pt, ...>
// 2025

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "imageRGB.h"
#include "instrumentation.h"

int main(int argc, char* argv[]) {
  program_name = argv[0];
  if (argc != 1) {
    error(1, 0, "Usage: imageRGBTest");
  }

  ImageInit();

  // Creating and displaying some images

  printf("1) ImageCreate\n");
  Image white_image = ImageCreate(100, 100);
  // ImageRAWPrint(white_image);

  printf("2) ImageCreateChess(black)+ ImageSavePBM\n");
  Image image_chess_1 = ImageCreateChess(150, 120, 30, 0x000000);  // black
  // ImageRAWPrint(image_chess_1);
  ImageSavePBM(image_chess_1, "chess_image_1.pbm");

  printf("3) ImageCreateChess(red) + ImageSavePPM\n");
  Image image_chess_2 = ImageCreateChess(20, 20, 8, 0xff0000);  // red
  ImageRAWPrint(image_chess_2);
  ImageSavePPM(image_chess_2, "chess_image_2.ppm");

  printf("4) ImageCreateChess(all black)\n");
  Image black_image = ImageCreateChess(100, 100, 100, 0x000000);  // all black
  // ImageRAWPrint(black_image);
  ImageSavePBM(black_image, "black_image.pbm");

  printf("5) ImageCopy\n");
  Image copy_image = ImageCopy(image_chess_1);
  ImageRAWPrint(copy_image);
  if (copy_image != NULL) {
    ImageSavePBM(copy_image, "copy_image.pbm");
  }

  printf("6) ImageLoadPBM\n");
  Image image_1 = ImageLoadPBM("img/feep.pbm");
  ImageRAWPrint(image_1);

  printf("7) ImageLoadPPM\n");
  Image image_2 = ImageLoadPPM("img/feep.ppm");
  ImageRAWPrint(image_2);

  printf("8) ImageCreatePalete\n");
  Image image_3 = ImageCreatePalete(4 * 32, 4 * 32, 4);
  ImageSavePPM(image_3, "palete.ppm");

  // Self made tests from here on out

  printf("9) ImageIsEqual\n");
  Image feepImg = ImageLoadPPM("img/feep.ppm");
  Image copy_feep = ImageCopy(feepImg);

  ImageSavePPM(copy_feep, "img/copy_feep.ppm");

  if(ImageIsEqual(feepImg, copy_feep)) printf("Images are equal\n");
  else printf("Images are not equal\n");

  ImageDestroy(&copy_feep);

  printf("10) Rotate 90 degress CW\n");
  Image feep_90 = ImageRotate90CW(feepImg);
  ImageSavePPM(feep_90, "img/feep_90.ppm");

  if(ImageIsEqual(feepImg, feep_90)) printf("Images are equal\n");
  else printf("Images are not equal\n");

  ImageDestroy(&feep_90);

  printf("11) Rotate 180 degress CW\n");
  Image feep_180 = ImageRotate180CW(feepImg);
  ImageSavePPM(feep_180, "img/feep_180.ppm");

  if(ImageIsEqual(feepImg, feep_180)) printf("Images are equal\n");
  else printf("Images are not equal\n");

  ImageDestroy(&feep_180);

  printf("12) Recursive Region filling\n");
  Image feep_copy = ImageCopy(feepImg);
  ImageSavePPM(feep_copy, "img/feep_copy.ppm");

  int pixels_changed = ImageRegionFillingRecursive(feep_copy, 10, 3, 1);
  ImageSavePPM(feep_copy, "img/feep_copy_rec.ppm");
  printf("PIXELS CHANGED: %d\n", pixels_changed);

  if(ImageIsEqual(feepImg, feep_copy)) printf("Images are equal\n");
  else printf("Images are not equal\n");


  printf("13) Image Region Filling with STACK\n");
  Image feep_copy_stack = ImageCopy(feepImg);

  pixels_changed = ImageRegionFillingWithSTACK(feep_copy_stack, 10, 3, 147);
  ImageSavePPM(feep_copy_stack, "img/feep_copy_stack.ppm");
  printf("PIXELS CHANGED STACK: %d\n", pixels_changed);

  if(ImageIsEqual(feep_copy, feep_copy_stack)) printf("Images are equal\n");
  else printf("Images are not equal\n");

  ImageDestroy(&feep_copy);
  ImageDestroy(&feep_copy_stack);

  // ------------------------------------------
  // chess img
  printf("15) Image Segmentation\n");
  Image segmentationTestImg = ImageLoadPBM("chess_image_1.pbm");
  ImageSegmentation(segmentationTestImg, ImageRegionFillingRecursive);
  ImageSavePPM(segmentationTestImg, "img/segmentationTestImg.ppm");

  ImageDestroy(&segmentationTestImg);

  ImageDestroy(&white_image);
  ImageDestroy(&black_image);
  if (copy_image != NULL) {
    ImageDestroy(&copy_image);
  }
  ImageDestroy(&image_chess_1);
  ImageDestroy(&image_chess_2);
  ImageDestroy(&image_1);
  ImageDestroy(&image_2);
  ImageDestroy(&image_3);

  ImageDestroy(&feepImg);

  printf("14) Flood fill with queue\n");
  Image floodFillQueueTestImg = ImageLoadPBM("chess_image_1.pbm");
  ImageRegionFillingWithQUEUE(floodFillQueueTestImg, 15, 10, 0);
  ImageSavePPM(floodFillQueueTestImg, "floodFillQueueTestImg.ppm");

  // chess img
  printf("15) Image Segmentation\n");
  Image segmentationTestImg = ImageLoadPBM("chess_image_1.pbm");
  ImageSegmentation(segmentationTestImg, ImageRegionFillingRecursive);
  ImageSavePPM(segmentationTestImg, "segmentationTestImg.ppm");

  ImageDestroy(&floodFillQueueTestImg);
  ImageDestroy(&segmentationTestImg);

  return 0;
}