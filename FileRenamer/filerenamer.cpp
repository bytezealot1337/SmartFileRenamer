#include "filerenamer.h"
#include "ui_filerenamer.h"
#include "qfiledialog.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>

FileRenamer::FileRenamer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileRenamer)
{
    m_bSessionActive = false;

    ui->setupUi(this);

    QStringList positionList = (QStringList()<<"Before"<<"After");
    this->ui->addPositionComboBox->addItems(positionList);
    this->ui->zeroPaddingBeforeAfterComboBox->addItems(positionList);

    QStringList whatList = (QStringList()<<"Text"<<"Counter");
    this->ui->addWhatComboBox->addItems(whatList);

    m_sFilter = ".jpg";
    this->ui->filterLineEdit->setText(m_sFilter);

    fileCount = 0;

    m_iCurrentTab = 0;

    m_bSmartPadding = false;

    m_sAddPosition = "Before";
    m_sAddWhat = "Text";

    m_sZeroPaddingPosition = "Before";

    m_iReplaceDetail = 0;
    this->ui->detail2LineEdit->setText("0");

    this->ui->tabWidget->setEnabled(false);

    m_iNumberOfZeros = 1;
    this->ui->numberOfZerosLineEdit->setText("1");

    this->ui->actionRename->setEnabled(false);
    this->ui->renameButton->setEnabled(false);

    connect(this->ui->actionBrowse, SIGNAL(triggered()), this, SLOT(on_browseButton_clicked()));
    connect(this->ui->actionReset, SIGNAL(triggered()), this, SLOT(on_resetButton_clicked()));
    connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(this->ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutFunction()));
}

FileRenamer::~FileRenamer()
{
    delete ui;
}

void FileRenamer::on_browseButton_clicked()
{
    if(!m_sFilter.startsWith("."))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name must start with a dot \".\"");
        msgBox.exec();

        return;
    }
    else if(!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 3)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 4)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 5)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 6)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 7)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 8)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 9)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 10)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 11)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 12)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 13)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())
                || (!m_sFilter[12].isLetter() && !m_sFilter[12].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 14)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())
                || (!m_sFilter[12].isLetter() && !m_sFilter[12].isDigit())
                || (!m_sFilter[13].isLetter() && !m_sFilter[13].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 15)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())
                || (!m_sFilter[12].isLetter() && !m_sFilter[12].isDigit())
                || (!m_sFilter[13].isLetter() && !m_sFilter[13].isDigit())
                || (!m_sFilter[14].isLetter() && !m_sFilter[14].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 16)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())
                || (!m_sFilter[12].isLetter() && !m_sFilter[12].isDigit())
                || (!m_sFilter[13].isLetter() && !m_sFilter[13].isDigit())
                || (!m_sFilter[14].isLetter() && !m_sFilter[14].isDigit())
                || (!m_sFilter[15].isLetter() && !m_sFilter[15].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if((m_sFilter.length() == 17)
            && ((!m_sFilter[1].isLetter() && !m_sFilter[1].isDigit())
                || (!m_sFilter[2].isLetter() && !m_sFilter[2].isDigit())
                || (!m_sFilter[3].isLetter() && !m_sFilter[3].isDigit())
                || (!m_sFilter[4].isLetter() && !m_sFilter[4].isDigit())
                || (!m_sFilter[5].isLetter() && !m_sFilter[5].isDigit())
                || (!m_sFilter[6].isLetter() && !m_sFilter[6].isDigit())
                || (!m_sFilter[7].isLetter() && !m_sFilter[7].isDigit())
                || (!m_sFilter[8].isLetter() && !m_sFilter[8].isDigit())
                || (!m_sFilter[9].isLetter() && !m_sFilter[9].isDigit())
                || (!m_sFilter[10].isLetter() && !m_sFilter[10].isDigit())
                || (!m_sFilter[11].isLetter() && !m_sFilter[11].isDigit())
                || (!m_sFilter[12].isLetter() && !m_sFilter[12].isDigit())
                || (!m_sFilter[13].isLetter() && !m_sFilter[13].isDigit())
                || (!m_sFilter[14].isLetter() && !m_sFilter[14].isDigit())
                || (!m_sFilter[15].isLetter() && !m_sFilter[15].isDigit())
                || (!m_sFilter[16].isLetter() && !m_sFilter[16].isDigit())))
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name : Invalid character(s) found...");
        msgBox.exec();

        return;
    }
    else if(m_sFilter.length() > 17)
    {
        QMessageBox msgBox;
        msgBox.setText("Extension name is too long...");
        msgBox.exec();

        return;
    }

    QFileDialog *fileDialog = new QFileDialog;
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setOption(QFileDialog::ShowDirsOnly);
    fileDialog->setViewMode(QFileDialog::Detail);

    int result = fileDialog->exec();

    if(result)
    {
        folderString = fileDialog->selectedFiles()[0];
        dirFunction();
    }
    else
    {
        fileDialog->close();
    }
}

