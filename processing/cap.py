import pyautogui as pag
import pygetwindow as gw
import time
import numpy as np

from PIL import Image
import pytesseract

import logging

logging.basicConfig(level=logging.DEBUG)

pytesseract.pytesseract.tesseract_cmd = r'C:\Program Files\Tesseract-OCR\tesseract.exe'


CAP_WIN_TITLE = "1: DC-G9"

### CURRENT APERTURE
class CurrAp:
    CENTER = (169,212)
    BOX_SIZE = (80,60)

    BOX_REGION = (CENTER[0] - BOX_SIZE[0]//2, CENTER[1] - BOX_SIZE[1]//2,
        BOX_SIZE[0], BOX_SIZE[1])


### APERTURE SELECTION
class ApSel:
    TOP_SCROLL = (214,234)
    BOTTOM_SCROLL = (214,569)

    LEFT_CORNER = (105, 211)
    BOX_HEIGHT = 36
    BOX_WIDTH = 100
    BOX_NUM = 10.5



DEAD_SPOT = (32,141)




def wait():
    time.sleep(0.075)

def apertureToFloat(ap: str):
    return float(ap.replace('F',''))

def runOCR(img: Image):
    return pytesseract.image_to_string(img)

def imgToAperture(img: Image):
    return apertureToFloat(runOCR(img))



class CaptureInteractor:

    def __init__(self) -> None:
        self.isDead = False
        self.isSetup = False

        cap_windows = gw.getWindowsWithTitle(CAP_WIN_TITLE)

        assert len(cap_windows) >= 1, "No capture window open"

        self.window = cap_windows[0]

        self.setup()

    def deadOut(self, remain_dead: bool = False):
        if not self.isDead:
            pag.click(DEAD_SPOT)
            self.isDead = remain_dead
            wait()

    def setup(self):
        self.window.activate()
        self.window.moveTo(0,0)
        self.deadOut()
        self.getApertureExtremes()
        self.isSetup = True


    def getApertureExtremes(self):
        self.deadOut()
        pag.click(CurrAp.CENTER)
        wait()
        pag.click(ApSel.TOP_SCROLL)

        ap_im = pag.screenshot(region=(*ApSel.LEFT_CORNER,ApSel.BOX_WIDTH,ApSel.BOX_HEIGHT))

        self.maxAperture = imgToAperture(ap_im)
        logging.info(f'Max Aperture: F{self.maxAperture}')

        pag.click(ApSel.BOTTOM_SCROLL)

        ap_im = pag.screenshot(region=(ApSel.LEFT_CORNER[0], ApSel.LEFT_CORNER[1] + ApSel.BOX_HEIGHT * (ApSel.BOX_NUM-1),ApSel.BOX_WIDTH,ApSel.BOX_HEIGHT))

        self.minAperture = imgToAperture(ap_im)
        logging.info(f'Min Aperture: F{self.minAperture}')
        self.deadOut()

    def getCurrentAperture(self):
        ap_im = pag.screenshot(region=CurrAp.BOX_REGION)
        current_ap = imgToAperture(ap_im)
        logging.info(f'Current Aperture: F{current_ap}')
        return current_ap








if __name__ == "__main__":
    a = CaptureInteractor()
    a.getCurrentAperture()



    while True:
        time.sleep(0.25)
        print(pag.position())
    