# Ray-Tracer
In 3D computer graphics, ray tracing is a rendering technique for generating an image by tracing the path of light as pixels in an image plane and simulating the effects of its encounters with virtual objects.

The technique is capable of producing a high degree of visual realism, more so than typical scanline rendering methods, but at a greater computational cost. This makes ray tracing best suited for applications where taking a relatively long time to render can be tolerated, such as in still computer-generated images, and film and television visual effects (VFX), but generally more poorly suited to real-time applications such as video games, where speed is critical in rendering each frame.

## Usage
### Building
* make
### Cleaning
* make clean

### Ray tracing an image
* ./target/debug > Images/[image_name]

## Rendered Samples
![alt text][render_01]

[render_01]: Images/diffuse_sphere.png "Diffuse material with gamma correction"

![alt text][render_02]

[render_02]: Images/metal_spheres.png "Metal spheres"

![alt text][render_03]

[render_03]: Images/Final_render.png "Final Render"
