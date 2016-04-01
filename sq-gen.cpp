#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <ctime>
#include <cerrno>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "sq-gen-cmdline.h"

int main (int argc, char **argv) {
    int ret;
    time_t t;
    sf::Image image;
    struct gengetopt_args_info args;

    if(cmdline_parser(argc, argv, &args)) {
        cmdline_parser_print_help();
        fprintf(stderr, "\nERROR: Incorret usage\n");
        return EINVAL;
    }
    if(args.width_arg <= 0 || args.height_arg <= 0) {
        cmdline_parser_print_help();
        fprintf(stderr, "\nERROR: Non-positivie size given\n");
        ret = EINVAL;
        goto main_err;
    }
    if((args.red_given ? args.red_arg < 0 : 0) || (args.green_given ? args.green_arg < 0 : 0) || (args.blue_given ? args.blue_arg < 0 : 0)) {
        cmdline_parser_print_help();
        fprintf(stderr, "\nERROR: Negative color parameter given\n");
        ret = EINVAL;
        goto main_err;
    }
    if((t = time(NULL)) < 0) {
        ret = errno;
        fprintf(stderr, "ERROR: Cannot get current time: %s\n", strerror(errno));
        goto main_err;
    }
    srand(t);
    image.create(args.width_arg, args.height_arg, sf::Color(args.red_given ? args.red_arg : rand() % 256, args.green_given ? args.green_arg : rand() % 256, args.blue_given ? args.blue_arg : rand() % 256));

    if(!image.saveToFile(args.output_arg)) {
        fprintf(stderr, "ERROR: Cannot save the image\n");
        ret = -1;
        goto main_err;
    }

    ret = 0;
main_err:
    cmdline_parser_free(&args);
    return ret;
}

