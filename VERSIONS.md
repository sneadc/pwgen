# sf-pwgen version history

## 1.5.1 (2022-10-17)
 * Personal version, strictly 'C', part of my security framework playground.

## 1.5 (2019-04-13)
 * Warn if passwords are shorter than requested. Thanks to @dancek for implementing this.
 * Updated Xcode project to fix Travis CI (had to add a unit test).

## 1.4 (2016-10-31)
 * Fix crash bug on Sierra.

## 1.3 (2014-04-17)
 * System requirements are now Mountain Lion (10.8) and later.
 * Show default password length and count in help output.
 * When generating a lot of passwords at once, only request a few so it doesn't hang.

## 1.2 (2014-03-29)
 * Xcode project added
 * Ported to Objective-C with ARC (instead of C + Core Foundation)
 * Added -L, --language to generate passwords in other languages.
 * Renamed project to pwgen (the whole project, not just the tool).
 * Added -v, --version.
 * Renamed tool to sf-pwgen from pwgen. The old name was already used by another project.

## 1.1.1 (2013-03-02)
 * Relicense the header from no license to Public Domain

## 1.1 (2013-02-11)

 * More functions documented in header. 
 * Assume defaults.
 * Print output using UTF-8.

## 1.0 (2012-07-23)

 * Initial release.
