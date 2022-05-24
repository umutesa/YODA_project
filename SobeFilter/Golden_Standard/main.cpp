nclude "SobelFilter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <cstring>
#include "common/FreeImage/include/FreeImage.h"

// Creates a new Wrapper for the OpenCL program with the
// provided OpenCL kernel filename
SobelFilter::SobelFilter()
{
        this->GetPlatforms();

        this->GetDevices();

        this->CreateContext(0);

        this->CreateCommandQueue();

        this->CreateProgram("SobelFilter.cl");
}

// Destructor to cleanup the SobelFilter object
SobelFilter::~SobelFilter()
{
        if (this->Queue != 0)
        {
                clReleaseCommandQueue(this->Queue);
        }

        if (this->Kernel != 0)
        {
                clReleaseKernel(this->Kernel);
        }

        if (this->Program != 0)
        {
                clReleaseProgram(this->Program);
        }
    
    
    
    
        if (this->Context != 0)
        {
                clReleaseContext(this->Context);
        }

        if (this->InputImage != nullptr)
        {
                clReleaseMemObject(this->InputImage);
        }

        if (this->OutputImage != nullptr)
        {
                clReleaseMemObject(this->OutputImage);
        }
}



int SobelFilter::GetPlatforms()
{
        // Declare some temp variables
        cl_int ErrNum;
        cl_uint NumberOfPlatforms;

        // This will retrieve the number of platforms
        ErrNum = clGetPlatformIDs(0, nullptr, &NumberOfPlatforms);

        if (ErrNum != CL_SUCCESS || NumberOfPlatforms <= 0)
        {
                std::cerr << "Failed to find any OpenCL platforms." << std::endl;
                return -1;
        }

        // Allocate space on the heap to hold the platform Ids
        cl_platform_id * PlatformIdsPtr = new cl_platform_id[NumberOfPlatforms];

        // Gets the platform Ids and assign to the above array
        ErrNum = clGetPlatformIDs(NumberOfPlatforms, PlatformIdsPtr, NULL);

        // Add the elements from the array
        for (unsigned int i = 0; i < NumberOfPlatforms; i++)
        {
                this->Platforms.push_back(PlatformIdsPtr[i]);
        }

        // Cleanup pointer
        delete[] PlatformIdsPtr;
        PlatformIdsPtr = nullptr;

        return EXIT_SUCCESS;
}

{
        cl_int ErrNum;

        // Will hold the device count for each platform
        cl_uint DeviceCount;

        // Iterate the platforms and get each of their devices
        for (unsigned int i = 0; i < this->Platforms.size(); i++)
        {
                // Gets the number of devices on the platform
                ErrNum = clGetDeviceIDs(
                        this->Platforms.at(i),
                        CL_DEVICE_TYPE_ALL,
                        0,
                        nullptr,
                        &DeviceCount
                );

                if (ErrNum != CL_SUCCESS || DeviceCount == 0)
                {
                        std::cerr << "Could find any devices on platform: " << this->Platforms.at(i) << std::endl;
                }

                // Declare an array on the heap to hold the device Ids
                cl_device_id * DeviceIdsPtr = new cl_device_id[DeviceCount];

                // Get the device Ids
                ErrNum = clGetDeviceIDs(this->Platforms.at(i), CL_DEVICE_TYPE_ALL, DeviceCount, DeviceIdsPtr, nullptr);

                // Add the ids to the vector
                for (unsigned int j = 0; j < DeviceCount; j++)
                {
                        this->Devices.push_back(DeviceIdsPtr[j]);
                }

                // Cleanup pointer
                delete[] DeviceIdsPtr;
                DeviceIdsPtr = nullptr;
        }

    
        return EXIT_SUCCESS;
}

// Creates the OpenCL context
int SobelFilter::CreateContext(const int platformId)
{
        cl_int ErrNum;

        cl_context_properties ContextProperties[] =
        {
                CL_CONTEXT_PLATFORM,
                (cl_context_properties)this->Platforms.at(platformId),
                0
        };

        // Attempte to create a GPU context on the platform
        this->Context = clCreateContextFromType(ContextProperties, CL_DEVICE_TYPE_GPU, nullptr, nullptr, &ErrNum);

        // If that fails, attempt to create a CPU context
        if (ErrNum != CL_SUCCESS)
        {
                std::cerr << "Could not create a GPU context, trying CPU..." << std::endl;

                this->Context = clCreateContextFromType(ContextProperties, CL_DEVICE_TYPE_CPU, nullptr, nullptr, &ErrNum);

                if (ErrNum != CL_SUCCESS)
                {
                        std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
                        return -1;
                }
        }

        return EXIT_SUCCESS;
}

int SobelFilter::CreateCommandQueue()
{
        cl_int ErrNum;
        size_t DeviceSizeBuffer = -1;

        ErrNum = clGetContextInfo(this->Context, CL_CONTEXT_DEVICES, 0, nullptr, &DeviceSizeBuffer);

        if (ErrNum != CL_SUCCESS)
        {
                std::cerr << "Failed to call clGetContextInfo(...,CL_CONTEXT_DEVICES,...)" << std::endl;
                return  -1;
        }

        if (DeviceSizeBuffer <= 0)
        {
                std::cerr << "No devices available." << std::endl;
                return -1;
        }

        cl_device_id * Devices = new cl_device_id[DeviceSizeBuffer / sizeof(cl_device_id)];

        ErrNum = clGetContextInfo(this->Context, CL_CONTEXT_DEVICES, DeviceSizeBuffer, Devices, nullptr);

        if (ErrNum != CL_SUCCESS)
        {
                delete[] Devices;
                Devices = nullptr;

                std::cerr << "Failed to get devices Ids." << std::endl;
        }

        this->PrimaryDevice = Devices[0];

        // OpenCL 2.0
        // this->Queue = clCreateCommandQueueWithProperties(this->Context, Devices[0], 0, &ErrNum);

        this->Queue = clCreateCommandQueue(this->Context, Devices[0], 0, &ErrNum);

    
