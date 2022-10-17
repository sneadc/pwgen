# sf-pwgen

`sf-pwgen` is a command line tool which generates passwords using the
SecurityFoundation framework in macOS. It runs on Mountain Lion and later.

    sf-pwgen - macOS password generator
    
      Usage: sf-pwgen [options]
    
        -a | --algorithm  Available algorithms: memorable, random, letters, alphanumeric, numbers.
        -c | --count      The number of passwords to generate (default: 5)    -l | --length     Desired length of the generated passwords (default: 12)
        -v | --version    Display version
        -h | --help       Display this help


## SFPasswordAssistant.h
This project also includes SFPasswordAssistant.h, which is a
reverse-engineered header for Apple's password assistant API
(used in Keychain Access.app, etc.). It should work on Snow Leopard
and above.

To use it simply include `SFPasswordAssistant.h` in your project
and link to `SecurityFoundation.framework`.
