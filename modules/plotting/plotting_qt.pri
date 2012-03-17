# Qt module class  
VRN_QT_MODULE_CLASSES += PlottingModuleQt
VRN_QT_MODULE_CLASS_HEADERS += plotting/plottingmoduleqt.h
VRN_QT_MODULE_CLASS_SOURCES += plotting/plottingmoduleqt.cpp

contains(DEFINES, VRN_DYNAMIC_LIBS) {
    DEFINES += VRN_MODULE_PLOTTING_BUILD_DLL
}

#
# Widget sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/qt/plotdatawidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotdatasimpletablemodel.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/extendedtable.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotdataextendedtablemodel.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotentitysettingsdialog.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotpredicatedialog.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectionentrytablemodel.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectiontablemodel.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectiondialog.cpp \

#
# Processor widget sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotprocessorwidgetfactory.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotprocessorwidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatamergewidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatafitfunctionwidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdataselectwidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatagroupwidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdataprocessorwidget.cpp 

#
# Property widget sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotpropertywidgetfactory.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotdatapropertywidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotentitiespropertywidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotpredicatepropertywidget.cpp \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotselectionpropertywidget.cpp 
 
 
#
# Widget headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/qt/plotdatawidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotdatasimpletablemodel.h \
    $${VRN_MODULE_DIR}/plotting/qt/extendedtable.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotdataextendedtablemodel.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotentitysettingsdialog.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotpredicatedialog.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectionentrytablemodel.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectiontablemodel.h \
    $${VRN_MODULE_DIR}/plotting/qt/plotselectiondialog.h \

#
# Processor widget headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotprocessorwidgetfactory.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotprocessorwidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatamergewidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatafitfunctionwidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdataselectwidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdatagroupwidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/processorwidgets/plotdataprocessorwidget.h 

#
# Property widget headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotpropertywidgetfactory.h \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotdatapropertywidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotentitiespropertywidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotpredicatepropertywidget.h \
    $${VRN_MODULE_DIR}/plotting/qt/propertywidgets/plotselectionpropertywidget.h 