void FileRenamer::dirFunction()
{
    QDir folder(folderString);
    folderString = folder.absolutePath();
    QString sFilterMOD = "*" + m_sFilter;
    folder.setNameFilters(QStringList()<< sFilterMOD);
    fileList = folder.entryList();

    fileCount = fileList.count();

    if(fileCount == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("No files with this extension in folder...");
        msgBox.exec();

        return;
    }
    else if(fileCount >= 1000000)
    {
        QMessageBox msgBox;
        msgBox.setText("There is too many files to rename...");
        msgBox.exec();

        this->ui->currentTextEdit->clear();
        fileList.clear();

        this->ui->previewTextEdit->clear();
        previewFileList.clear();

        this->ui->smartPaddingCheckBox->setChecked(false);

        this->ui->browseButton->setEnabled(true);

        return;
    }

    showCurrentFileNames();

    this->ui->tabWidget->setEnabled(true);
    m_bSessionActive = true;

    this->ui->filterLineEdit->setEnabled(false);

    this->ui->actionRename->setEnabled(true);
    connect(this->ui->actionRename, SIGNAL(triggered()), this, SLOT(on_renameButton_clicked()));

    this->ui->renameButton->setEnabled(true);

    previewFunction();
}

void FileRenamer::showCurrentFileNames()
{
    this->ui->currentTextEdit->clear();

    for(int n = 0; n < fileCount; n++)
    {
        this->ui->currentTextEdit->append(fileList[n]);
    }
}

void FileRenamer::on_filterLineEdit_textChanged(const QString &arg1)
{
    m_sFilter = QString(arg1);
}

