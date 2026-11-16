Each data type is a header (`charge.h`) and an implementation (`charge.c`), with a test client (`12_charge.c`). Other programs use it with `#include "charge.h"` and by compiling `../12_charge/charge.c` with `-I../12_charge`. `lib` holds `Color`, `Picture` (PPM images) and `Draw` (SVG drawings). Programs that draw save a `.ppm` or `.svg` file; open it with `open koch.svg`. 10 and 22 read the sample quote pages in `10_stockquote/quotes`. 21 can also be compiled with the `Complex` from 23.

```
.
├── 01_potentialgene
│   └── 01_potentialgene.c
├── 02_chargeclient
│   └── 02_chargeclient.c
├── 03_alberssquares
│   └── 03_alberssquares.c
├── 04_luminance
│   ├── 04_luminance.c
│   ├── luminance.c
│   └── luminance.h
├── 05_grayscale
│   ├── 05_grayscale.c
│   ├── darwin.ppm
│   └── mandrill.ppm
├── 06_scale
│   └── 06_scale.c
├── 07_fade
│   └── 07_fade.c
├── 08_potential
│   ├── 08_potential.c
│   └── charges.txt
├── 09_cat
│   ├── 09_cat.c
│   ├── in1.txt
│   └── in2.txt
├── 10_stockquote
│   ├── 10_stockquote.c
│   ├── quotes
│   │   ├── ADBE.html
│   │   ├── GOOG.html
│   │   ├── IBM.html
│   │   └── MSFT.html
│   ├── stockquote.c
│   └── stockquote.h
├── 11_split
│   ├── 11_split.c
│   └── djia.csv
├── 12_charge
│   ├── 12_charge.c
│   ├── charge.c
│   └── charge.h
├── 13_stopwatch
│   ├── 13_stopwatch.c
│   ├── stopwatch.c
│   └── stopwatch.h
├── 14_histogram
│   ├── 14_histogram.c
│   ├── histogram.c
│   └── histogram.h
├── 15_turtle
│   ├── 15_turtle.c
│   ├── turtle.c
│   └── turtle.h
├── 16_koch
│   └── 16_koch.c
├── 17_spiral
│   └── 17_spiral.c
├── 18_drunk
│   └── 18_drunk.c
├── 19_drunks
│   └── 19_drunks.c
├── 20_complex
│   ├── 20_complex.c
│   ├── complexnum.c
│   └── complexnum.h
├── 21_mandelbrot
│   └── 21_mandelbrot.c
├── 22_stockaccount
│   ├── 22_stockaccount.c
│   ├── stockaccount.c
│   ├── stockaccount.h
│   └── turing.txt
├── 23_complexpolar
│   ├── 23_complexpolar.c
│   ├── complexnum.c
│   └── complexnum.h
├── 24_counter
│   ├── 24_counter.c
│   ├── counter.c
│   └── counter.h
├── 25_vector
│   ├── 25_vector.c
│   ├── vector.c
│   └── vector.h
├── 26_sketch
│   ├── 26_sketch.c
│   ├── genome20.txt
│   ├── sketch.c
│   └── sketch.h
├── 27_comparedocuments
│   ├── 27_comparedocuments.c
│   ├── actg.txt
│   ├── amazon.html
│   ├── constitution.txt
│   ├── documents.txt
│   ├── huckfinn.txt
│   ├── prejudice.txt
│   └── tomsawyer.txt
├── 28_body
│   ├── 28_body.c
│   ├── body.c
│   └── body.h
├── 29_universe
│   ├── 29_universe.c
│   ├── 2body.txt
│   ├── 2bodytiny.txt
│   ├── 3body.txt
│   ├── 4body.txt
│   ├── universe.c
│   └── universe.h
└── lib
    ├── color.h
    ├── draw.c
    ├── draw.h
    ├── picture.c
    └── picture.h
```
