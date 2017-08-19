# Project Mp

## Intro

- Succinctly, this is a fractal play pen.
- It is _not_ a library.
- There is no **API**.
    + There are a lot of functions that might be of use
    + They may even one day be documented
- List its most useful/innovative/noteworthy features.
    * Mandelbrot set calculated with reals only
    * Mandelbrot set calculated with complex numbers
    * Mandelbrot set calculated with the Distance Estimator Method
    * Mandelbrot set calculated with the Continuous Potential Method
- State its goals/what problem(s) it solves.
    * Dust off my programming skills.
    * As much as possible work with what's out there&hellip;
    * Continue working with _fractals_ &mdash;probably the real point.
- This is now and always will be ***alpha***.
- Does not include badges.
- No box tops either.
- Still not a library.

### Getting Started/Requirements/Prerequisites/Dependencies
Include any essential instructions for:
- Getting it
    * Engage the usual suspects; download or clone&hellip;
- Installing It
    * Make sure you have a usable GCC
    * I use msys2 on windows and that insures GCC 6.3.0
    * you will need libs jpeg, gd and quadmath. openmp as well&hellip;
    * compile using GCC;
    * gcc -Wall -o mp -std=c99 -O3 -msse2 -march=native -fopenmp palette.c dictionary.c iniparser.c getopt.c cnames.c cspace.c colors.c elapsed.c util.c cJSON.c mp.c -ljpeg -lgd -lquadmath
- Running it
    * try this:
```   
    hsmyers\@BIGIRON c:\\perldev\\Fractal Labels\mp
    >mp -x -0.65 -y 0.0 -d 2.0 -i 500 -f test.jpg
    mp vr0.027
    FLT-diameter:2, dims: 3840x2160 test.jpg color=10, tweak=3 aa=(null)
    ————————————————————————————————
    13:08:2017 15:48:45.770362㎳ MDT
    elapsed time 0:0:0:20:566000㎳
    13:08:2017 15:49:06.336362㎳ MDT
    maxiter = '500', nMax = '499'
    ———————————————————————————————
```


### Mini&ndash;Manual

```void help( char c, char *Program, char *Version, char *Date ) {
    printf( "%s v%s dated %s\n", Program, Version, Date );
    if ( c == 'h' || c == '?' ) {
        printf( "\n  Options:\n\n" );
        printf( "  --aa           requires filename as an argument -a\n" );
        printf( "  --bourke       requires number as an argument -b\n" );
        printf( "  --color        requires number as an argument -r\n" );
        printf( "  --config       requires filename as an argument -c\n" );
        printf( "  --diameter     requires real as an argument   -d\n" );
        printf( "  --escape       requires real as an argument   -e\n" );
        printf( "  --file         requires filename as an argument -f\n" );
        printf( "  --height       requires number as an argument -l\n" );
        printf( "  --help         no argument                    -h\n" );
        printf( "  --iteration    requires number as an argument -i\n" );
        printf( "  --json         requires filename as an argument -j\n" );
        printf( "      may be prefixed with W: to write parameters\n" );
        printf( "  --kolor        requires RGB spec as an argument -k\n" );
        printf( "      allows up to %d RGB color specifications\n", NAMES_SIZE );
        printf( "      which may be 'named' colors or braced {..}\n" );
        printf( "  --magnify      requires real as an argument   -m\n" );
        printf( "  --next         argument is optional number    -n\n" );
        printf( "  --old          requires number as argument    -o\n" );
        printf( "  --palette      requires filename as an argument -p\n" );
        printf( "  --semidiameter requires number as an argument -s\n" );
        printf( "      this is an alias for radius\n" );
        printf( "  --tweak        requires number as an argument -t\n" );
        printf( "  --ultra        requires string in quotes as an argument -u\n");
        printf( "  --version      no argument                    -v\n" );
        printf( "  --width        requires number as an argument -w\n" );
        printf( "  --x_center     requires real as an argument   -x\n" );
        printf( "  --y_center     requires real as an argument   -y\n" );
        printf( "\n  long options ('--' prefix) are incremental till unambiguous\n" );
        printf( "  short options ('-' prefix) are exact\n" );
        printf( "  Hideously enough, options with optional arguments,\n" );
        printf( "  take the form [-[-]]option=arg, no spaces.\n" );
    }
    exit( 0 );
}
```

### Contributing
- Chris Thomasson
- Greg Harley

### TODO
- Improve documentation
- Next steps
- Features planned
- Known bugs (shortlist)

### Contact
- hsmyers@gmail.com
- http://www.sdragons.org/

### License
- see file License.txt
