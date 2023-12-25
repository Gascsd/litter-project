"""
这段代码用于从data.mp4中读取一些图片出来
"""
import cv2

# 打开视频文件
videoName = 'data.mp4'
picNum = 5
video_capture = cv2.VideoCapture(videoName)

# 检查视频文件是否成功打开
if not video_capture.isOpened():
    print("打开%s失败" % videoName)
else:
    total_frames = int(video_capture.get(cv2.CAP_PROP_FRAME_COUNT))  # 获取视频的总帧数
    frame_to_read = 1  # 设置要读取的帧数
    while picNum != 0:
        video_capture.set(cv2.CAP_PROP_POS_FRAMES, frame_to_read)  # 设置视频捕获对象的位置
        success, frame = video_capture.read()  # 读取指定帧
        if success:
            # 保存指定帧为图片文件
            file_name = str(picNum) + '.jpg'
            cv2.imwrite(file_name, frame)
            print("Frame", frame_to_read, "has been saved as", file_name)
        else:
            print("Error: Unable to read the specified frame of the video.")
        frame_to_read = frame_to_read + total_frames / 5
        picNum -= 1

# 释放视频文件
video_capture.release()
