
function(swift_vexos_include_for_arch arch var)
  set(paths)
  list(APPEND paths "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/include")
  set(${var} ${paths} PARENT_SCOPE)
endfunction()

function(swift_vexos_lib_for_arch arch var)
  set(paths)
  list(APPEND paths "${SWIFT_VEX_SDK_PATH}/vexv5/gcc/libs")

  set(${var} ${paths} PARENT_SCOPE)
endfunction()
