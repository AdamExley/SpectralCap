import rawpy
import numpy
import cv2

from .utils import *


PREVIEW_DS = 4


class RawImage():
    def __init__(self, filepath: str) -> None:
        self.filepath = filepath
        self.raw = rawpy.imread(filepath)

    @property
    def processed_preview(self):
        return downscale(self.raw.postprocess(), PREVIEW_DS)