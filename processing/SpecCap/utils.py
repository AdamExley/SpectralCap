import numpy as np
import cv2



def downscale(img: np.ndarray, ds: float):
    outsize = np.array(img.shape[:2][::-1]) // ds
    return cv2.resize(img, outsize)