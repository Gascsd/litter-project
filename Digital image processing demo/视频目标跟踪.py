import cv2

# 初始化视频捕捉对象
video_capture = cv2.VideoCapture('data.mp4')
# 初始化对象检测器
object_detector = cv2.createBackgroundSubtractorMOG2()
# 初始化多目标跟踪器
multi_tracker = cv2.legacy.MultiTracker()
while True:
    ret, frame = video_capture.read()
    if not ret:
        break
    # 对当前帧进行目标检测
    mask = object_detector.apply(frame)
    # 对检测到的目标进行轮廓检测
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    for contour in contours:
        # 计算轮廓外接矩形
        (x, y, w, h) = cv2.boundingRect(contour)
        # 初始化单目标跟踪器
        tracker = cv2.legacy.TrackerCSRT_create()  # 或者使用 cv2.TrackerKCF_create()
        multi_tracker.add(tracker, frame, (x, y, w, h))
    # 多目标跟踪
    success, boxes = multi_tracker.update(frame)
    # 在图像上绘制跟踪框
    for box in boxes:
        (x, y, w, h) = [int(v) for v in box]
        cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
    # 显示结果
    cv2.imshow('Multi-object Tracking', frame)
    key = cv2.waitKey(30)
    if key == 27:  # 按下Esc键退出
        break
# 释放资源
video_capture.release()
cv2.destroyAllWindows()