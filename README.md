# Lunar Image Processing and Quality Analysis

This project is a small Python image-processing workflow for lunar surface images. I built it to test basic ways of cleaning up and comparing lunar image products, especially contrast, brightness spread, edge visibility, and residual noise.

The script reads images from `data/raw/`, processes them, and saves the results into the `outputs/` folder.

## What it does

For each image, the script creates:

- a normalized grayscale image
- a contrast-stretched image
- an edge map
- a residual/noise image
- smaller image tiles
- a comparison plot
- a row of image-quality metrics in a CSV file

The goal is not to do crater detection or terrain classification. This is more of a preprocessing and quality-check project: take raw lunar images, make surface features easier to inspect, and record some basic metrics for comparison.

## Installation

Clone the repo:

    git clone https://github.com/sssuriset/lunar-image-processing.git
    cd lunar-image-processing

Install the dependencies:

    python3 -m pip install -r requirements.txt

The main packages are:

    numpy
    matplotlib
    pillow
    scikit-image

## How to run it

Put one or more images in:

    data/raw/

Then run:

    python3 src/process_image.py

Supported image types:

    .png
    .jpg
    .jpeg
    .tif
    .tiff

The script saves processed images, plots, tiles, and a metrics CSV in the `outputs/` folder.

## Processing steps

### Normalization

Each image is converted to grayscale and rescaled using percentile limits. I used percentile scaling instead of the absolute minimum and maximum because a few extreme pixels can make the rest of the image look flat.

### Contrast stretching

The script stretches the useful brightness range of the image. This helps bring out crater rims, shadow boundaries, and surface texture that may be hard to see in the raw image.

### Edge detection

An edge map is created to show where sharp boundaries appear in the image. This gives a rough check of how much visible structure the image has after processing.

### Residual image

The script subtracts a blurred version of the image from the normalized image. This leaves smaller-scale variation behind. I use this as a simple residual/noise check, not as a calibrated noise model.

The residual plot is displayed with symmetric limits so positive and negative residuals are treated evenly.

### Tiling

The image is split into smaller sections. Edge tiles are kept even when the image size does not divide evenly by the tile size, so the script does not silently throw away the right or bottom edge of an image.

## Metrics

The CSV file records:

    mean
    median
    std
    sharpness
    edgeFrac
    residStd
    contrastRange
    brightFrac
    darkFrac

What they mean:

- `mean`: average normalized brightness
- `median`: median normalized brightness
- `std`: spread of pixel values
- `sharpness`: rough sharpness estimate based on image variation
- `edgeFrac`: fraction of pixels marked as edges
- `residStd`: spread of the residual image
- `contrastRange`: difference between high and low percentile brightness values
- `brightFrac`: fraction of very bright pixels
- `darkFrac`: fraction of very dark pixels

These are simple comparison metrics. They are useful for checking image quality across a batch, but they are not calibrated lunar surface measurements.

## Limitations

This project uses classical image-processing methods only. It does not georeference images, match features to lunar catalogs, classify terrain, or estimate physical reflectance.

The results should be treated as image-quality and preprocessing outputs, not as a full scientific analysis pipeline.

## Possible upgrades

Some reasonable next steps would be:

- add FITS image support
- add command-line options for tile size and contrast limits
- add batch summary plots
- test crater or ridge candidate detection
- compare processed outputs against labeled lunar features
