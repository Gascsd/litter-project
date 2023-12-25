import cv2

# 读取图像文件
image = cv2.imread('1.jpg')

# 去噪
denoised_image = cv2.fastNlMeansDenoisingColored(image, None, 10, 10, 7, 21)

# 颜色空间转换（从BGR到RGB）
rgb_image = cv2.cvtColor(denoised_image, cv2.COLOR_BGR2RGB)

# 展示原始图像和处理后的图像
cv2.imshow('Original Image', image)
cv2.imshow('Processed Image', rgb_image)
cv2.waitKey(0)
cv2.destroyAllWindows()