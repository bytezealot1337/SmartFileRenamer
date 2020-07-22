#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <QMainWindow>

namespace Ui {
class FileRenamer;
}

class FileRenamer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileRenamer(QWidget *parent = 0);
    ~FileRenamer();

    bool m_bSessionActive;

    QString folderString;
    QStringList fileList;

    int fileCount;

    QStringList previewFileList;

    QString m_sFilter;

    QString m_sAddPosition;
    QString m_sAddWhat;
    QString m_sAddDetail;
    int m_iAddDetail;

    int m_iReplaceDetail;

    int m_iNumberOfZeros;
    bool m_bSmartPadding;

    int m_iCurrentTab;

    QString m_sZeroPaddingPosition;

private slots:
    void on_browseButton_clicked();
    void dirFunction();
    void showCurrentFileNames();
    void on_filterLineEdit_textChanged(const QString &arg1);
    void on_addWhatComboBox_currentIndexChanged(const QString &arg1);
    void on_numberOfZerosLineEdit_textChanged(const QString &arg1);
    void on_smartPaddingCheckBox_toggled(bool checked);
    void on_tabWidget_currentChanged(int index);
    void on_zeroPaddingBeforeAfterComboBox_currentIndexChanged(const QString &arg1);
    void previewFunction();
    void on_renameButton_clicked();
    void on_addPositionComboBox_currentIndexChanged(const QString &arg1);
    void on_detailLineEdit_textChanged(const QString &arg1);
    void on_detail2LineEdit_textChanged(const QString &arg1);
    void on_resetButton_clicked();
    void aboutFunction();

private:
    Ui::FileRenamer *ui;
};

#endif // FILERENAMER_H
