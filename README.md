# FaceRecog
OpenCV + libfacedetection + dlib + CUDA Face Recognition Demo  
  
# Environment Configuration
***OpenCV 4.7.0***  
[https://opencv.org/releases/](https://opencv.org/releases/)  
Download **opencv-4.7.0-windows.exe**  
Extract `opencv` folder to your prefer location.  
Files in `opencv` will be included in the opencv property of project.  
  
***CUDA Toolkit 12.1 Update 1***  
[https://developer.nvidia.com/cuda-downloads](https://developer.nvidia.com/cuda-downloads)  
  
***cuDNN v8.9.1 (May 5th, 2023), for CUDA 12.x***  
[https://developer.nvidia.com/rdp/cudnn-download](https://developer.nvidia.com/rdp/cudnn-download)  
  
***Dlib v19.24***  
[http://dlib.net/](http://dlib.net/)  
  
1. Download `dlib-19.24.zip` and extract `dlib-19.24` to the project root folder. ( In the same folder as `FaceRecog`, `libfacedetection`, `EZ_Source`. )  
![Imgur Image](https://imgur.com/CJImt2N.jpg)  
  
2. Create a new folder named `build` under `dlib-19.24`.  
And then create a new folder named `x64` under `build`.  
  
3. 
- 3.1. Use CMake GUI to generate Visual Studio project.  
![Imgur Image](https://imgur.com/zWAVF5m.jpg)  
![Imgur Image](https://imgur.com/ReFzrGw.jpg)   
Or  
- 3.2. Use Command Line, cd to `dlib-19.24\build\x64` folder and execute command:  
`cmake -G "Visual Studio 16 2019" -A x64 -T host=x64 ../../dlib`  
  
4. Open VS project in `dlib-19.24\build\x64`. Build '**Release**' version.  
  
# Properties
Make sure all directories in properties are correct.  
![Imgur Image](https://imgur.com/tRDMzN3.jpg)  
  
# Usage
1. Put the face pictures that want to be recognized into the folder: `faces`.  
This folder should be in the same directory as the main program.  
Like: `N:\Development\FaceRecog\FaceRecog\x64\Release\faces`  
  
2. Open `FaceRecog\FaceRecog.sln` and make a **Release x64** build.  
  
# Demo
![Imgur Image](https://imgur.com/yNag7LV.jpg)  
  