void FileRenamer::on_addWhatComboBox_currentIndexChanged(const QString &arg1)
{
    m_sAddWhat = QString(arg1);

    if(m_sAddWhat == "Text")
    {
        this->ui->detailLabel->setText("Text to Add :");
    }
    else if(m_sAddWhat == "Counter")
    {
        this->ui->detailLabel->setText("Count From :");
    }

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_addPositionComboBox_currentIndexChanged(const QString &arg1)
{
    m_sAddPosition = QString(arg1);

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_detailLineEdit_textChanged(const QString &arg1)
{
    if(m_sAddWhat == "Text")
    {
        m_sAddDetail = QString(arg1);
    }
    else if(m_sAddWhat == "Counter")
    {
        m_iAddDetail = QString(arg1).toInt();
    }

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_detail2LineEdit_textChanged(const QString &arg1)
{
    m_iReplaceDetail = QString(arg1).toInt();

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_numberOfZerosLineEdit_textChanged(const QString &arg1)
{
    m_iNumberOfZeros = QString(arg1).toInt();

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_smartPaddingCheckBox_toggled(bool checked)
{
    m_bSmartPadding = checked;

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_tabWidget_currentChanged(int index)
{
    m_iCurrentTab = index;

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::on_zeroPaddingBeforeAfterComboBox_currentIndexChanged(const QString &arg1)
{
    m_sZeroPaddingPosition = QString(arg1);

    if(m_bSessionActive == true)
    {
        previewFunction();
    }
}

void FileRenamer::previewFunction()
{
    if(m_iCurrentTab == 0)
    {
        if(m_sAddPosition == "Before")
        {
            if(m_sAddWhat == "Text")
            {
                previewFileList.clear();

                for(int n = 0; n < fileCount; n++)
                {
                    previewFileList << m_sAddDetail + fileList[n];
                }
            }
            else if(m_sAddWhat == "Counter")
            {
                previewFileList.clear();

                for(int n = 0; n < fileCount; n++)
                {
                    QString sCounter = QString::number(m_iAddDetail + n);

                    previewFileList << sCounter + fileList[n];
                }
            }
        }
        else if(m_sAddPosition == "After")
        {
            if(m_sAddWhat == "Text")
            {
                previewFileList.clear();

                for(int n = 0; n < fileCount; n++)
                {
                    previewFileList << fileList[n];
                    previewFileList[n].chop(m_sFilter.length());
                    previewFileList[n] = previewFileList[n] + m_sAddDetail + m_sFilter;
                }
            }
            else if(m_sAddWhat == "Counter")
            {
                previewFileList.clear();

                for(int n = 0; n < fileCount; n++)
                {
                    QString sCounter = QString::number(m_iAddDetail + n);

                    previewFileList << fileList[n];
                    previewFileList[n].chop(m_sFilter.length());
                    previewFileList[n] = previewFileList[n] + sCounter + m_sFilter;
                }
            }
        }
    }
    else if(m_iCurrentTab == 1)
    {
        if(m_bSmartPadding == false)
        {
            previewFileList.clear();

            for(int n = 0; n < fileCount; n++)
            {
                QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                previewFileList << sReplaceCounter + m_sFilter;
            }
        }
        else if(m_bSmartPadding == true)
        {
            previewFileList.clear();

            if(fileCount+m_iReplaceDetail < 10)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                    previewFileList << sReplaceCounter + m_sFilter;
                }
            }
            else if(fileCount+m_iReplaceDetail < 100)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    if((m_iReplaceDetail+n) < 10)
                    {
                        QString sReplaceCounter = "0" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100)
                    {
                        QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                }
            }
            else if(fileCount+m_iReplaceDetail < 1000)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    if((m_iReplaceDetail+n) < 10)
                    {
                        QString sReplaceCounter = "00" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100)
                    {
                        QString sReplaceCounter = "0" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 1000)
                    {
                        QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                }
            }
            else if(fileCount+m_iReplaceDetail < 10000)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    if((m_iReplaceDetail+n) < 10)
                    {
                        QString sReplaceCounter = "000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100)
                    {
                        QString sReplaceCounter = "00" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 1000)
                    {
                        QString sReplaceCounter = "0" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 10000)
                    {
                        QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                }
            }
            else if(fileCount+m_iReplaceDetail < 100000)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    if((m_iReplaceDetail+n) < 10)
                    {
                        QString sReplaceCounter = "0000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100)
                    {
                        QString sReplaceCounter = "000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 1000)
                    {
                        QString sReplaceCounter = "00" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 10000)
                    {
                        QString sReplaceCounter = "0" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100000)
                    {
                        QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                }
            }
            else if(fileCount+m_iReplaceDetail < 1000000)
            {
                for(int n = 0; n < fileCount; n++)
                {
                    if((m_iReplaceDetail+n) < 10)
                    {
                        QString sReplaceCounter = "00000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100)
                    {
                        QString sReplaceCounter = "0000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 1000)
                    {
                        QString sReplaceCounter = "000" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 10000)
                    {
                        QString sReplaceCounter = "00" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 100000)
                    {
                        QString sReplaceCounter = "0" + QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                    else if((m_iReplaceDetail+n) < 1000000)
                    {
                        QString sReplaceCounter = QString::number(m_iReplaceDetail + n);
                        previewFileList << sReplaceCounter + m_sFilter;
                    }
                }
            }
        }
    }
    else if(m_iCurrentTab == 2)
    {
        QString sZeroPadding = "0";

        for(int i = 0; i < m_iNumberOfZeros-1; i++)
        {
            sZeroPadding += "0";
        }

        if(m_sZeroPaddingPosition == "Before")
        {
            previewFileList.clear();

            for(int n = 0; n < fileCount; n++)
            {
                previewFileList << sZeroPadding + fileList[n];
            }
        }
        else if(m_sZeroPaddingPosition == "After")
        {
            previewFileList.clear();

            for(int n = 0; n < fileCount; n++)
            {
                previewFileList << fileList[n];
                previewFileList[n].chop(m_sFilter.length());
                previewFileList[n] = previewFileList[n] + sZeroPadding + m_sFilter;
            }
        }
    }

    this->ui->previewTextEdit->clear();

    for(int n = 0; n < fileCount; n++)
    {
        this->ui->previewTextEdit->append(previewFileList[n]);
    }
}

void FileRenamer::on_renameButton_clicked()
{
    for(int n = 0; n < fileCount; n++)
    {
        QString sPathAndCurrentFileName(folderString + "/" + fileList[n]);
        QString sPathAndNewFileName(folderString + "/_temp_" + previewFileList[n]);

        QFile file(sPathAndCurrentFileName);
        file.rename(sPathAndNewFileName);

        this->ui->progressBar->setValue(50*n/fileCount);
    }

    QDir folder(folderString);
    folderString = folder.absolutePath();
    QString sFilterMOD = "*" + m_sFilter;
    folder.setNameFilters(QStringList()<< sFilterMOD);
    fileList = folder.entryList();

//    fileCount = fileList.count();

    for(int n = 0; n < fileCount; n++)
    {
        QString sPathAndCurrentFileName(folderString + "/" + fileList[n]);
        QString sPathAndNewFileName(folderString + "/" + previewFileList[n]);

        QFile file(sPathAndCurrentFileName);
        file.rename(sPathAndNewFileName);

        this->ui->progressBar->setValue(50+50*n/fileCount);
    }

    this->ui->progressBar->setValue(100);

    this->ui->currentTextEdit->clear();

    folder.setNameFilters(QStringList()<< sFilterMOD);
    fileList = folder.entryList();

//    fileCount = fileList.count();

    for(int n = 0; n < fileCount; n++)
    {
        this->ui->currentTextEdit->append(fileList[n]);
    }

    this->ui->previewTextEdit->clear();
    previewFunction();
}

void FileRenamer::on_resetButton_clicked()
{
    this->ui->currentTextEdit->clear();
    fileList.clear();

    this->ui->previewTextEdit->clear();
    previewFileList.clear();

    this->ui->filterLineEdit->setEnabled(true);

    this->ui->actionRename->setEnabled(false);
    this->ui->renameButton->setEnabled(false);

    this->ui->progressBar->setValue(0);
}

void FileRenamer::aboutFunction()
{
    QMessageBox::about(this, tr("Universal File Renamer"), "Universal File Renamer V1.0 - CopyRight © Apps Brothers 2014 - All Rights Reserved.");
}
