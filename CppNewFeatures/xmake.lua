add_rules("mode.debug", "mode.release")

function create_targets_for_cpp_files(directory, cpp_standard)
    for _, file in ipairs(os.files(directory .. "/*.cpp")) do
        local name = path.basename(file)
        target(directory .. "_" .. name)
            set_kind("binary")
            set_languages(cpp_standard)
            add_files(directory .. "/" .. name .. ".cpp")
    end
end

create_targets_for_cpp_files("Cpp11", "c++11")
-- create_targets_for_cpp_files("cpp_labs", "c++14")
