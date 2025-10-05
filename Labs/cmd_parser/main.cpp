#include "cmd.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    cmdline::parser args;
    args.add<std::string>("host",
                          'h',
                          "host name",
                          true,
                          "");
    args.add<int>("port",
                  'p',
                  "port number",
                  false,
                  80,
                  cmdline::range(1, 65535));
    args.add<std::string>("type",
                          't',
                          "protocol type",
                          false,
                          "http",
                          cmdline::oneof<std::string>("http", "https", "ssh", "ftp"));
    args.add("gzip",
             '\0',
             "gzip when transfer");

    args.parse_check(argc, argv);

    std::cout << args.get<std::string>("type") << "://"
              << args.get<std::string>("host") << ":"
              << args.get<int>("port") << std::endl;

    if (args.exist("gzip")) {
        std::cout << "gzip" << std::endl;
    }

    return 0;
}
