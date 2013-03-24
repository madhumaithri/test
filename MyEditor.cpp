 /* CS3249 ASSISGNMENT 1
   NAME : MADHU MAITHRI PARVATANENI
   MATRIC NUMBER : A0074807Y
   LAB GROUP : 1
*/

// MyEditor.cpp
// Simple text editor.

#include <QtGui>
#include "MyEditor.h"


// Constructor

MyEditor::MyEditor()
{
    createWidgets();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
}


// Protected methods

void MyEditor::closeEvent(QCloseEvent *event)
{
    if (okToContinue())
        event->accept();
    else
        event->ignore();
}


// Create widgets, actions, menus, toolbars, status bar.

void MyEditor::createWidgets()
{
    textEdit = new QPlainTextEdit;
    setCentralWidget(textEdit);
    setWindowIcon(QIcon(":/images/myeditor.png"));
    setGeometry(0, 0, 550, 650);
    setCurrentFiles("");
    setCurrentFile("");
}


void MyEditor::createActions()
{      
    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    
    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save the document to a file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit MyEditor"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    
    cutAction = new QAction(tr("C&ut"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("Cut selected contents to clipboard"));
    connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));
      
    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("Paste clipboard's contents into current"
                                 "selection"));
    connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));
    
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Open a new file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    saveAsAction = new QAction(tr("&SaveAs"), this);
    saveAsAction->setIcon(QIcon(":/images/saveas.png"));
    saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
    saveAsAction->setStatusTip(tr("Save as a file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("Copy a file"));
    connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));
    

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show information about this MyEditor"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    

    //recently opened files
    
    for(int i=0;i<MaxRecentFiles; ++i)
    {
   	recentFileActions[i]=new QAction(this);
	recentFileActions[i]->setVisible(false);
	connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }
    
    
    // Other connections
    cutAction->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAction, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(isModified()));

   // Other connections
    copyAction->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAction, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(isModified()));
}


void MyEditor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    separatorAction = fileMenu->addSeparator();
    for(int i=0;i<MaxRecentFiles;i++)
    fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();

    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}


void MyEditor::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
}


void MyEditor::createStatusBar()
{
    statusBar()->showMessage(tr(""));
}


// Slot functions

void MyEditor::open()
{
    if (okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open plain text file"), ".",
            tr("Plain text files (*.txt)"));
            
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}


bool MyEditor::save()
{
   return saveFile(currFile);
}


void MyEditor::about()
{
    QMessageBox::about(this, tr("About MyEditor"),
        tr("This is a simple editor written in Qt.\n\n"
           "It illustrates menu bar, toolbars, status bar,"
           "and the use of QPlainTextEdit widget"));
}


void MyEditor::isModified()
{
    setWindowModified(textEdit->document()->isModified());
}


// Supporting methods

bool MyEditor::okToContinue()
{
    if (!(textEdit->document()->isModified()))
        return true;
    
    int code = QMessageBox::warning(this, tr("MyEditor"),
        tr("The document has been modified.\n"
           "Do you want to save the changes?"),
        QMessageBox::Yes | QMessageBox::Default,
        QMessageBox::No,
        QMessageBox::Cancel | QMessageBox::Escape);

    if (code == QMessageBox::Yes)
        return save();
    else if (code == QMessageBox::Cancel)
        return false;
    
    return true;
}


void MyEditor::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("MyEditor"),
            tr("Cannot read file %1:\n%2.")
            .arg(fileName).arg(file.errorString()));
        return;
    }

    // Read file content into textEdit widget.
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFiles(fileName);setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}


bool MyEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
      saveAs();       
    }

    // Write contents in textEdit widget into file.
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFiles(fileName);setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}


void MyEditor::setCurrentFiles(const QString &fileName)
{
    currFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = "MyEditor - " + currFile + "[*]";
    if (currFile.isEmpty())
        shownName = "MyEditor - untitled.txt [*]";
    setWindowTitle(shownName);
}

void MyEditor::newFile()
{
if(okToContinue())
	{
	  textEdit->clear();
	  setCurrentFiles("");setCurrentFile("");	 	
	}
}

bool MyEditor::saveAs()
{
QString FileName = QFileDialog::getSaveFileName();
if(FileName!="")
{saveFile(FileName);return true;}
else
return false;
}

//Recent Files

void MyEditor::setCurrentFile(const QString &fileName)
{
 curFile = fileName;
 setWindowModified(false);
 QString shownName = tr("Untitled");
 if(!curFile.isEmpty())
 {
  shownName = strippedName(curFile);
  recentFiles.removeAll(curFile);
  recentFiles.prepend(curFile);
  updateRecentFileActions();
 }
 setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("MyEditor")));
}

QString MyEditor::strippedName(const QString &fullFileName)
{
   return QFileInfo(fullFileName).fileName(); 
}

void MyEditor::updateRecentFileActions()
{
 QMutableStringListIterator i(recentFiles);
 //remove files that no longer exist
 while(i.hasNext())
 {
  if(!QFile::exists(i.next()))
   i.remove();
 }
 //make the list
 for( int j=0; j< MaxRecentFiles; ++j)
 {
  if(j<recentFiles.count())
  {
   QString text=tr("&%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));
   recentFileActions[j]->setText(text);
   recentFileActions[j]->setData(recentFiles[j]);
   recentFileActions[j]->setVisible(true);
  }
  else
  {
   recentFileActions[j]->setVisible(false);
  }
  }
  //add the separator
  separatorAction->setVisible(!recentFiles.isEmpty()); 
}


void MyEditor::openRecentFile()
{
if(okToContinue())
 {
 QAction *action = qobject_cast<QAction *>(sender());
 if(action)
 loadFile(action->data().toString());
 }
}
