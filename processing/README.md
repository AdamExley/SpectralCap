# Processing

This includes a few of my forays in automatic processing of 7-channel hyperspectral images into false-color. 

This section of the repository is *very much* a work-in-progress.

So far, I've had an easy time capturing hyper-spectral images, but have had less success automating the processing of them.



# Camera Control


I also played around with the idea of using higher-level control of the camera while changing the lighting.

Ultimately, as I have a full-spectrum Lumix G9, which doesn't have an easy method of automated control, I abandoned this.

What I *did* try, though, was automating the tethered camera's settings via a GUI-manipulating bot. This was clunky, and relied on quite a bit of hardcoding, but is in [cap.py](./cap.py)


## Extra Installation


```bash
pip install -r requirements.txt
```


For USB control of Lumix G9, you also need tesseract: 
https://github.com/UB-Mannheim/tesseract/wiki
> This enables the bot to use GUI screenshots to parse camera settings