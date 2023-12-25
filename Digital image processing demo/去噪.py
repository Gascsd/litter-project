"""
对指定图片进行去噪
"""
import cv2
import numpy as np
import pywt

image = cv2.imread('1.jpg')  # 读取图片
mean_blur = cv2.blur(image, (5, 5))# 均值滤波
median_blur = cv2.medianBlur(image, 5)# 中值滤波
gaussian_blur = cv2.GaussianBlur(image, (5, 5), 0)# 高斯滤波
# 小波去噪
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)# 将图像转换为灰度
coeffs = pywt.dwt2(gray, 'haar')# 进行小波变换

# 设置阈值来去噪
coeffs = list(coeffs)
coeffs[0] *= 0
coeffs[1] *= 0
reconstructed_image = pywt.idwt2(coeffs, 'haar')
reconstructed_image = np.uint8(reconstructed_image)# 转换图像的数据类型

# 显示并保存结果
cv2.imshow('Original Image', image)
cv2.imshow('Mean Blurred Image', mean_blur)
cv2.imshow('Median Blurred Image', median_blur)
cv2.imshow('Gaussian Blurred Image', gaussian_blur)
# cv2.imshow('Wavelet Denoised Image', reconstructed_image)

cv2.waitKey(0)

# 保存结果图像
cv2.imwrite('mean_blurred.jpg', mean_blur)
cv2.imwrite('median_blurred.jpg', median_blur)
cv2.imwrite('gaussian_blurred.jpg', gaussian_blur)
cv2.imwrite('wavelet_denoised.jpg', reconstructed_image)

cv2.destroyAllWindows()
