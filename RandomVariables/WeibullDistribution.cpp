/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: fmckenna

#include "WeibullDistribution.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>


WeibullDistribution::WeibullDistribution(QWidget *parent) :RandomVariableDistribution(parent)
{
    //
    // create the main horizontal layout and add the input entries
    //

    QHBoxLayout *mainLayout = new QHBoxLayout();

    shapeparam = this->createTextEntry(tr("Shape"), mainLayout);
    scaleparam = this->createTextEntry(tr("Scale"), mainLayout);

    mainLayout->addStretch();

    // set some defaults, and set layout for widget to be the horizontal layout
    mainLayout->setSpacing(10);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);
}
WeibullDistribution::~WeibullDistribution()
{

}

bool
WeibullDistribution::outputToJSON(QJsonObject &rvObject){

    // check for error condition, an entry had no value
    if (shapeparam->text().isEmpty() || scaleparam->text().isEmpty()) {
        emit sendErrorMessage("ERROR: WeibullDistribution - data has not been set");
        return false;
    }
    rvObject["shapeparam"]=shapeparam->text().toDouble();
    rvObject["scaleparam"]=scaleparam->text().toDouble();
    return true;
}

bool
WeibullDistribution::inputFromJSON(QJsonObject &rvObject){

    //
    // for all entries, make sure i exists and if it does get it, otherwise return error
    //

    if (rvObject.contains("shapeparam")) {
        QJsonValue theShapeValue = rvObject["shapeparam"];
        shapeparam->setText(QString::number(theShapeValue.toDouble()));
    } else {
        emit sendErrorMessage("ERROR: WeibullDistribution - no \"mean\" entry");
        return false;
    }

    if (rvObject.contains("scaleparam")) {
        QJsonValue theScaleValue = rvObject["scaleparam"];
        scaleparam->setText(QString::number(theScaleValue.toDouble()));
    } else {
        emit sendErrorMessage("ERROR: WeibullDistribution - no \"stdDev\" entry");
        return false;
    }

    return true;
}

QString
WeibullDistribution::getAbbreviatedName(void) {
  return QString("Weibull");
}
