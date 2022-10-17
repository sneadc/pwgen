/*
 * sf-pwgen.c
 * pwgen
 *
 * Modified by Christopher Snead on 2022-10-05.
 *
 * sf-pwgen.m -- macOS command line password generator
 * Copyright (c) 2012-2019 Anders Bergh <anders1@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must
 *   not be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 */

#include "SFPasswordAssistant.h"
#include <getopt.h>
#include <printf.h>

#define PROGRAM_NAME "sf-pwgen"
#define PROGRAM_VERSION "1.5.1"

#define PASS_DEFAULT_COUNT 5
#define PASS_DEFAULT_LENGTH 12

void usage(const char *programName) {
  printf(
    "%s - macOS password generator\n\n"
    "  Usage:\n"
    "    -a | --algorithm  Available algorithms: memorable, random, letters, "
    "alphanumeric, numbers.\n"
    "    -c | --count      The number of passwords to generate (default: %d)"
    "    -l | --length     Desired length of the generated passwords "
    "(default: "
    "%d)\n"
    "    -v | --version    Display version\n"
    "    -h | --help       Display this help\n",
    programName, PASS_DEFAULT_COUNT, PASS_DEFAULT_LENGTH);
}

/**
 * Post a formatted error message to stderr
 *
 * Method documentation placeholder
 * @param [in] fmt Formatting specifier
 * @param [in] ... Additional arguments
 */
void post(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}

int main(int argc, char *const argv[]) {
  // Defaults
  int count = PASS_DEFAULT_COUNT;
  int length = PASS_DEFAULT_LENGTH;
  SFPWAAlgorithm algorithm = kSFPWAAlgorithmMemorable;

  //  Command line arguments
  static struct option options[] = {// Arguments
                                    {"algorithm", required_argument, 0, 'a'},
                                    {"count", required_argument, 0, 'c'},
                                    {"length", required_argument, 0, 'l'},
                                    // Help and stuff ...
                                    {"version", no_argument, 0, 'v'},
                                    {"help", no_argument, 0, 'h'},
                                    {NULL, 0, NULL, 0}};

  int opt, ndx;
  while ((opt = getopt_long(argc, argv, "a:c:l:hv", options, &ndx)) != -1) {
    switch (opt) {
      case 'a':
        switch (tolower(*optarg)) {
          case 'm':
            // memorable
            algorithm = kSFPWAAlgorithmMemorable;
            break;
          case 'r':
            // random
            algorithm = kSFPWAAlgorithmRandom;
            break;
          case 'l':
            // letters
            algorithm = kSFPWAAlgorithmLetters;
            break;
          case 'a':
            // alphanumeric
            algorithm = kSFPWAAlgorithmAlphanumeric;
            break;
          case 'n':
            // numbers
            algorithm = kSFPWAAlgorithmNumbers;
            break;
          default:
            post("error: unknown algorithm.\n");
            usage(argv[0]);
            return EXIT_FAILURE;
        }
        break;
      case 'c':
        count = (int)strtol(optarg, NULL, 10);
        break;
      case 'l':
        length = (int)strtol(optarg, NULL, 10);
        break;
      case 'h':
        usage(argv[0]);
        return EXIT_SUCCESS;
      case 'v':
        printf("%s v%s\n", PROGRAM_NAME, PROGRAM_VERSION);
        break;
      default:
        usage(argv[0]);
        return EXIT_FAILURE;
    }
  }

  SFPWAContextRef ctx;
  CFPropertyListRef pol;
  CFMutableArrayRef suggestions;
  CFStringEncoding enc;

  pol = SFPWAPolicyCopyDefault();
  enc = CFStringGetSystemEncoding();
  ctx = SFPWAContextCreateWithDefaults();
  suggestions = SFPWAPasswordSuggest(ctx, NULL, length, 0, count, algorithm);

  for (int i = 0; i < CFArrayGetCount(suggestions); ++i) {
    printf("%s\n",
           CFStringGetCStringPtr(CFArrayGetValueAtIndex(suggestions, i), enc));
  }

  CFRelease(suggestions);
  SFPWAContextRelease(ctx);
  CFRelease(pol);

  return EXIT_SUCCESS;
}