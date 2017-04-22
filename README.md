# image-based-font
Image based font generator generates a set of B-spline curves based on an image provided by the user.

## Usage
To compile, use make.

### Image Based Curve Generation

To run, use ./a.out image.png where image.png is the file name of the image. For example: ./a.out q.png.

The program runs in several stages. Use scroll wheel to adjust threshold values in each stage; press Enter to confirm adjustment and advance onto the next stage.

1. Adjust edge detection threshold. Use scroll wheel to adjust until all desired edges are shown and connected EXCEPT where corners are apparent; it is ok if some noise are apparent.
2. Adjust corner detection threshold. Detected corners are displayed as a cross. Use scroll wheel to adjust until all desired corners are shown; corners do not have to be exactly 1 pixel wide.
3. Several automatic generation stages proceeds.
4. Adjust corner connection threshold. Corners are being connected to their respective nearest edges, use scroll wheel to adjust until all corners are connected to their nearest edges.
5. Several automatic noise cancelling, curve generation stages proceeds.
6. Adjust details to each edge. Use scroll wheel to adjust the level of details each edge has.
7. Manual editing. Curves are generated and are ready for manual editing.
   * Left click and drag to move a control point.
   * Right click on a control point to delete it.
   * Press Enter to save the curves. The file will be named curves/image.txt where image.png is the image name.
   
### Curve Editing

To run, use ./a.out image.txt where image.txt is the file name of the curve. For example: ./a.out q.txt.

The program automatically advances to manual editing stage. See above for manual editing instructions.

## Specifications

The program uses
1. Canny edge detector for edge detection.
2. Harris corner detector for corner detection.
3. Several passes of breadth first search for processing edges, corners, noise removal and target curve detection.
4. Reverse Chaikin subdivision for curve generation.
