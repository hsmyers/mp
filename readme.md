# Project Mp

### Intro

- Succently, this is a fractal play pen.
- It is _not_ a library.
- There is no **_API_**
- List its most useful/innovative/noteworthy features.
    * feature one
    * feature two
- State its goals/what problem(s) it solves.
    * Dust off my programming skills.
    * As much as possible work with what's out there…
    * Continue working with *fractals*—probably the real point.
- Key concepts.
    * concept one
    * concept two
- This is now and always will be _alpha_.
- Does not include badges.

### Core Technical Concepts/Inspiration

- Why does it exist?
- Frame your project for the potential user. 
- Compare/contrast your project with other, similar projects so the user knows how it is different from those projects.
- Highlight the technical concepts that your project demonstrates or supports. Keep it very brief.

### Getting Started/Requirements/Prerequisites/Dependencies
Include any essential instructions for:
- Getting it
- Installing It
- Configuring It
- Running it

### Mini-Manual…
``` C
void help( char c, char *Program, char *Version, char *Date ) {
    printf( "%s v%s dated %s\n", Program, Version, Date );
    if ( c == 'h' || c == '?' ) {
        printf( "\n  Options:\n\n" );
        printf( "  --x_center    requires real as an argument   -x\n" );
        printf( "  --y_center    requires real as an argument   -y\n" );
        printf( "  --magnify     requires real as an argument   -m\n" );
        printf( "  --diameter    requires real as an argument   -d\n" );
        printf( "  --iteration   requires number as an argument -i\n" );
        printf( "  --width       requires number as an argument -w\n" );
        printf( "  --height      requires number as an argument -l\n" );
        printf( "  --file        requires string as an argument -f\n" );
        printf( "  --palette     requires string as an argument -p\n" );
        printf( "  --next        argument is optional number    -n\n" );
        printf( "  --config      requires string as an argument -c\n" );
        printf( "  --color       requires number as an argument -r\n" );
        printf( "  --aa          requires string as an argument -a\n" );
        printf( "  --tweak       requires number as an argument -t\n" );
        printf( "  --version     no argument                    -v\n" );
        printf( "  --help        no argument                    -h\n" );
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
- Next steps
- Features planned
- Known bugs (shortlist)

### Contact
- hsmyers@gmail.com
- http://www.sdragons.org/

### License
- see file License.txt
