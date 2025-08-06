#include <cstdint>
#include <expected>
#include <filesystem>
#include <fstream>
#include <print>
#include <vector>

enum class FileErrorCode : std::int8_t {
    FileNotFound,
    PermissionDenied,
    NotAFile,
    ReadFailure,
    FileTooLarge,
    UnknownError
};

struct FileError {
    FileErrorCode code;
    std::filesystem::path path;
    std::string message;

    friend std::ostream& operator<<(std::ostream& os, const FileError& err) {
        os << "FileError[" << err.path << "]: ";
        switch (err.code) {
            case FileErrorCode::FileNotFound    : os << " File not found"; break;
            case FileErrorCode::PermissionDenied: os << " Permission denied"; break;
            case FileErrorCode::NotAFile        : os << " Not a file"; break;
            case FileErrorCode::ReadFailure     : os << " Read failure"; break;
            case FileErrorCode::FileTooLarge    : os << " File too large"; break;
            case FileErrorCode::UnknownError    : os << " Unknown error"; break;
        }
        if (!err.message.empty()) {
            os << " (" << err.message << ") ";
        }
        return os;
    }
};

template <>
struct std::formatter<FileError> {
    static constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }

    static auto format(const FileError& err, format_context& ctx) {
        std::ostringstream oss;
        oss << err;
        return std::format_to(ctx.out(), "{}", oss.str());
    }
};

static auto ReadFile(const std::filesystem::path& path) -> std::expected<std::vector<char>, FileError> {
    std::error_code ec;

    // 1. Existence check
    if (!std::filesystem::exists(path, ec)) {
        return std::unexpected(FileError{ .code = FileErrorCode::FileNotFound,
                                          .path = path,
                                          .message = ec.message() });
    }

    // 2. Type check
    if (!std::filesystem::is_regular_file(path, ec)) {
        return std::unexpected(FileError{ .code = FileErrorCode::NotAFile,
                                          .path = path,
                                          .message = ec.message() });
    }

    // 3. Size check
    const auto size = std::filesystem::file_size(path, ec);
    if (ec) {
        return std::unexpected(FileError{ .code = FileErrorCode::ReadFailure,
                                          .path = path,
                                          .message = ec.message() });
    }
    if (size > static_cast<uint64_t>(1024) * 1024) {
        return std::unexpected(FileError{ .code = FileErrorCode::FileTooLarge,
                                          .path = path,
                                          .message = "File is too large." });
    }

    // 4. Open and read
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        return std::unexpected(FileError{ .code = FileErrorCode::ReadFailure,
                                          .path = path,
                                          .message = "Failed to open file." });
    }

    std::vector<char> buffer(static_cast<size_t>(size));
    if (!file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()))) {
        return std::unexpected(FileError{ .code = FileErrorCode::ReadFailure,
                                          .path = path,
                                          .message = "Stream read failed." });
    }

    return buffer;
}

int main() {
    std::filesystem::path path{ "demo_auto.hpp" };
    auto result = ReadFile(path);
    if (result) {
        std::println("Loaded {} successfully, size = {}", path.string(), result->size());
    } else {
        std::println("Failed to load {}", path.string());
        std::println("Error message: {}", result.error());
    }

    return 0;
}
