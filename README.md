## 浙江工业大学2024秋嵌入式系统综合作业

本项目运行环境为Ubuntu18.04（可选择使用虚拟机），使用vscode+remote ssh插件进行开发；基于任课教师提供的实验指导书和基础代码，在Atlas200DevBoard上完成

根据指导书的内容，一共有六个小实验和综合性实验。在本项目中，实现了LED、按键控制，Sht20温湿度读取和显示（OLED和数码管），基于Yolov3的目标检测（视频流），基于URAT和ESP32的数据传输等

**关于模型转换方面：**

1. 文件切换到HwHiAiUser 用户，进入`/home/HwHiAiUser/experiment/Ascend310/scripts`目录修改`param.conf`文件。如果使用TYPE-C线连接开发板，则将这两个参数修改为“192.168.1.2”。
2. 进入`/home/HwHiAiUser/experiment/Ascend310/model`目录下，执行`atc --model=./yolov3.prototxt --weight=./yolov3.caffemodel --framework=0 --output=yolov3 --soc_version=Ascend310 --insert_op_conf=./aipp_bgr.cfg`，将 caffe 框架的模型和权重文件转化为昇腾平台下适配的om模型(建议手动输入指令)。等待5分钟左右，当看到`ATC run success`字样，表示模型转换已经成功， 查看当前目录，可以看到`yolov3.om`，为本实验需要加载的模型文件。 
3. 执行`bash /home/HwHiAiUser/software/samples/common/run_presenter_server.sh /home/HwHiAiUser/experiment/Ascend310/scripts/param.conf` 指令开启 web 服务器。 使用给出的网址http://192.168.1.2:7007来打开电脑的浏览器来访问web页面。若为网线连接开发板则使用http://192.168.0.2:7007 来访问。 
4. 进入`/home/HwHiAiUser/experiment/Ascend310/out`目录，执行`./main -t  Yolov3_Test`来加载视频文件运行推理程序。 