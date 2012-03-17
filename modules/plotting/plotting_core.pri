
contains(DEFINES, VRN_DYNAMIC_LIBS) {
    DEFINES += VRN_MODULE_PLOTTING_BUILD_DLL
}

#    
# Processor sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/processors/barplot.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/hemisphereplot.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/imageanalyzer.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/lineplot.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatafitfunction.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatagroup.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatasource.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexport.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexporttext.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexportbase.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataselect.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatamerge.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotfunctiondiscret.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotfunctionsource.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/plotprocessor.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/surfaceplot.cpp \
    $${VRN_MODULE_DIR}/plotting/processors/scatterplot.cpp 
    
#
# Property sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/properties/plotentitiesproperty.cpp \
    $${VRN_MODULE_DIR}/plotting/properties/plotpredicateproperty.cpp \
    $${VRN_MODULE_DIR}/plotting/properties/plotselectionproperty.cpp \
    $${VRN_MODULE_DIR}/plotting/properties/plotdataproperty.cpp
    
#
# Port sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/ports/plotport.cpp 
    
#
# Utils sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/utils/aggregationfunction.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/aggregationfunctionfactory.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/colormap.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotexpression.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/functionlibrary.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotbase.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotentitysettings.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotdata.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotdatainserter.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotcell.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunction.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarylatex.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarylatexrender.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrary.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibraryfilebase.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarynonefilebase.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibraryopengl.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarysvg.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarysvgrender.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotrow.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotpredicate.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotpredicatefactory.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/plotselection.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/smartlabel.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctionterminals.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctiongrammar.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctionlexer.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctionparser.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctionnode.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctionvisitor.cpp \
    $${VRN_MODULE_DIR}/plotting/utils/parser/plotfunctiontoken.cpp
    
#
# Interaction sources
#
SOURCES += \
    $${VRN_MODULE_DIR}/plotting/interaction/plotcamerainteractionhandler.cpp \
    $${VRN_MODULE_DIR}/plotting/interaction/plotpickingmanager.cpp 
    
    
# 
# Processor headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/plottingmoduledefine.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatasource.h \    
    $${VRN_MODULE_DIR}/plotting/processors/plotfunctionsource.h \
    $${VRN_MODULE_DIR}/plotting/processors/barplot.h \
    $${VRN_MODULE_DIR}/plotting/processors/hemisphereplot.h \
    $${VRN_MODULE_DIR}/plotting/processors/imageanalyzer.h \
    $${VRN_MODULE_DIR}/plotting/processors/lineplot.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatafitfunction.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatagroup.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexport.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexporttext.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataexportbase.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdataselect.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotdatamerge.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotfunctiondiscret.h \
    $${VRN_MODULE_DIR}/plotting/processors/plotprocessor.h \
    $${VRN_MODULE_DIR}/plotting/processors/surfaceplot.h \
    $${VRN_MODULE_DIR}/plotting/processors/scatterplot.h 

#
# Property headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/properties/plotentitiesproperty.h \
    $${VRN_MODULE_DIR}/plotting/properties/plotpredicateproperty.h \
    $${VRN_MODULE_DIR}/plotting/properties/plotselectionproperty.h \
    $${VRN_MODULE_DIR}/plotting/properties/plotdataproperty.h
   
#
# Port headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/ports/plotport.h

#
# Utils headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/utils/aggregationfunction.h \
    $${VRN_MODULE_DIR}/plotting/utils/aggregationfunctionfactory.h \
    $${VRN_MODULE_DIR}/plotting/utils/colormap.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotentitysettings.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotexpression.h \
    $${VRN_MODULE_DIR}/plotting/utils/interval.h \
    $${VRN_MODULE_DIR}/plotting/utils/functionlibrary.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotbase.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotcell.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotdata.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotdatainserter.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunction.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarylatex.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarylatexrender.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrary.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibraryfilebase.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarynonefilebase.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibraryopengl.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarysvg.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotlibrarysvgrender.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotpredicate.h \    
    $${VRN_MODULE_DIR}/plotting/utils/plotpredicatefactory.h \    
    $${VRN_MODULE_DIR}/plotting/utils/plotrow.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotselection.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotzoomstate.h \
    $${VRN_MODULE_DIR}/plotting/utils/smartlabel.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctionterminals.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctiongrammar.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctionlexer.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctionparser.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctionnode.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctionvisitor.h \
    $${VRN_MODULE_DIR}/plotting/utils/plotfunctiontoken.h   

#
# Interaction headers
#
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/interaction/plotcamerainteractionhandler.h \
    $${VRN_MODULE_DIR}/plotting/interaction/plotpickingmanager.h 
    
    
# external dependency: triangle library
INCLUDEPATH += $${VRN_MODULE_DIR}/plotting/ext/triangle

SOURCES += \
    $${VRN_MODULE_DIR}/plotting/ext/triangle/src/del_impl.cpp
HEADERS += \
    $${VRN_MODULE_DIR}/plotting/ext/triangle/include/del_interface.hpp \
    $${VRN_MODULE_DIR}/plotting/ext/triangle/include/dpoint.hpp \
    $${VRN_MODULE_DIR}/plotting/ext/triangle/include/triangle.h \
    $${VRN_MODULE_DIR}/plotting/ext/triangle/include/triangle_impl.hpp
    
