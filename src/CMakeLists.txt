cmake_minimum_required(VERSION 3.5.1)

project(Ascend310)

set(LIBRARY_OUTPUT_PATH  "../lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "../out")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -O0 -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -O2 -Wall")
set(SRC_LIST 
    cJSON.c    
    esp32_c3.c  
    key.c       
    pca9557.c  
    spi.c      
    task.c
    adxl345.c       
    ds1339u.c  
    i2c.c       
    led.c  
    multiButton.c  
    sht20.c    
    ssd1306.c  
    uart.c
    v4l2.c
    ms1100.c
)

set(ASCEND_TOOLKIT_PATH /data/Ascend/ascend-toolkit)
set(ASCEND_DDK_PATH /data/ascend_ddk)

include_directories(
    ../inc/
    ${ASCEND_DDK_PATH}/arm/include/opencv4
    ${ASCEND_DDK_PATH}/arm/include/
    ${ASCEND_TOOLKIT_PATH}/latest/arm64-linux/acllib/include
)

link_directories(
    /usr/local/lib
    ${ASCEND_DDK_PATH}/arm/lib/
    ${ASCEND_TOOLKIT_PATH}/latest/arm64-linux/acllib/lib64/
    ${ASCEND_TOOLKIT_PATH}/latest/atc/lib64
)


add_executable(main 
    main.cpp
    ${SRC_LIST}
    model_process.cpp
    object_detect.cpp
    utils.cpp
    yolov3.cpp
)
target_link_libraries(main  
    pthread 
    ascendcl 
    atlasutil
    stdc++ 
    opencv_highgui  
    opencv_core 
    opencv_imgproc 
    opencv_imgcodecs 
    opencv_calib3d 
    opencv_features2d 
    opencv_videoio 
    protobuf 
    presenteragent
    avcodec 
    swresample
)

install(TARGETS main DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

