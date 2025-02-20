#pragma once

#include <IApplication.h>

#include <QtWidgets/QApplication>


class CApplication : public QApplication, public IApplication
{
    Q_OBJECT

public:
    CApplication ( int, char*[] );
    ~CApplication ();

    // Inherited via IApplication
    bool execute ( ) override;
};
