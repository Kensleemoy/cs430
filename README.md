# GROUP 3: Mandelbrot
### Nori Natsuhara, Kenslee Moy, Shivanvi Singh, Monte Hedrick, Tung Ho

## Compiling

To compile, run from root directory:
```
make mandelbrot
```

## Running & Converting

To run, run from root directory:
```
./bin/mandelbrot <out.ppm>
```

This will create a .ppm file at the location or your choosing or will
default to the root directory.

If you want to convert this to a .png file, you can run
the command:
```
convert -normalize <your .ppm file name> <desired .png file name>
```

OR, if you want to change the color:
```
convert -negate -normalize -fill blue -tint 100 <your .ppm file name> <desired .png file name>
```

Example of running and converting (from root directory):
```
./bin/mandelbrot pic.ppm
convert -normalize ./pic.ppm ./converted.png
```

## Resources
[Mandelbrot Code Serial](https://gist.github.com/andrejbauer/7919569)