#include <stdint.h>

struct sysinfo {
    uint64_t freemem;  // Bộ nhớ trống (tính bằng byte)
    uint64_t nproc;    // Số tiến trình đang hoạt động
    uint64_t loadavg;  // Tải trung bình (tùy chọn cho thử thách)
};
