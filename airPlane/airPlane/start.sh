# /bin/sh
/clean.sh  &

#启动主进程，主要用于获取ＧＰＳ坐标，及获取图像
/home/ubuntu/airPlane/airPlane >> test.log &      

#等待５０Ｓ，为确保系统已经完全启动，且已经开始拍照
sleep 10

#启动用于发送图片的客户端
/home/ubuntu/airPlane/Client >> pic.log & 
#等待１０Ｓ用于错开ＳＯＣＫＥＴ建立
sleep 10
#启动用于发送ＧＰＳ坐标文件的客户端
/home/ubuntu/airPlane/Clientini  >> ini.log &


datepath=`date +%Y-%m-%d+%H:%M`

filepath=/media/ubuntu/EC70AB4170AB117E/$datepath

mkdir $filepath

#用于拷贝数据到SD卡
python IniParse.py  $filepath >> sdcp.log &
