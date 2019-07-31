#include <QString>
#include <QtTest>

#include <dgiofile.h>
#include <dgiofileinfo.h>

class DGioSimpleFileInfoTest : public QObject
{
    Q_OBJECT

public:
    DGioSimpleFileInfoTest();

private Q_SLOTS:
    void testCase_RegularFile();
};

DGioSimpleFileInfoTest::DGioSimpleFileInfoTest()
{
    //
}

void DGioSimpleFileInfoTest::testCase_RegularFile()
{
    QTemporaryFile tmpFile("test_RegularFile.txt");
    QVERIFY(tmpFile.open());
    QFileInfo tmpFileInfo(tmpFile);

    QScopedPointer<DGioFile> file(DGioFile::createFromPath(tmpFileInfo.absoluteFilePath()));

    QCOMPARE(file->basename(), tmpFileInfo.fileName());
    QCOMPARE(file->path(), tmpFileInfo.absoluteFilePath());
}

QTEST_APPLESS_MAIN(DGioSimpleFileInfoTest)

#include "tst_simplefileinfo.moc"
