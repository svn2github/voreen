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

#include "voreen/qt/widgets/processor/canvasrendererwidget.h"
#include "voreen/core/network/networkevaluator.h"
#include "voreen/core/utils/voreenpainter.h"
#include "voreen/qt/widgets/snapshotwidget.h"
#include "voreen/qt/voreenapplicationqt.h"

#include <QDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QMainWindow>

namespace voreen {

CanvasRendererWidget::CanvasRendererWidget(QWidget* parent, CanvasRenderer* canvasRenderer)
    : QProcessorWidget(canvasRenderer, parent)
    , canvasWidget_(0)
    , snapshotElement_(0)
{
    tgtAssert(canvasRenderer, "No CanvasRenderer");

    setWindowTitle(QString::fromStdString(canvasRenderer->getName()));
    resize(256, 256);
}

CanvasRendererWidget::~CanvasRendererWidget() {
    // deregister canvas at owning CanvasRenderer
    CanvasRenderer* canvasRenderer = dynamic_cast<CanvasRenderer*>(processor_);
    if (canvasRenderer)
        canvasRenderer->setCanvas(0);

    if (canvasWidget_)
        delete canvasWidget_->getPainter();
    delete canvasWidget_;

}

void CanvasRendererWidget::initialize() {
    QProcessorWidget::initialize();

    CanvasRenderer* canvasRenderer = dynamic_cast<CanvasRenderer*>(processor_);
    tgtAssert(canvasRenderer, "CanvasRenderer expected");

    if (!VoreenApplication::app()) {
        LERRORC("voreen.qt.CanvasRendererWidget", "VoreenApplication not instantiated");
        throw new VoreenException("VoreenApplication not instantiated");
    }
    NetworkEvaluator* evaluator = VoreenApplication::app()->getNetworkEvaluator();
    if (!evaluator) {
        LERRORC("voreen.qt.CanvasRendererWidget", "No evaluator assigned to VoreenApplication");
        throw new VoreenException("No evaluator assigned to VoreenApplication");
    }

    canvasWidget_ = new tgt::QtCanvas("", tgt::ivec2(getSize().x, getSize().y), tgt::GLCanvas::RGBADD, this, true, 0);
    canvasWidget_->setMinimumSize(64, 64);
    canvasWidget_->setMouseTracking(true); // for receiving mouse move events without a pressed button

    QGridLayout* layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(canvasWidget_, 0, 0);
    setLayout(layout);

    //show();

    VoreenPainter* painter = new VoreenPainter(canvasWidget_, evaluator, canvasRenderer);
    canvasWidget_->setPainter(painter);
    painter->initialize();

    canvasRenderer->setCanvas(canvasWidget_);
    initialized_ = true;
}

//#ifdef VRN_MODULE_DEVIL
//void CanvasRendererWidget::keyPressEvent(QKeyEvent* event) {
//    if ((event->modifiers() == Qt::AltModifier) && (event->key() == Qt::Key_P) ) {
//        if (!snapshotTool_)
//            createSnapshotTool();
//        snapshotTool_->show();
//        snapshotTool_->setFocus();
//    }
//#else
//void CanvasRendererWidget::keyPressEvent(QKeyEvent*) {
//#endif
//}

void CanvasRendererWidget::resizeEvent(QResizeEvent* event) {
    if (snapshotElement_)
        snapshotElement_->updateFromProcessor();
    QProcessorWidget::resizeEvent(event);
}

//void CanvasRendererWidget::createSnapshotTool() {
//    if (snapshotTool_)
//        return;
//
//    snapshotTool_ = new SnapshotPlugin(VoreenApplicationQt::qtApp()->getMainWindow(),
//                                       dynamic_cast<CanvasRenderer*>(processor_));
//    snapshotTool_->adjustSize();
//    snapshotTool_->setFixedSize(snapshotTool_->sizeHint());
//}

//void CanvasRendererWidget::showSnapshotTool() {
//    if (!snapshotTool_)
//        createSnapshotTool();
//    snapshotTool_->show();
//    snapshotTool_->raise();
//}

void CanvasRendererWidget::updateFromProcessor() {
    if (canvasWidget_ && processor_) {
        Property* prop = processor_->getProperty("showCursor");
        if(prop) {
            BoolProperty* bp = dynamic_cast<BoolProperty*>(prop);
            if(bp) {
                if(bp->get())
                    canvasWidget_->setCursor(Qt::ArrowCursor);
                else
                    canvasWidget_->setCursor(Qt::BlankCursor);
            }
        }
    }
    QProcessorWidget::updateFromProcessor();
}

void CanvasRendererWidget::setSnapshotElement(SnapshotElement* element) {
    snapshotElement_ = element;
}

} //namespace voreen
