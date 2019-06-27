
function(swift_vexos_include var)
  set(paths)
  list(APPEND paths "${SWIFT_VEX_SDK_PATH}/vexv5/include"
                    "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/include"
                    "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/include/c++/4.9.3"
                    "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/include/c++/4.9.3/arm-none-eabi/armv7-ar/thumb"
                    "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/include/c++/4.9.3/arm-none-eabi/armv7-ar/thumb/bits"
                    "${SWIFT_VEX_SDK_PATH}/vexv5/clang/7.0.0/include")
  set(${var} ${paths} PARENT_SCOPE)
endfunction()

function(swift_vexos_lib_for_arch arch var)
  set(paths)
  list(APPEND paths "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/libs")
  set(${var} ${paths} PARENT_SCOPE)
endfunction()
