// main.cpp

#include <QApplication>
#include "MyEditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyEditor editor;
    editor.show();
    return app.exec();
}

