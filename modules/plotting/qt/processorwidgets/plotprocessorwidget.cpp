/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Created between 2005 and 2012 by The Voreen Team                   *
 * as listed in CREDITS.TXT <http://www.voreen.org>                   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#include "plotprocessorwidget.h"

#include "../plotpredicatedialog.h"
#include "../plotdataextendedtablemodel.h"
#include "../extendedtable.h"

//#include "../../utils/functionlibrary.h"
#include "../../utils/plotfunction.h"

#include "voreen/qt/voreenapplicationqt.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QCheckBox>

//#include <QMenu>
//#include <QTextEdit>


namespace voreen {

PlotProcessorWidget::PlotProcessorWidget(QWidget* parent, PlotProcessor* PlotProcessor)
    : QProcessorWidget(PlotProcessor, parent)
    , svgFileName_()
    //, File_(0,tr("Save SVG-File",0),QString::fromStdString(VoreenApplication::app()->getDataPath()),
    //tr("SVG (*.svg);;All TextFiles (*.svg *.xml)",0))
    //, updateFile_(tr("Update File",0),0)
{
    tgtAssert(PlotProcessor, "No Plotprocessor");
    setWindowTitle(QString::fromStdString(PlotProcessor->getName()));
    resize(256, 100);
    setMinimumSize(256,160);
    setMaximumWidth(1024);
    setMaximumHeight(200);
    adjustSize();
    switchLabel_ = new QLabel(tr("Change Render-Object",0));
    switchBox_ = new QComboBox();
    saveFile_ = new QPushButton(tr("Define File",0),0);
    fileLabel_ = new QLabel(tr("No File Defined..",0));
    fileLabel_->setWordWrap(true);
    file_ = new QFileDialog(0,tr("Set Render-File",0),QString::fromStdString(VoreenApplication::app()->getDataPath()),
        tr("SVG (*.svg);;All TextFiles (*.svg *.xml)",0));
    file_->setAcceptMode(QFileDialog::AcceptSave);
    updateFile_ = new QPushButton(tr("Update File",0),0);
    updateFile_->setEnabled(false);
    viewportClipping_ = new QCheckBox(tr("Clipp on ViewPort-Size",0),0);
    viewportClipping_->setChecked(true);
    viewportClipping_->setTristate(false);
    QObject::connect(saveFile_,SIGNAL(released()),this,SLOT(savereleased()));
    QObject::connect(updateFile_,SIGNAL(released()),this,SLOT(updateFileReleased()));  
    QObject::connect(switchBox_,SIGNAL(currentIndexChanged(int)),this,SLOT(updateObjectSwitch(int)));
    QObject::connect(viewportClipping_,SIGNAL(stateChanged(int)),this,SLOT(changeViewPortClipping(int)));
}

PlotProcessorWidget::~PlotProcessorWidget() {
    delete switchLabel_;
    delete switchBox_;
    delete file_;
    delete updateFile_;
    delete saveFile_;
    delete fileLabel_;
    delete viewportClipping_;
}

void PlotProcessorWidget::initialize() {

    QProcessorWidget::initialize();

    switchBox_->addItem(tr("SVG",0),QVariant(PlotLibraryFileBase::SVG));
    switchBox_->addItem(tr("Latex",0),QVariant(PlotLibraryFileBase::LATEX));
    
    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(switchLabel_,0,0);
    mainLayout->addWidget(switchBox_,1,0);
    mainLayout->addWidget(saveFile_,2,0);
    mainLayout->addWidget(fileLabel_,3,0);
    mainLayout->addWidget(viewportClipping_,4,0);
    mainLayout->addWidget(updateFile_,5,0);

    setLayout(mainLayout);
    file_->setModal(true);


    //show();

    initialized_ = true;
}


void PlotProcessorWidget::updateFromProcessor(){
}

void PlotProcessorWidget::savereleased() {
    if (file_->exec() == QFileDialog::Accepted) {
        updateFile_->setEnabled(true);
        svgFileName_ = file_->selectedFiles().at(0).toStdString();
        fileLabel_->setText(QString::fromStdString(svgFileName_));
    }
    else if (svgFileName_.length() == 0) {
        updateFile_->setEnabled(false);
        fileLabel_->setText(tr("No File Defined..",0));
    }
    adjustSize();
}

void PlotProcessorWidget::updateFileReleased() {
    PlotProcessor* plotprocessors = dynamic_cast<PlotProcessor*>(processor_);
    PlotLibraryFileBase::PlotLibraryFileType filetype = 
        static_cast<PlotLibraryFileBase::PlotLibraryFileType>(switchBox_->itemData(switchBox_->currentIndex()).toInt());
    plotprocessors->setFile(filetype,svgFileName_);
    plotprocessors->switchPlotLibrary();
}

void PlotProcessorWidget::updateObjectSwitch(int index) {
    if (index == 0) {
        file_->setFilter(tr("SVG (*.svg);;All TextFiles (*.svg *.xml)",0));
        //file_->
    }
    else {
        file_->setFilter(tr("Latex (*.tex);;All TextFiles (*.tex *.txt)",0));
    }
    if (updateFile_->isEnabled()) {
        svgFileName_ = file_->selectedFiles().at(0).toStdString();
        fileLabel_->setText(QString::fromStdString(svgFileName_));
    }
}

void PlotProcessorWidget::changeViewPortClipping(int state) {
    PlotProcessor* plotprocessors = dynamic_cast<PlotProcessor*>(processor_);
    if (state== Qt::Unchecked)
        plotprocessors->setViewPortClipping(false);
    else 
        plotprocessors->setViewPortClipping(false);
}

} //namespace voreen

