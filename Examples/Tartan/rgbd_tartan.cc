/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<opencv2/core/core.hpp>
#include <boost/filesystem.hpp>

#include<System.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "Thirdparty/cnpy/cnpy.h"

using namespace std;

int CountImages(const string &tartanFolder);

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        cerr << endl << "Usage: ./rgbd_tartan path_to_vocabulary path_to_settings path_to_sequence output_file_name" << endl;
        return 1;
    }

    // Retrieve paths to images
    string tartanFolder = string(argv[3]);
    const int nImages = CountImages(tartanFolder);

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(argv[1],argv[2],ORB_SLAM2::System::RGBD,true);

    // Vector for tracking time statistics
    vector<float> vTimesTrack;
    vTimesTrack.resize(nImages);

    cout << endl << "-------" << endl;
    cout << "Start processing sequence ..." << endl;
    cout << "Images in the sequence: " << nImages << endl << endl;

    // Main loop
    cv::Mat imRGB, imD;
    for(int ni=0; ni<nImages; ni++)
    {
        // format curr_index
        stringstream ss;
        ss << setw(6) << setfill('0') << ni;
        string indexStr = ss.str();
        // read rgb image
        string imgPth = string(argv[3]) + "/image_left/" + indexStr + "_left.png";
        imRGB = cv::imread(imgPth, CV_LOAD_IMAGE_UNCHANGED);
        // read depth npy
        string depPth = string(argv[3]) + "/depth_left/" + indexStr + "_left_depth.npy";
        cnpy::NpyArray depArr = cnpy::npy_load(depPth);
        float* dep_data = depArr.data<float>();
        int dim1 = depArr.shape[0];
        int dim2 = depArr.shape[1];
        cv::Mat rawDep(cv::Size(dim2, dim1), CV_32FC1, dep_data);
        // set high depth pixels (sky) to nan
        for (int r = 0; r < rawDep.rows; r++) {
            for (int c = 0; c < rawDep.cols; c++) {
                if (rawDep.at<float>(r, c) < 10000) continue;
                rawDep.at<float>(r, c) = std::nanf("1");
            }
        }
        imD = rawDep.clone();
        double tframe = (double)ni;

        if(imRGB.empty())
        {
            cerr << endl << "Failed to load image at: "
                 << string(argv[3]) << "/" << imgPth << endl;
            return 1;
        }

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system
        SLAM.TrackRGBD(imRGB,imD,tframe);

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

        vTimesTrack[ni]=ttrack;

        // Wait to load the next frame
        // seems unnecessary?
        // double T=0;
        // if(ni<nImages-1)
        //     T = vTimestamps[ni+1]-tframe;
        // else if(ni>0)
        //     T = tframe-vTimestamps[ni-1];

        // if(ttrack<T)
        //     usleep((T-ttrack)*1e6);
    }

    // Stop all threads
    SLAM.Shutdown();

    // Tracking time statistics
    sort(vTimesTrack.begin(),vTimesTrack.end());
    float totaltime = 0;
    for(int ni=0; ni<nImages; ni++)
    {
        totaltime+=vTimesTrack[ni];
    }
    cout << "-------" << endl << endl;
    cout << "median tracking time: " << vTimesTrack[nImages/2] << endl;
    cout << "mean tracking time: " << totaltime/nImages << endl;

    // Save camera trajectory
    SLAM.SaveTrajectoryTartan(string(argv[4])); 

    return 0;
}

int CountImages(const string &tartan_folder)
{
    // use left camera only, rgbd
    const string depth_pth = tartan_folder + "/depth_left";
    const string image_pth = tartan_folder + "/image_left";
    // count number of files in both dirs
    int depth_count = 0;
    boost::filesystem::directory_iterator end_it;
    for (boost::filesystem::directory_iterator it(depth_pth); it != end_it; it++) {
      depth_count++;
    }
    int image_count = 0;
    for (boost::filesystem::directory_iterator it(image_pth); it != end_it; it++) {
      image_count++;
    }
    assert (depth_count == image_count);
    cout << "Found " << depth_count << " image pairs\n";
    return depth_count;
}
