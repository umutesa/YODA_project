# YODA PROJECT (Your Own Digital Accerlerator)

 This is the Formal Git Repository for the YODA Project

 # Tools

 <p style="display: flex; gap: 50px;">
  <img src="https://www.svgrepo.com/show/373947/opencl.svg" alt="OpenCL" width="100" height="120"/>
  <img src="https://www.svgrepo.com/show/354139/opencv.svg" alt="OpenCV" width="100" height="120"/>
  <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS8dzZBc0u9kuqE-Fn3vrNDadX-TNzA5vF_gA&s" alt="C++" width="100" height="120"/>
</p>


## Median Filter:


The median filter is a non-linear digital filtering technique, often used to remove noise from an image or signal. Such noise reduction is a typical pre-processing step to improve the results of later processing (for example, edge detection on an image). Median filtering is very widely used in digital image processing because, under certain conditions, it preserves edges while removing noise (but see the discussion below), also having applications in signal processing.

To demonstrate, using a window size of three with one entry immediately preceding and following each entry, a median filter will be applied to the following simple one-dimensional signal:

x = (2, 3, 80, 6, 2, 3). <br />
So, the median filtered output signal y will be: <br />

y1 = med(2, 3, 80) = 3, (already 2, 3, and 80 are in the increasing order so no need to arrange them) <br />
y2 = med(3, 80, 6) = med(3, 6, 80) = 6, (3, 80, and 6 are rearranged to find the median) <br />
y3 = med(80, 6, 2) = med(2, 6, 80) = 6, <br />
y4 = med(6, 2, 3) = med(2, 3, 6) = 3, <br />
i.e. y = (3, 6, 6, 3) <br />

### Added Noise unsing Matlab:

#### Salt annd Peper Noise 

![Screenshot](saltpepper.PNG)

#### Speckle Noise

![Screenshot](speckle.PNG)

#### Noisy Image :

![Screenshot](speckle.PNG)

#### Denoise Image :

![Screenshot](original_image.PNG)

#### Edge Detection:Sobel Filter

Edge detection includes a variety of mathematical methods that aim at identifying edges, curves in a digital image at which the image brightness changes sharply or, more formally, has discontinuities.
Sobel Edge detection is a widely used algorithm of edge detection in image processing. Along with Canny and Prewitt, Sobel is one of the most popular edge detection algorithms used in today's technology.


### The Math Behind the Sobel Algorithm
When using Sobel Edge Detection, the image is processed in the X and Y directions separately first, and then combined together to form a new image which represents the sum of the X and Y edges of the image. However, these images can be processed separately as well. This will be covered later in this document.

When using a Sobel Edge Detector, it is first best to convert the image from an RGB scale to a Grayscale image. Then from there, we will use what is called kernel convolution. A kernel is a 3 x 3 matrix consisting of differently (or symmetrically) weighted indexes. This will represent the filter that we will be implementing for an edge detection.

When we want to scan across the X direction of an image for example, we will want to use the following X Direction Kernel to scan for large changes in the gradient. Similarly, when we want to scan across the Y direction of an image, we could also use the following Y Direction Kernel to scan for large gradients as well.

#### Orginal Image

![Screenshot](VGA1.png)

#### Atter Sobel Filter

![Screenshot](VGA.png)


