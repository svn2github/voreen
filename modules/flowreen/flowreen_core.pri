#
# This file is included by voreenlib_core.pro with "VRN_MODULES += flowreen".
#

HEADERS += \
    $${VRN_MODULE_DIR}/flowreen/datastructures/flow2d.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/flow3d.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/simpletexture.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/streamlinetexture.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/volumeflow3d.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/volumeoperatorflowmagnitude.h \
    $${VRN_MODULE_DIR}/flowreen/datastructures/volumeoperatorintensitymask.h \
    $${VRN_MODULE_DIR}/flowreen/flowreenmodule.h \
    $${VRN_MODULE_DIR}/flowreen/io/flowreader.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowmagnitudes3d.h \
    $${VRN_MODULE_DIR}/flowreen/processors/floworthogonalslicerenderer.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowreenadapter.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowreenprocessor.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer2d.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer3d.h \
    $${VRN_MODULE_DIR}/flowreen/processors/flowstreamlinestexture3d.h \
    $${VRN_MODULE_DIR}/flowreen/processors/pathlinerenderer3d.h \
    $${VRN_MODULE_DIR}/flowreen/processors/streamlinerenderer3d.h \
    $${VRN_MODULE_DIR}/flowreen/utils/colorcodingability.h \
    $${VRN_MODULE_DIR}/flowreen/utils/flowmath.h 

SOURCES += \
    $${VRN_MODULE_DIR}/flowreen/datastructures/flow2d.cpp \
    $${VRN_MODULE_DIR}/flowreen/datastructures/flow3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/datastructures/simpletexture.cpp \
    $${VRN_MODULE_DIR}/flowreen/datastructures/streamlinetexture.cpp \
    $${VRN_MODULE_DIR}/flowreen/datastructures/volumeflow3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/datastructures/volumeoperatorflowmagnitude.cpp \
    $${VRN_MODULE_DIR}/flowreen/flowreenmodule.cpp \
    $${VRN_MODULE_DIR}/flowreen/io/flowreader.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowmagnitudes3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/floworthogonalslicerenderer.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowreenadapter.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowreenprocessor.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer2d.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowslicerenderer3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/flowstreamlinestexture3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/pathlinerenderer3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/processors/streamlinerenderer3d.cpp \
    $${VRN_MODULE_DIR}/flowreen/utils/colorcodingability.cpp \
    $${VRN_MODULE_DIR}/flowreen/utils/flowmath.cpp 

### Local Variables:
### mode:conf-unix
### End:
