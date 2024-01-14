bazel build --config=stm32 //... --copt="-Wno-error" \
    --platforms=//targets:stm32
