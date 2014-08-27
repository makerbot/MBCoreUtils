OPTION(MBCOREUTILS_LIB_BUILD_SHARED
    "Build MBCOREUTILS_lib as a shared library."
    OFF)
IF(MBCOREUTILS_LIB_BUILD_SHARED)
  SET(MBCOREUTILS_LIB_TYPE SHARED)
  ADD_DEFINITIONS( -DJSON_DLL_BUILD )
ELSE()
  SET(MBCOREUTILS_LIB_TYPE STATIC)
ENDIF()

ADD_LIBRARY( MBCoreUtils_lib ${MBCOREUTILS_LIB_TYPE}
    angle.h
    appparameters.h
    commontypes.h
    conditionvariable.h
    event.h
    ilifecyclecontrol.h
    ilock.h
    irunnable.h
    json.h
    json_impl.h
    kilograms.h
    linuxapplication.h
    lockguard.h
    macapplication.h
    materials.h
    meters.h
    mutex.h
    tagged_id.h
    thread.h
    usb_descriptor.h
    vector_version.h
    version.h )

SET_TARGET_PROPERTIES( MBCoreUtils_lib PROPERTIES OUTPUT_NAME MBCoreUtils )
SET_TARGET_PROPERTIES( MBCoreUtils_lib PROPERTIES LINKER_LANGUAGE C )
INSTALL( TARGETS MBCoreUtils_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib )
