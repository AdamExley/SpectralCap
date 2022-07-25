from SpecCap import *
import rawpy
import cv2

a = RawImage(r'inp/720nm.RW2')
b = RawImage(r'inp/670nm.RW2')

c = a.raw
c.raw_image = np.abs(a.raw.raw_image - b.raw.raw_image)


cv2.imshow(c.postprocess())

# print(cv2.Canny(a.processed_preview,50,100) / 512)
# cv2.imshow("B",(cv2.Canny(b.processed_preview,50,100) - cv2.Canny(a.processed_preview,50,100)) / 512 + 0.5)
# cv2.imshow("B",cv2.Canny(a.processed_preview,50,100) - cv2.Canny(b.processed_preview,50,100))
cv2.waitKey(0)