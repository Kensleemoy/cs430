# GROUP 3: Mandelbrot
### Nori Natsuhara, Kenslee Moy, Shivanvi Singh, Monte Hedrick, Tung Ho

## Compiling

To compile, run from root directory:
```
make mandelbrot <xmin> <xmax> <ymin> <ymax> <maxiter> <xres> <out.ppm>
```

## Running & Converting

To run, run from root directory:
```
./bin/mandelbrot
```

This will create a .ppm file. 

If you want to convert this to a .png file, you can run
the command:
```
convert -normalize <your ppm file name>.ppm <desired png file name>.png
```

## Resources
[Mandelbrot Code Serial](https://gist.github.com/andrejbauer/7919569)