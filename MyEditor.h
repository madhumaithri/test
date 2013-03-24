
/* CS3249 ASSISGNMENT 1
   NAME : MADHU MAITHRI PARVATANENI
   MATRIC NUMBER : A0074807Y
   LAB GROUP : 1
*/
// MyEditor.h
// Simple text editor.

#ifndef MYEDITOR_H
#define MYEDITOR_H

#include <QMainWindow>

// Class declaration without loading .h files. Faster compilation.
class QAction;
class QMenu;
class QPlainTextEdit;

class MyEditor: public QMainWindow
{
    Q_OBJECT

public:
    MyEditor();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    bool save();
    void about();
    void isModified();
    void newFile();
    bool saveAs();
    void openRecentFile();

private:
    void createWidgets();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();

    QStringList recentFiles;
    QString curFile;	

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *newAction;
    QAction *saveAsAction;
    QAction *copyAction;
    
    //Recent files
    void setCurrentFile(const QString &fileName);	
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    enum{ MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

   
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    
    // Widgets and variables
    QPlainTextEdit *textEdit;
    QString currFile;
   

    // Supporting methods
    bool okToContinue();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFiles(const QString &fileName);
};

#endif
