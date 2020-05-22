#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s times\n", argv[0]);
        return 0;
    }
    size_t limit = atoi(argv[1]);

    int min_fd = limit + 1;
    int max_fd = 0;
    for (size_t i = 0; i < limit; ++i) {
        std::string file = std::to_string(i) + ".txt";
        int fd = open(file.c_str(), O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
            exit(1);
        }

        if (fd < min_fd) {
            min_fd = fd;
        }
        if (fd > max_fd) {
            max_fd = fd;
        }
    }

    auto start = std::chrono::steady_clock::now();
#if USE_CLOSEFROM
    closefrom(min_fd);
#else
    for (size_t i = min_fd; i < max_fd; ++i) {
        close(i);
    }
#endif
    auto end = std::chrono::steady_clock::now();

    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

#if USE_CLOSEFROM
    std::cout << "closefrom: " << diff.count() << " usecs" << std::endl;
#else
    std::cout << "close: " << diff.count() << " usecs" << std::endl;
#endif

    for (size_t i = 0; i < limit; ++i) {
        std::string file = std::to_string(i) + ".txt";
        unlink(file.c_str());
    }

    return 0;
}
