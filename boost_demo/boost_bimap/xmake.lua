target(
    "boost_bimap",
    function()
        set_kind("binary")
        set_languages("c++23")

        add_files("boost_bimap.cpp")

        add_packages("boost")
    end
)
